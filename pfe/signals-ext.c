/** 
 * -- Handle signals in forth
 *
 *  Copyright (C) Tektronix, Inc. 1998 - 2001. All rights reserved.
 *
 *  @see     GNU LGPL
 *  @author  Tektronix CTE            @(#) %derived_by: guidod %
 *  @version %version: 5.9 %
 *    (%date_modified: Mon Mar 12 10:32:41 2001 %)
 *
 *  @description
 *  Signal-Klassen, die ich in PFE SIGNALS extension aufmache:
 *
 *  <dl>
 *  <dt>P4_ON_XXXXX:</dt><dd>
 *   	ein Signal dem direkt ein bestimmter THROW in Forth
 *	entspricht, z.B. SIGFPE.
 *  </dd>
 *  <dt>Abort:</dt><dd>		
 *	ein Signal, das uns nicht gleich t�tet, dem aber kein
 *	THROW entspricht, z.B. SIGILL. Es f�hrt zu einem
 *	ABORT" Signalbeschreibung"
 *   </dd>
 *  <dt>Fatal:</dt><dd>
 *	wir sterben gracefully.
 *  </dd>
 *  <dt>Default:</dt><dd>
 *	Ein Signal, mit dem ich nichts anfangen kann.
 *	Wenn z.B. ein Forth-Programmierer und AIX wei�,
 *	was SIGGRANT bedeutet, kann er ein Forth-Wort drauf
 *	setzen, ansonsten bleibt dieses Signal unber�hrt. 
 *  </dd>
 *  <dt>Chandled:</dt><dd>
 *	Ein Signal, das pfe intern braucht und behandelt,
 *	konkret Job-Control und SIGWINCH, wenn xterm die
 *	Gr��e �ndert.
 *  </dd>
 *  </dl>
 *
 * Auf den ersten drei Typen sitzt der default Forth Signal-Handler.
 * Dessen Aktion ist, gucken, ob Forth-Routine registriert ist (dann
 * ausf�hren) oder nicht (dann throw, abort" oder tot).
 *
 * Auf den vierten Typ wird der Forth-Signal-Handler erst dann
 * installiert, wenn der User ein Forth-Wort draufschaltet, ansonsten
 * bleibt es bei der System-default-Aktion.
 *
 * Auf den vierten Typ wird unter keinen Umst�nden der default
 * Forth-Signal-Handler geschaltet. Also k�nnen da auch keine Forth-Worte
 * drauf. Wenn ich das alles jetzt noch richtig verstehe :-)
 *                             <p align=right> Dirk-Uwe Zoller </p>
 */
/*@{*/

#if defined(__version_control__) && defined(__GNUC__)
static char* id __attribute__((unused)) = 
"@(#) $Id: signals-ext.c,v 0.32 2006-08-08 06:21:35 guidod Exp $";
#endif

#define _P4_SOURCE 1

#include <pfe/pfe-base.h>
#include <pfe/def-xtra.h>

#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <pfe/def-comp.h>
#include <pfe/term-sub.h>
#include <pfe/_nonansi.h>
#include <pfe/_missing.h>
#include <pfe/logging.h>

typedef void (*SigHdl) (int);	/* signal handler function type */

enum				/* Classification of signals: The */
{				/* signal class is either a THROW code or: */
    Fatal,			/*   p4th terminates if such a signal arrives */
    Abort,			/*   executes ABORT" */
    Chandled,			/*   handled by C code, e.g. stop/continue */
    Default			/*   left alone by p4th, cannot be caught */
};

typedef struct			/* all we need to know about a signal */
{
    short sig;			/* the signal */
    short cLass;		/* a classification */
    char const * name;		/* the name of the signal */
#ifndef HAVE_SYS_SIGLIST
    char const * msg;		/* a textual signal description */
#endif
    SigHdl old;			/* state of signal before we took it */
    p4xt hdl;			/* a forth word to handle the signal */
} Siginfo;

#ifdef PFE_OLD_STRINGIZE
# ifdef HAVE_SYS_SIGLIST
# define SIG(NM,CL,MSG)		{ NM, CL, "NM", SIG_DFL, 0 }
# else
# define SIG(NM,CL,MSG)		{ NM, CL, "NM", MSG, SIG_DFL, 0 }
# endif
#else
# ifdef HAVE_SYS_SIGLIST
# define SIG(NM,CL,MSG)		{ NM, CL, #NM, SIG_DFL, 0 }
# else
# define SIG(NM,CL,MSG)		{ NM, CL, #NM, MSG, SIG_DFL, 0 }
# endif
#endif

