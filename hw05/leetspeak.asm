;;=============================================================
;; CS 2110 - Summer 2021
;; Homework 5 - Leetspeak!
;;=============================================================
;; Name: 
;;=============================================================

;; Pseudocode (see PDF for explanation)
;;
;;	string = "spongebob";
;;
;;	i = 0;
;;
;;	while(string[i] != 0) {
;;		if (string[i] == 'o') {
;;			//convert to '0'
;;			//note that 'o' - '0' is 0x3F in hex
;;			string[i] = string[i] - 0x3F;
;;		} else if (string[i] == 'e') {
;;			//convert to '3'
;;			//note that 'e' - '3' is 0x32 in hex
;;			string[i] = string[i] - 0x32;
;;		}
;;
;;		i++;
;;	}

.orig x3000

;;put your code here
		AND R0, R0, #0		; i = 0

WHILE	LD R1, STRING		; addr of STRING
		ADD R6, R1, R0		; get address of STRING[i]
		LDR R6, R6, #0		; R6 = STRING[i]
		BRz PASS			; if STRING[i] == 0, halt

		LD R2, LOWERO		; value of o
		NOT R2, R2			
		ADD R2, R2, #1		; - LOWERO
		ADD R2, R6, R2
		BRz CHANGEO

		LD R2, LOWERE
		NOT R2, R2
		ADD R2, R2, #1
		ADD R2, R6, R2		; string[i] - 'e'
		BRz CHANGEE
		BR ALWAYS

CHANGEO	LD R1, STRING		; addr of STRING
		ADD R6, R1, R0		; get address of STRING[i]
		LDR R6, R6, #0		; get value STRING[i]
		LD R4, CHANGE0
		NOT R4, R4		
		ADD R4, R4, #1
		ADD R4, R4, R6		; STRING[i] - '0'
		LD R1, STRING		; addr of STRING
		ADD R1, R1, R0		; addr of string[i]
		STR R4, R1,	#0		; string[i] = string[i] - 0x3F; 
		BR ALWAYS

CHANGEE	LD R1, STRING		; addr of STRIN
		ADD R6, R1, R0		; get address of STRING[i]
		LDR R6, R6, #0		; get value STRING[i]
		LD R5, CHANGE3
		NOT R5, R5		
		ADD R5, R5, #1
		ADD R5, R5, R6		; string[i] - 0x32
		LD R1, STRING		; addr of STRING
		ADD R1, R1, R0		; addr of string[i]
		STR R5, R1,	#0		; string[i] = string[i] - 0x32;
		BR ALWAYS

ALWAYS	ADD R0, R0, #1		; i++
		BR WHILE

PASS	HALT

STRING .fill x4000

LOWERO .fill x6F
LOWERE .fill x65
CHANGE0 .fill x3F
CHANGE3 .fill x32

.end

.orig x4000

.stringz "spongebob"

.end