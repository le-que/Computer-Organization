*;;=============================================================
;; Name: Que Le
;;=============================================================

;; Pseudocode (see PDF for explanation)
;;
;; x = 0; // first index of ARR_X
;; y = 0; // first index of ARR_RES
;; //assume ARR_X and ARR_RES will be arrays of ints and ARR_X will be of even length
;; 
;; sum = 0; //initial sum
;; 
;; while (x < LENGTH_X) {
;;	if (x % 2 == 0) {
;;		//if we are at an even index, update sum
;;		sum = sum + ARR_X[x];
;;	} else {
;;		//if we are at odd index, copy the value from ARR_X to ARR_RES
;;		ARR_RES[y] = ARR_X[x];
;;		y++;
;;	}
;;
;;	x++;
;; }

;; lastly, place sum of evens at the end of ARR_RES
;; ARR_RES[LENGTH_RES - 1] = sum;

;; the final array should be in ARR_RES

.orig x3000

;;put your code here
			AND R0, R0, #0	; x = 0
			AND R1, R1, #0	; y = 0
			AND R2, R2, #0	; sum = 0
			
WHILE		LD R3, LENGTH_X	; R3 = length_x
			NOT R3, R3
			ADD R3, R3, #1
			ADD R3, R3, R0
			BRzp ANSWER		; if x - length_x >= 0

			AND R7, R0, #1	; check if x is odd
			BRp COPY		; else
			BR ADDSUM		; if (x % 2 == 0)
			
ADDSUM		LD R4, ARR_X	; addr of ARR_x
			ADD R6, R4, R0	; R6 = addr ARR_X[x]
			LDR R6, R6, #0	; R6 = value ARR_X[x]
			ADD R2, R2, R6	; add to sum
			ADD R0, R0, #1	; x++
			BR WHILE		; go back to while loop

COPY		LD R4, ARR_X	; addr of ARR_x
			ADD R6, R4, R0	; get address of ARR_X[x]
			LDR R6, R6, #0	; R6 = value of ARR_X[x]
			LD R5, ARR_RES
			ADD R5, R5, R1	; ARR_RES[y]
			STR R6, R5, #0	; ARR_RES[y] = ARR_X[x];
			ADD R1, R1, #1	; y++
			ADD R0, R0, #1	; x++
			BR WHILE		; go back to while loop

ANSWER		LD R7, LENGTH_RES
			ADD R7, R7, #-1	; LENGTH_RES - 1
			LD R5, ARR_RES
			ADD R5, R5, R7	; ARR_RES[LENGTH_RES - 1]
			STR R2, R5, #0	; ARR_RES[LENGTH_RES - 1] = sum
			HALT

ARR_X      .fill x4000
ARR_RES    .fill x4100

LENGTH_X   .fill 4
LENGTH_RES .fill 3

.end

.orig x4000
.fill 1
.fill 5
.fill 10
.fill 11
.end
