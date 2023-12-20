;;=======================================
;; CS 2110 - Summer 2021
;; HW6 - Recursive Greatest Common Denominator
;;=======================================
;; Name: Que Le
;;=======================================

;; In this file, you must implement the 'gcd' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in Complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'gcd' label.


.orig x3000
HALT

gcd
;; See the PDF for more information on what this subroutine should do.
;;
;; Arguments of GCD: integer a, integer b
;;
;; Pseudocode:
;; gcd(int a, int b) {
;;     if (a == b) {
;;         return a;
;;     } else if (a < b) {
;;         return gcd(b, a);
;;     } else {
;;         return gcd(a - b, b);
;;     }
;; }


;; YOUR CODE HERE
	ADD R6, R6, -4          ;make room for return value, return address, old frame pointer, and 1 local
	STR R7, R6, 2           ;save return address in the space we made it
	STR R5, R6, 1           ;save R5 in space for the old frame pointer
	ADD R5, R6, 0           ;save R5 to the frame pointer of the activation record
	ADD R6, R6, -5          ;make room for saving registers
	STR R0, R5, -1          
	STR R1, R5, -2 
	STR R2, R5, -3
	STR R3, R5, -4
	STR R4, R5, -5

    LDR R0, R5, 4
    LDR R1, R5, 5

    NOT R2, R1
    ADD R2, R2, 1           ;R2 = -B
    ADD R2, R2, R0          ;R2 = A-B
    BRZ IF
    BRN ELSEIF
    BRP ELSE
    BR  TEARDOWN


IF          LDR R0, R5, 4
            STR R0, R5, 3
            BR TEARDOWN

ELSEIF      ADD R6, R6, -2
            LDR R1, R5, 5   ; B
            STR R1, R6, 0
            LDR R0, R5, 4   ; A
            STR R0, R6, 1
            JSR gcd
            LDR R2, R6, 0
            STR R2, R5, 3
            BR TEARDOWN

ELSE        ADD R6, R6, -2
            LDR R1, R5, 5   ; B
            LDR R0, R5, 4   ; A
            NOT R3, R1
            ADD R3, R3, 1
            ADD R3, R0, R3
            STR R3, R6, 0
            STR R1, R6, 1
            JSR gcd
            LDR R2, R6, 0
            STR R2, R5, 3
            BR TEARDOWN

;stack teardown and return
TEARDOWN    LDR R4, R5, -5	; Restore R4
	        LDR R3, R5, -4	; Restore R3
	        LDR R2, R5, -3	; Restore R2
	        LDR R1, R5, -2	; Restore R1
	        LDR R0, R5, -1	; Restore R0
            ADD R6, R5, 0   ;Reset stack pointer to frame pointer (R6 = R5)
            LDR R5, R6, 1   ;Restore old frame pointer to R5
            LDR R7, R6, 2   ;Restore return address to R7
            ADD R6, R6, 3   ;Reallocate space for local, old frame pointer and return address
            RET

; Needed by Simulate Subroutine Call in Complx
STACK .fill xF000
.end