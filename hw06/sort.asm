;;=============================================================
;;CS 2110 - Summer 2021
;;Homework 6 - Recursive Insertion Sort
;;=============================================================
;;Name: Que Le
;;=============================================================

;; In this file, you must implement the 'SORT' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff: don't run
;; this directly by pressing 'RUN' in complx, since there is nothing put at
;; address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'sort' label.

.orig x3000
HALT

;;Pseudocode (see PDF for explanation)
;;  arr: memory address of the first element in the array
;;  n: integer value of the number of elements in the array
;;    sort(arr, n) {
;;        // base case
;;        if (n <= 1)
;;            return;
;;      
;;        //first, we sort the first n-1 elements
;;        sort(arr, n-1);
;;      
;;        //now, we need to insert the last element where it belongs in the array
;;        //when subroutine returns, first n-1 elements have been sorted
;;        last = arr[n-1];
;;        j = n-2;
;;      
;;        //if an element is greater than 'last', we move it up by one space in the array
;;        while (j >= 0 && arr[j] > last) {
;;            arr[j+1] = arr[j];
;;            j--;
;;        }
;;
;;        arr[j+1] = last;
;;    }

;;YOUR CODE HERE
sort
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

	LDR R0, R5, 5	; R0 = N
	ADD R0, R0, -1	; N - 1
	BRNZ TEARDOWN

	;; sort(arr, n-1);
	ADD R6, R6, -2
	LDR R0, R5, 5	; R0 = N
	ADD R0, R0, -1	; N - 1
	STR R0, R6, 1
	LDR R1, R5, 4	; R1 = ARR
	STR R1, R6, 0
	JSR sort

	;; last = arr[n-1];
	LDR R0, R5, 5	; R0 = N
	ADD R0, R0, -1	; N - 1
	LDR R1, R5, 4	; R1 = ARR
	ADD R1, R1, R0	; R1 = ARR[N - 1]
	LDR R2, R1, #0	; R2 = last, last =  ARR[N - 1]
	;; j = n-2;
	LDR R0, R5, 5	; R0 = N
	ADD R3, R0, -2	; J = N - 2


WHILE	
	;; R3 = J, R2 = LAST
	;;	while (j >= 0 && arr[j] > last) {
	ADD R3, R3, 0
	BRN ENDWHILE
	LDR R1, R5, 4	; R1 = ARR
	ADD R1, R1, R3	; R1 = ARR [J]
	LDR R4, R1, 0	; VALUE OF ARR [J]
	NOT R0, R2
	ADD R0, R0, 1
	ADD R0, R0, R4	; ARR[J] - LENGTH <= 0
	BRnz ENDWHILE

	;; arr[j+1] = arr[j];
	ADD R4, R3, 1	; j+1;
	LDR R1, R5, 4	; R1 = ARR
	ADD R0, R1, R4	; R0 = ARR [J + 1]
	LDR R1, R5, 4	; R1 = ARR
	ADD R1, R1, R3	; R1 = ARR [J]
	LDR R4, R1, 0	; VALUE OF ARR [J]
	STR R4, R0, 0	; ARR [J + 1] = ARR [J]
	ADD R3, R3, -1	; j--;
	BR WHILE

ENDWHILE
	;; arr[j+1] = last
	ADD R3, R3, 1	; J + 1
	LDR R1, R5, 4	; R1 = ARR
	ADD R1, R1, R3	; R1 = ARR [J + 1]
	STR R2, R1, #0	; ARR [J + 1] = LAST

TEARDOWN
	LDR R4, R5, -5	; Restore R4
	LDR R3, R5, -4	; Restore R3
	LDR R2, R5, -3	; Restore R2
	LDR R1, R5, -2	; Restore R1
	LDR R0, R5, -1	; Restore R0
	ADD R6, R5, 0   ;Reset stack pointer to frame pointer (R6 = R5)
	LDR R5, R6, 1   ;Restore old frame pointer to R5
	LDR R7, R6, 2   ;Restore return address to R7
	ADD R6, R6, 3   ;Reallocate space for local, old frame pointer and return address
	RET


;; used by the autograder
STACK .fill xF000
.end

;; USE FOR DEBUGGING IN COMPLEX
;; load array at x4000 and put the length as 7

;; ARRAY
.orig x4000
    .fill 4
    .fill -9
    .fill 0
    .fill -2
    .fill 9
    .fill 3
    .fill -10
.end