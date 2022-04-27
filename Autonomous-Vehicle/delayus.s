  
; ////////////////////////////////////
; // SOURCE FILE   delayus.s          //
; ////////////////////////////////////
  
;/**************************************************************************
; *  Autonom Eingebettete Systeme    (AEiSy)                               *  
; *                                                                        *
; **************************************************************************
; *  PROJECT       MC Mobile  									   		  *
; *  MODULE        delayus.c               	                    		  *
; *  REVISION      1.0                                                    *
; *  AUTHOR        Simon Hoffmann & Aleksei Svatko              		  *
; **************************************************************************
; *  PURPOSE:                                                              *
; *       Delay function in us          								   *
; *                                                                        *
; **************************************************************************
; *  CHANGE HISTORY:                                                       *
; *   Date  		       Author      						 Description   *
; *   26.04.2022  	   S. Hoff & A. Svatko     			 creation          *
; *                                                                        *
; *************************************************************************/
  
  
  AREA  DELAY, CODE, READONLY    

  THUMB


delayus FUNCTION        ; start of function 
    EXPORT delayus 
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
	