/*
 * With the means of the above structures and classifications we
 * describe a lot of signals to p4th conditionally. Fine if a system
 * has a signal. If not it's just as well.
 */

static Siginfo siginfo[] =
{

/**
 * signal constants as being defined on the local system.
 * not all signal names must be valid in a specific system,
 * the pfe will only export those being available.
 * <p>
 * The set of signal names being tested for during pfe compilation
 * are described in W.R.Stevens' <br>
 * "Advanced Programming in the UNIX Environment"
 * <p>
 * The signals constants are generated by their
 * signal constructor => <<load_signals>>
 */
    /*"SIGABRT"*/
#ifdef SIGABRT
  SIG (SIGABRT, Fatal, "abnormal termination (abort)"),
#endif
    /*"SIGALRM"*/
#ifdef SIGALRM
  SIG (SIGALRM, Abort, "time out (alarm)"),
#endif
    /*"SIGBUS"*/
#ifdef SIGBUS
  SIG (SIGBUS, P4_ON_ADDRESS_ALIGNMENT, NULL),
#endif
    /*"SIGCHLD"*/
#ifdef SIGCHLD
  SIG (SIGCHLD, Default, "change in status of child"),
#endif
    /*"SIGCONT"*/
#ifdef SIGCONT
  SIG (SIGCONT, Default, "continue stopped process"),
#endif
    /*"SIGEMT"*/
#ifdef SIGEMT
  SIG (SIGEMT, Abort, "hardware fault (EMT)"),
#endif
    /*"SIGPFE"*/
#ifdef SIGFPE
  SIG (SIGFPE, P4_ON_FP_FAULT, NULL),
#endif
    /*"SIGHUP"*/
#ifdef SIGHUP
  SIG (SIGHUP, Fatal, "hangup"),
#endif
    /*"SIGILL"*/
#ifdef SIGILL
  SIG (SIGILL, Abort, "illegal hardware instruction"),
#endif
    /*"SIGINFO"*/
#ifdef SIGINFO
  SIG (SIGINFO, Default, "status request from keyboard"),
#endif
    /*"SIGINT"*/
#ifdef SIGINT
  SIG (SIGINT, P4_ON_USER_INTERRUPT, NULL),
#endif
    /*"SIGIO"*/
#ifdef SIGIO
  SIG (SIGIO, Default, "asynchronous io"),
#endif
    /*"SIGIOT"*/
#ifdef SIGIOT
  SIG (SIGIOT, Abort, "hardware fault (IOT)"),
#endif
    /*"SIGKILL"*/
#ifdef SIGKILL
  SIG (SIGKILL, Default, "kill"),
#endif
    /*"SIGPIPE"*/
#ifdef SIGPIPE
  SIG (SIGPIPE, Fatal, "write to pipe with no readers"),
#endif
    /*"SIGPOLL"*/
#ifdef SIGPOLL
  SIG (SIGPOLL, Abort, "pollable event (poll)"),
#endif
    /*"SIGPROF"*/
#ifdef SIGPROF
  SIG (SIGPROF, Abort, "profiling time alarm (timer)"),
#endif
    /*"SIGPWR"*/
#ifdef SIGPWR
  SIG (SIGPWR, Default, "power fail/restart"),
#endif
    /*"SIGQUIT"*/
#ifdef SIGQUIT
  SIG (SIGQUIT, Fatal, "terminal quit key"),
#endif
    /*"SIGSEGV"*/
#ifdef SIGSEGV
  SIG (SIGSEGV, P4_ON_INVALID_MEMORY, NULL),
#endif
    /*"SIGSTOP"*/
#ifdef SIGSTOP
  SIG (SIGSTOP, Default, "stop"),
#endif
    /*"SIGSYS"*/
#ifdef SIGSYS
  SIG (SIGSYS, Abort, "invalid system call"),
#endif
    /*"SIGTERM"*/
#ifdef SIGTERM
  SIG (SIGTERM, Fatal, "terminated"),
#endif
    /*"SIGTRAP"*/
#ifdef SIGTRAP
  SIG (SIGTRAP, Abort, "hardware fault (trace trap)"),
#endif
    /*"SIGTSTP"*/
#ifdef SIGTSTP
  SIG (SIGTSTP, Chandled, "terminal stop character"),
#endif
    /*"SIGTTIN"*/
#ifdef SIGTTIN
  SIG (SIGTTIN, Chandled, "background read from control tty"),
#endif
    /*"SIGTTOU"*/
#ifdef SIGTTOU
  SIG (SIGTTOU, Chandled, "background write to control tty"),
#endif
    /*"SIGURG"*/
#ifdef SIGURG
  SIG (SIGURG, Abort, "urgent condition"),
#endif
    /*"SIGUSR1"*/
#ifdef SIGUSR1
  SIG (SIGUSR1, Abort, "user defined signal 1"),
#endif
    /*"SIGUSR2"*/
#ifdef SIGUSR2
  SIG (SIGUSR2, Abort, "user defined signal 2"),
#endif
    /*"SIGVTALRM"*/
#ifdef SIGVTALRM
  SIG (SIGVTALRM, Abort, "virtual time alarm (timer)"),
#endif
    /*"SIGWINCH"*/
#ifdef SIGWINCH
  SIG (SIGWINCH, Chandled, "terminal window size change"),
#endif
    /*"SIGXCPU"*/
#ifdef SIGXCPU
  SIG (SIGXCPU, Fatal, "CPU limit exceeded"),
#endif
    /*"SIGXFSZ"*/
#ifdef SIGXFSZ
  SIG (SIGXFSZ, Abort, "file size limit exceeded"),
#endif

/**
 * Some Signals are specific to certain systems. They don't belong
 * to the normal set of UNIX signals like => SIGALRM or => SIGQUIT
 * <p>
 * The signals constants are generated by their
 * signal constructor => <<load_signals>>
 */
    /*"SIGSTKFLT"*/
#ifdef SIGSTKFLT		/* Linux */
  SIG (SIGSTKFLT, Abort, "SIGSTKFLT"),
#endif

    /*"SIGBREAK"*/
#ifdef SIGBREAK			/* EMX, Watcom */
  SIG (SIGBREAK, P4_ON_USER_INTERRUPT, NULL),
#endif

    /*"SIGMSG"*/
#ifdef SIGMSG			/* AIX 3.2 */
  SIG (SIGMSG, Default, "input data is in the HFT ring buffer"),
#endif
    /*"SIGDANGER"*/
#ifdef SIGDANGER
  SIG (SIGDANGER, Default, "system crash imminent; free up some page space"),
#endif
    /*"SIGMIGRATE"*/
#ifdef SIGMIGRATE
  SIG (SIGMIGRATE, Default, "migrate process (see TCF)"),
#endif
    /*"SIGPRE"*/
#ifdef SIGPRE
  SIG (SIGPRE, Default, "programming exception"),
#endif
    /*"SIGVIRT"*/
#ifdef SIGVIRT
  SIG (SIGVIRT, Default, "AIX virtual time alarm"),
#endif
    /*"SIGGRANT"*/
#ifdef SIGGRANT
  SIG (SIGGRANT, Default, "HFT monitor mode granted"),
#endif
    /*"SIGRETRACT"*/
#ifdef SIGRETRACT
  SIG (SIGRETRACT, Default, "HFT monitor mode should be relinguished"),
#endif
    /*"SIGSOUND"*/
#ifdef SIGSOUND
  SIG (SIGSOUND, Default, "HFT sound control has completed"),
#endif
    /*"SIGSAK"*/
#ifdef SIGSAK
  SIG (SIGSAK, Default, "secure attention key"),
#endif
};

