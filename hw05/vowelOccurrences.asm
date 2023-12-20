;;=============================================================
;; CS 2110 - Fall 2020
;; Homework 5 - Vowel Occurrences
;;=============================================================
;; Name:
;;=============================================================

;; Pseudocode (see PDF for explanation):
;;
;;	string = "A TEN OUT OF TEN IS GREAT";
;;	result = [0, 0, 0, 0, 0];
;;	len = 0;
;;
;;	a = 0; // index of 'a' occurrences in result array
;;	e = 1; // index of 'e' occurrences in result array
;;	i = 2; // index of 'i' occurrences in result array
;;	o = 3; // index of 'o' occurrences in result array
;;	u = 4; // index of 'u' occurrences in result array
;;
;;	while (string[len] != '\0') {
;;		if (string[len] == 'a') {
;;			result[a] = result[a] + 1;
;;		} else if (string[len] == 'e') {
;;			result[e] = result[e] + 1;
;;		} else if (string[len] == 'i') {
;;			result[i] = result[i] + 1;
;;		} else if (string[len] == 'o') {
;;			result[o] = result[o] + 1;
;;		} else if (string[len] == 'u') {
;;			result[u] = result[u] + 1;
;;		}
;;
;;		len = len + 1;
;;	}
;;


.orig x3000



;; put your code here
		
		
		AND R2, R2, #0		; len = 0


WHILE	LD R0, STRING
		ADD R3, R0, R2		; address of string[len]
		LDR R3, R3, #0		; value of string[len]
		ADD R7, R3, #0		; see if string[len] == 0
		BRz PASS			; if string[len] == 0, end loop

		LD R4, A
		LD R0, STRING
		NOT R4, R4
		ADD R4, R4, #1
		ADD R4, R4, R3
		BRz ADDA

		LD R4, E
		LD R0, STRING
		NOT R4, R4
		ADD R4, R4, #1
		ADD R4, R4, R3
		BRz ADDE

		LD R4, I
		LD R0, STRING
		NOT R4, R4
		ADD R4, R4, #1
		ADD R4, R4, R3
		BRz ADDI

		LD R4, O
		LD R0, STRING
		NOT R4, R4
		ADD R4, R4, #1
		ADD R4, R4, R3
		BRz ADDO

		LD R4, U
		LD R0, STRING
		NOT R4, R4
		ADD R4, R4, #1
		ADD R4, R4, R3
		BRz ADDU

		BR ALWAYS

ADDA	LD R1, ANSWER
		ADD R5, R1, #0		; addr result[a]
		LDR R5, R5, #0		; value of result[a]
		ADD R5, R5, #1		; result[a] + 1
		LD R1, ANSWER
		ADD R1, R1, #0
		STR R5, R1, #0
		BR ALWAYS

ADDE	LD R1, ANSWER
		ADD R5, R1, #1		; addr result
		LDR R5, R5, #0		; value of result
		ADD R5, R5, #1		; result + 1
		LD R1, ANSWER
		ADD R1, R1, #1
		STR R5, R1, #0
		BR ALWAYS

ADDI	LD R1, ANSWER
		ADD R5, R1, #2		; addr result
		LDR R5, R5, #0		; value of result
		ADD R5, R5, #1		; result + 1
		LD R1, ANSWER
		ADD R1, R1, #2
		STR R5, R1, #0
		BR ALWAYS

ADDO	LD R1, ANSWER
		ADD R5, R1, #3		; addr result
		LDR R5, R5, #0		; value of result
		ADD R5, R5, #1		; result + 1
		LD R1, ANSWER
		ADD R1, R1, #3
		STR R5, R1, #0
		BR ALWAYS

ADDU	LD R1, ANSWER
		ADD R5, R1, #4		; addr result
		LDR R5, R5, #0		; value of result
		ADD R5, R5, #1		; result + 1
		LD R1, ANSWER
		ADD R1, R1, #4
		STR R5, R1, #0
		BR ALWAYS

ALWAYS	ADD R2, R2, #1		; len++
		BR WHILE

PASS	HALT


A .fill x41    ;; A in ASCII
E .fill x45
I .fill x49
O .fill x4F
U .fill x55

;;NOTE: Make sure to fill in the ASCII values
;;for the rest of the vowels here!!


STRING .fill x4000
ANSWER .fill x4100
.end

.orig x4000
.stringz "A TEN OUT OF TEN IS GREAT"
.end

.orig x4100
.fill 0
.fill 0
.fill 0
.fill 0
.fill 0
.end