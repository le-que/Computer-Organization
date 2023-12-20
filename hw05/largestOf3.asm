;;=============================================================
;; CS 2110 - Summer 2021
;; Homework 5 - Largest of 3 Integers
;;=============================================================
;; Name:Que Le
;;=============================================================

;; Pseudocode (see PDF for explanation):
;;
;; a = (argument 1);
;; b = (argument 2);
;; c = (argument 3);
;; ANSWER = 0;
;;
;; if (a > b) {
;;   if (a > c) {
;;      ANSWER = a;
;;	 } else {
;;       ANSWER = c;
;;   }
;; } else {
;;     if (b > c) {
;;       ANSWER = b;
;;     } else {
;;         ANSWER = c;
;;     }
;; }

.orig x3000

;; put your code here
		LD R1, A		; set R1 to A
		LD R2, B		; set R2 to B
		LD R3, C		; set R3 to C
		NOT R5, R2		
		ADD R5, R5, #1	; R5 = -R2
		ADD R5, R1, R5	; R5 = R1 - R2
		BRnz BC			; if A < B
		BRnzp AC		; if A > B

BC		NOT R6, R3
		ADD R6, R6, #1
		ADD R6, R2, R6
		BRnz ANSC
		BRnzp ANSB

AC		NOT R4, R3
		ADD R4, R4, #1
		ADD R4, R1, R4
		BRnz ANSC
		BRnzp ANSA

ANSA	ST R1, ANSWER
		BR PASS

ANSB	ST R2, ANSWER
		BR PASS

ANSC	ST R3, ANSWER
		BR PASS

PASS	HALT

A .fill 18
B .fill 22
C .fill 25

ANSWER .blkw 1

.end