static int
getinfo (int sig)
{
    int i;

    for (i = 0; i < DIM (siginfo); i++)
        if (siginfo[i].sig == sig)
            return i;

    p4_throw (P4_ON_ARG_TYPE);
    return i;
}

#define SIGHANDLER (RETSIGTYPE (*)(int))

static void
sig_handler (int sig)		/* Signal handler for all signals */
{
    Siginfo *s;
    const char *msg;

# if !KEEPS_SIGNALS
    signal (sig, SIGHANDLER sig_handler);	/* reinstall handler */
# endif
# if defined SYS_EMX || defined SYS_WC_OS2V2
    signal (sig, SIG_ACK);	/* OS/2: acknowledge signal */
# endif
# if defined SYS_EMX
    _control87 (EM_DENORMAL | EM_INEXACT, MCW_EM);
# endif
  
# if defined P4_REGTH && defined VXWORKS
    p4TH = p4_main_threadP; 
    /* register-p4TH may be lost if signal came from a system proc */
# endif

    s = &siginfo[getinfo (sig)];
    if (s->hdl)
        p4_call (s->hdl);	/* a p4sys.handled signal */
    else
    {
# ifdef HAVE_SYS_SIGLIST
        msg = sys_siglist[sig];
# else
        msg = s->msg;
# endif
        switch (s->cLass)
	{
         default:		/* an ANSI-Forth defined condition */
             p4_throw (s->cLass);
         case Abort:		/* another catchable signal */
             p4_throws (-256 - sig, msg, 0);
         case Fatal:		/* a signal that kills us */
             P4_fatal2 ("Received signal %s, %s", s->name, msg);
	     PFE.exitcode = 1;
             p4_longjmp_exit ();
	}
    }
}

