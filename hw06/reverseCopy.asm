;;=============================================================
;; CS 2110 - Summer 2021
;; Homework 6 - Copy a Linked List in Reverse
;;=============================================================
;; Name: Que Le
;;============================================================

;; In this file, you must implement the 'reverseCopy' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff: don't run
;; this directly by pressing 'RUN' in complx, since there is nothing put at
;; address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'reverseCopy' label.

.orig x3000
HALT

;; Pseudocode (see PDF for explanation):
;;
;; Arguments of reverseCopy: Node head
;;
;; reverseCopy(Node head) {
;;     // note that a NULL address is the same thing as the value 0
;;     if (head == NULL) {
;;         return 0;
;;     }
;;     Node next = head.next;
;;     int index = reverseCopy(next);
;;     ARRAY[index] = head.data;
;;     return index + 1;
;; }

;; YOUR CODE HERE
reverseCopy
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

			LDR R0, R5, 4           ; HEAD
			ADD R0, R0, 0
			BRZ IF
			BR ELSE

			;; IF NULL RETURN 0
IF			AND R2, R2, 0
			STR R2, R5, 3
			BR TEARDOWN

ELSE		LDR R4, R0, 0	; Node next = head.next;
			;; int index = reverseCopy(next);
			ADD R6, R6, -1
			STR R4, R6, 0
			JSR reverseCopy
			LDR R3, R6, 0	; INDEX
			;; ARRAY[index] = head.data;
			LD R1, ARRAY
			ADD R1, R1, R3	; ARRAY[index]
			LDR R2, R0, 1	; HEAD data
			STR R2, R1, 0	; ARRAY[index]	= head.data
			;;	return index + 1;
			ADD R3, R3, 1
			STR R3, R5, 3
			BR TEARDOWN

TEARDOWN	LDR R4, R5, -5	; Restore R4
			LDR R3, R5, -4	; Restore R3
			LDR R2, R5, -3	; Restore R2
			LDR R1, R5, -2	; Restore R1
			LDR R0, R5, -1	; Restore R0
			ADD R6, R5, 0	; Restore SP
			LDR R5, R6, 1	; Restore FP
			LDR R7, R6, 2	; Restore RA
			ADD R6, R6, 3	; Pop ra,fp,lv1
			RET 

;; used by the autograder
STACK .fill xF000

;; store data here
ARRAY .fill x5000
.end

;; The following is an example of a small linked list that starts at x4000.
;;
;; The first number (offset 0) contains the address of the next node in the
;; linked list, or zero if this is the final node.
;;
;; The second number (offset 1) contains the data of this node.
.orig x4000
.fill x4008
.fill 5
.end

.orig x4008
.fill x4010
.fill 12
.end

.orig x4010
.fill 0
.fill -7
.end
