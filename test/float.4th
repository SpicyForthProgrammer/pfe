\
\ test/float.4th ---	Does a few tests of the floating point word set.
\			Only the most basic things.
\ (duz 05Aug93)
\

CR .( floating point word set)
CR .( =======================)
CR

MARKER FORGET-FLOAT-TESTS

DECIMAL

CR .( testing F~) CR .(    )

 1.0E0		 1.0E0		 0E		F~ Y
 1.0E0		 1.1E0		 0E		F~ N SPACE

 1.000000E0	 1.000001E0	 0.0000011E0	F~ Y
-1.000000E0	-1.000001E0	 0.0000011E0	F~ Y
 1.000000E0	 1.000001E0	 0.0000009E0	F~ N
 1.000000E0	-1.000001E0	 0.0000011E0	F~ N
-1.000000E0	 1.000001E0	 0.0000011E0	F~ N SPACE

 1.000000E10	 1.000001E10	-0.0000006E0	F~ Y
-1.000000E10	-1.000001E10	-0.0000006E0	F~ Y
 1.000000E10	 1.000001E10	-0.0000004E0	F~ N
-1.000000E10	 1.000001E10	-0.0000006E0	F~ N
 1.000000E10	-1.000001E10	-0.0000006E0	F~ N SPACE D FD

: F=	0E F~ ;			\ identity
: FEX	F= Y ;			\ 0 if two floats identical
: FEQ	-1E-15 F~ Y ;		\ 0 if two floats have same value

CR .( floating point number input) CR .(    )
1E0	FDEPTH 1 = Y		\ interpreted floating number
1. D>F	FDEPTH 2 = Y		\ converted floating number from double
FEX	D FD			\ should be exactly identical

: TEST>FLOAT	S" "		>FLOAT Y 0E0		FEX
		S"      "	>FLOAT Y 0E0		FEX
		S" 0E "		>FLOAT Y 0E0		FEX
		S"  0E0   "	>FLOAT Y 0E0		FEX
		S"  +0D  "	>FLOAT Y 0E0		FEX
		S"  0E+0  "	>FLOAT Y 0E0		FEX
		S"  1-1   "	>FLOAT Y 1E-1		FEX
		S"  1+1   "	>FLOAT Y 1E1		FEX
		S"  1      "	>FLOAT Y 1E0		FEX
		S"  1.E+1  "	>FLOAT Y 1E1		FEX
		S"  .1E+1  "	>FLOAT Y 1E0		FEX
		S" 10.E-1"	>FLOAT Y 1E0		FEX
		S"  -1.E+0"	>FLOAT Y -1E0		FEQ
		S"  -.1E+1"	>FLOAT Y -1E0		FEQ
		S" -10.E-1"	>FLOAT Y -1E0		FEQ
		S" +1234.56E-9"	>FLOAT Y +1234.56E-9	FEQ
		S" -1234.56E+9"	>FLOAT Y -1234.56E+9	FEQ ;

CR .(    ) TEST>FLOAT SPACE D FD

CR .( floating point constants and variables) CR .(    )
+.1234567E+09 FCONSTANT FC1 FD	FC1 123456700. D>F FEX	FD
-.7654321E-34 FCONSTANT FC2 FD	FC2 -.7654321E-34 FEX	FD	SPACE

\ constant name of different length to detect alignment problems
+.1234567E+09 FCONSTANT FCONST1 FD  FCONST1 123456700. D>F FEX	FD
-.7654321E-34 FCONSTANT FCONST2 FD  FCONST2 -.7654321E-34 FEX	FD	SPACE

FVARIABLE FV1		FC1 FV1     F! FD
FVARIABLE FVARIA2	FC2 FVARIA2 F! FD	SPACE FD

FV1     F@ FC1 FEX
FVARIA2 F@ FC2 FEX

FC2 FV1     F!  FV1     F@ FC2 FEX
FC1 FVARIA2 F!  FVARIA2 F@ FC1 FEX	SPACE D FD

CR .( floating point stack operations) CR .(    )
FC1 FC2		FDROP	FC1 F=				  Y FD	D SPACE
FC1 FC2		FDUP	FC2 F=  FC2 F=  AND  FC1 F=  AND  Y FD	D SPACE
FC1 FC2		FSWAP	FC1 F=  FC2 F=  AND		  Y FD	D SPACE
FC1 FC2		FOVER	FC1 F=  FC2 F=  AND  FC1 F=  AND  Y FD  D SPACE
FC1 FC2	1E0	FROT	FC1 F=  1E0 F=  AND  FC2 F=  AND  Y FD	D SPACE


CR .( testing REPRESENT) CR .(    )
: TEST-REPRESENT
	\ width --- ; F: r -- ;
	FDUP F0< >R
	PAD OVER REPRESENT  DROP
	R> = Y  .
	[CHAR] " EMIT PAD SWAP TYPE [CHAR] " EMIT SPACE SPACE ;

          0E0  1 TEST-REPRESENT
          0E0  3 TEST-REPRESENT
          0E0  7 TEST-REPRESENT
          0E0 11 TEST-REPRESENT		CR .(    )

          1E0  1 TEST-REPRESENT
         -1E0  3 TEST-REPRESENT
          1E0  7 TEST-REPRESENT
         -1E0 11 TEST-REPRESENT		CR .(    )

          1E1   1 TEST-REPRESENT
         -1E3   3 TEST-REPRESENT
          1E5   7 TEST-REPRESENT
         -1E11 11 TEST-REPRESENT	CR .(    )

0.950000001E1   1 TEST-REPRESENT
    -0.9994E3   3 TEST-REPRESENT
.9999999501E5   7 TEST-REPRESENT
 -.99999999E30  9 TEST-REPRESENT	CR .(    )

0.950000001E-1  1 TEST-REPRESENT
    -0.9994E-3  3 TEST-REPRESENT
  .99999995E-5  7 TEST-REPRESENT
 -.99999999E-30 9 TEST-REPRESENT	CR .(    )

  123456789E1   1 TEST-REPRESENT
 -123456789E3   3 TEST-REPRESENT
  123456789E5   7 TEST-REPRESENT
 -123456789E30  9 TEST-REPRESENT	CR .(    )

  123456789E-1  1 TEST-REPRESENT
 -123456789E-3  3 TEST-REPRESENT
  123456789E-5  7 TEST-REPRESENT
 -123456789E-30 9 TEST-REPRESENT	CR .(    )

D FD

FORGET-FLOAT-TESTS