/*
 * Actions to take when job control interferes or on window size change:
 */

#ifdef SIGTSTP
static void
stop_hdl (int sig)
{
#  if !KEEPS_SIGNALS
    signal (sig, SIGHANDLER stop_hdl);
#  endif
    _p4_thread_local();
    PFE.on_stop ();
    p4_swap_signals ();
#  if _BSD
    _pfe_raise (SIGSTOP);
#  else
    _pfe_raise (SIGTSTP);
#  endif
    p4_swap_signals ();
    PFE.on_continue ();
}
#endif

#ifdef SIGWINCH
static void
winchg_hdl (int sig)
{
#  if !KEEPS_SIGNALS
    signal (sig, winchg_hdl);
#  endif
    _p4_thread_local();
    PFE.on_winchg ();
}
#endif

#ifdef SIGALRM
static volatile void
handle_sigalrm (int sig)
{
#  if !KEEPS_SIGNALS
    signal (sig, SIGHANDLER handle_sigalrm);
#  endif
    _p4_thread_local();
    if (PFE.on_sigalrm)
        (*PFE.on_sigalrm)();
}
#endif

/**
 * install all signal handlers:
 */
_export void
p4_install_signal_handlers (void)
{
    int i, j;

    for (i = 0; i < DIM (siginfo); i++)
    {
        /* some systems may have more than one name for the same signal,
         * take care not to install it twice: */
        for (j = 0; j < i; j++)
            if (siginfo[i].sig == siginfo[j].sig)
                goto cont;
        switch (siginfo[i].cLass)
	{
         default:
             siginfo[i].old = signal (siginfo[i].sig, sig_handler);
         case Chandled:
         case Default:;
	}
     cont:;
    }
#ifdef SIGTSTP
    if (signal (SIGTSTP, SIG_IGN) == SIG_DFL)
    {
        signal (SIGTSTP, stop_hdl);
        siginfo[getinfo (SIGTSTP)].old = SIG_DFL;
        siginfo[getinfo (SIGTTIN)].old = signal (SIGTTIN, stop_hdl);
        siginfo[getinfo (SIGTTOU)].old = signal (SIGTTOU, stop_hdl);
    }
#endif
#ifdef SIGWINCH
#ifdef KEEPS_SIGNALS
    signal (SIGWINCH, winchg_hdl);
#endif
    winchg_hdl (SIGWINCH);
#endif

#ifdef SIGALRM
    signal (SIGALRM, SIGHANDLER handle_sigalrm);
#endif
}

/**
 * switch between p4th setting of signals and state before 
 */
_export void
p4_swap_signals (void)
{
    int i;

    for (i = 0; i < DIM (siginfo); i++)
        if (siginfo[i].cLass != Default || siginfo[i].hdl)
            siginfo[i].old = signal (siginfo[i].sig, siginfo[i].old);
}

/**
 * xt != NULL: install forth word as signal handler for signal
 * xt == NULL: install p4th default signal handler for signal
 */
_export p4xt
p4_forth_signal (int sig, p4xt xt)
{
    int i = getinfo (sig);
    p4xt old;
    
    old = siginfo[i].hdl;
    siginfo[i].hdl = xt;

    if (siginfo[i].cLass == Default)
    {
        if (xt == NULL)
        {
            siginfo[i].old = signal (sig, siginfo[i].old);
        }
        else
        {
            siginfo[i].old = signal (sig, sig_handler);
        }
    }

    return old;
}

/**
 * Load constants for each signal found into the dictionary.
 */
_export void
p4_load_signals (p4_Wordl *wid)
{
    Siginfo *s;
    char *nfa;
    Head *h;

    for (s = siginfo; s < siginfo + DIM (siginfo); s++)
    {
        h = p4_make_head (s->name, strlen (s->name), &nfa, wid);
        h->cfa = p4_constant_RT_;
        FX_COMMA (s->sig);
    }
}

/** 
 * the signals-constructor will declare the available
 * system signals as contants - usually sth. like
 * => SIGALRM or => SIGHUP or => SIGABRT
 * <p>
 * some signals are only valid in specific systems,
 * like => SIGBREAK or => SIGMSG or => SIGVIRT
 */
FCode (p4_load_signals)
{
    p4_load_signals (CURRENT);
}

P4_LISTWORDS (signals) =
{
    CX ("<<load_signals>>", p4_load_signals),
};
P4_COUNTWORDS (signals, "Signals Extension");

/*@}*/

