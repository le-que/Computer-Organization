;; Timed Lab 3
;; Student Name:Que Le

;; Please read the PDF for full directions.
;; The pseudocode for the program you must implement is listed below; it is also listed in the PDF.
;; If there are any discrepancies between the PDF's pseudocode and the pseudocode below, notify a TA on Piazza quickly.
;; However, in the end, the pseudocode is just an example of a program that would fulfill the requirements specified in the PDF.

;; Pseudocode:
;;
;; SQUARE(x) {
;;     int sum = 0;
;;     if (x < 0){
;;          x = -1*x;
;;     }
;;     for (int i = 0; i < x; i++){
;;         sum+=x;
;;     }
;;     return sum; 
;; }
;;
;;
;;
;; DIV(x, y) {
;;     if (y > x) {
;;         return 0;
;;     } else {
;;         return 1 + DIV(x - y, y);
;;     }
;; }
;;
;;
;; MAP(array, length) {
;;     i = 0;
;;     sumEvens = 0;
;;     sumOdds = 0;   
;;     while (i < length) {
;;         element = arr[i];
;;         if (i & 1 == 0) {
;;             result = SQUARE(element);
;;             sumEvens += result; 
;;         } else {
;;             result = DIV(element, i);
;;             sumOdds += result; 
;;         }
;;         arr[i] = result;
;;         i++;
;;     }
;; }

.orig x3000
HALT

STACK .fill xF000

; DO NOT MODIFY ABOVE


; START SQUARE SUBROUTINE
SQUARE


    ; STACK BUILDUP
    ADD R6, R6, -4
    STR R5, R6, 1
    STR R7, R6, 2
    ADD R5, R6, 0
    ADD R6, R6, -5
    STR R0, R6, 4
    STR R1, R6, 3
    STR R2, R6, 2
    STR R3, R6, 1
    STR R4, R6, 0

    LDR R0, R5, #4 ;Load parameter
    
    AND R2, R2, 0 ;Initialize Total
    ADD R1, R0, #0 ;Initialize Counter

    brz ENDPOW
    brp STARTPOW 
    NOT R0, R0 ; Make sure that the counter and parameter are positive
    ADD R0, R0, #1
    ADD R1, R0, 0

    STARTPOW brnz ENDPOW
    ADD R2, R2, R0
    ADD R1, R1, -1
    brnzp STARTPOW 

    ENDPOW STR R2, R5, 3; TEARDOWN
    LDR R4, R6, 0
    LDR R3, R6, 1
    LDR R2, R6, 2
    LDR R1, R6, 3
    LDR R0, R6, 4
    ADD R6, R6, 5
    LDR R5, R6, 1
    LDR R7, R6, 2
    ADD R6, R6, 3


RET
; END SQUARE SUBROUTINE




; START DIV SUBROUTINE
DIV


    ; STACK BUILDUP
    ADD R6, R6, -4
    STR R5, R6, 1
    STR R7, R6, 2
    ADD R5, R6, 0
    ADD R6, R6, -5
    STR R0, R6, 4
    STR R1, R6, 3
    STR R2, R6, 2
    STR R3, R6, 1
    STR R4, R6, 0

    LDR R0, R5, #4 ; R0 = x
    LDR R1, R5, #5 ; R1 = y
    NOT R2, R1
    ADD R2, R2, #1 ; R2 = -y
    ADD R2, R0, R2 ; R2 = x - y

    BRn BASE_CASE

    ADD R6, R6, -1
    STR R1, R6, 0
    ADD R6, R6, -1
    STR R2, R6, 0
    JSR DIV
    LDR R1, R6, 0
    ADD R1, R1, 1
    ADD R6, R6, 3
    BR RETURN2

    BASE_CASE
    AND R1, R1, 0

    RETURN2
    STR R1, R5, 3
    ; TEARDOWN
    LDR R4, R6, 0
    LDR R3, R6, 1
    LDR R2, R6, 2
    LDR R1, R6, 3
    LDR R0, R6, 4
    ADD R6, R5, 0
    LDR R5, R6, 1
    LDR R7, R6, 2
    ADD R6, R6, 3


RET
; END DIV SUBROUTINE



; START MAP SUBROUTINE
MAP


    ; STACK BUILDUP
    ADD R6, R6, -4
    STR R5, R6, 1
    STR R7, R6, 2
    ADD R5, R6, 0
    ADD R6, R6, -5
    STR R0, R6, 4
    STR R1, R6, 3
    STR R2, R6, 2
    STR R3, R6, 1
    STR R4, R6, 0

    LDR R0, R5, #4 ; R0 = ARRAY
    LDR R1, R5, #5 ; R1 = len
    
    AND R2, R2, 0 ; R2 = i = 0
    
    LD R3, SUMEVENS ;Make sure that SUMODDS and SUMEVENS memory locations are intialized to 0
    STR R2, R3, 0
    LD R3, SUMODDS
    STR R2, R3, 0


    WHILE 
    
    NOT R3, R1
    ADD R3, R3, 1 ; R3 = -len
    ADD R3, R2, R3 ; R3 = i - len
    BRzp ENDWHILE
    ADD R3, R0, R2 
    LDR R3, R3, 0 ; R3 = arr[i]
    ADD R6, R6, -1
    STR R3, R6, 0 ; push x to stack
    AND R4, R2, 1
    BRnp ELSE

    JSR SQUARE
    LDR R4, R6, 0 ; R4 = result
    
    LDR R3, R5, #4 ; R0 = ARRAY
    ADD R3, R3, R2
    STR R4, R3, #0
    
    ADD R6, R6, 2 ; Restore stack
    LDI R3, SUMEVENS ;Load current sum
    ADD R4, R3, R4
    LD R3, SUMEVENS
    STR R4, R3, 0
    BR ENDIF

    ELSE
    STR R2, R6, 0
    ADD R6, R6, -1
    STR R3, R6, 0 ; push x to stack
    JSR DIV
    LDR R4, R6, 0 ; R4 = result
    
    LDR R3, R5, #4 ; R0 = ARRAY
    ADD R3, R3, R2
    STR R4, R3, #0

    ADD R6, R6, 3 ; Restore stack
    LDI R3, SUMODDS ;Load current sum
    ADD R4, R3, R4
    LD R3, SUMODDS
    STR R4, R3, 0
    BR ENDIF
    
    ENDIF
    ADD R2, R2, 1
    BR WHILE
    ENDWHILE

    ; TEARDOWN
    LDR R4, R6, 0
    LDR R3, R6, 1
    LDR R2, R6, 2
    LDR R1, R6, 3
    LDR R0, R6, 4
    ADD R6, R5, 0
    LDR R5, R6, 1
    LDR R7, R6, 2
    ADD R6, R6, 3



RET
; END MAP SUBROUTINE

; ARRAY FOR TESTING
ARRAY .fill x4000
SUMEVENS .fill x4010
SUMODDS .fill x4011
.end

.orig x4000
.fill -2
.fill 5
.fill 3
.fill 2
.fill -6
.fill 0
.end
