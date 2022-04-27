  
; ////////////////////////////////////
; // SOURCE FILE   delay.s          //
; ////////////////////////////////////
  
;/**************************************************************************
; *  Autonome Eingebettete Systeme    (AEiSy)                              *                                                                                                  *
; **************************************************************************
; *  PROJECT       Basisproject                                            *
; *  MODULE        delay.s                                                 *
; *  REVISION      1.0                                                     *
; *  LAST AUTHOR                                                           *
; *  LAST MODIFIED                                                         *
; *  RESPONSIBLE   Peter Raab                                              *
; **************************************************************************
; *  PURPOSE:                                                              *
; *   Delay of CPU execution; implements an exact time deley of R0 * 1ms   *
; *                                                                        *
; **************************************************************************
; *  REMARKS:                                                              *
; *   SYSCLK = 48 MHz                                                      *
; *                                                                        *
; **************************************************************************
; *  CHANGE HISTORY:                                                       *
; *  Revision   Date          Author      Description                      *
; *     1.0      01.02.2022    P. Raab     creation                        *
; *                                                                        *
; *************************************************************************/
  
  
  AREA  DELAY, CODE, READONLY    

  THUMB


delayms FUNCTION        ; start of function 
    EXPORT delayms 
    PUSH {R1}           ; store used registers

    MOV    R1, #12000    ; = 0.001 s / (4 * 1/48000000Hz)
    MUL    R0, R0, R1
	
    ALIGN  4      ; following instruction to be 32Bit aligned
loop_delay_ms 
    SUB    R0, R0, #1
    CMP    R0, #0
    BNE    loop_delay_ms
    NOP

    POP    {R1}
    BX     lr


    ENDFUNC  ; end of function
    END
		
delayus FUNCTION        ; start of function 
    EXPORT delayms 
    PUSH {R1}           ; store used registers

    MOV    R1, #12    	; = 1 us / (4 * 1/48000000Hz)
    MUL    R0, R0, R1
	
    ALIGN  4      ; following instruction to be 32Bit aligned
loop_delay_us 
    SUB    R0, R0, #1
    CMP    R0, #0
    BNE    loop_delay_us
    NOP

    POP    {R1}
    BX     lr


    ENDFUNC  ; end of function
    END
	