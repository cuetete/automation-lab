;//###########################################################################
;//
;//  Ver  |   date	  |   name   | Description of changes
;// ===== |===========|=======================================================
;//  1.00 |2011.08.22 |          | 
;//  	  | 		  |		 	 | 
;//       |           |      	 | 
;//###########################################################################
	.def	start;	;.def defined in the current module, references in other modules						
					;.ref referenced in the current module defined in other modules
					;.global contain both above 

;//###################################################################
;//Defined Functions	
;//###################################################################

;//###################################################################
;//Definition of variables
	.bss	var,64,1,1	;Open save space
	.def	x 
	.def	buf

;//Defined shift variables
x	.set	var+0
buf	.set	var+6
;//###################################################################
	.text

add:
	ADDB	SP,#4			;The stack pointer plus 4
	MOV		*-SP[2],AH		;Fed value (SP-2) to AH
	MOV		*-SP[1],AL		;Fed value (SP-1) to AL

	MOV		AL,*-SP[2]		;Fed value (SP-2) to AL
	ADD		AL,*-SP[1]		;(SP-1) added to the AL value
	MOV		*-SP[3],AL		;Fed value (SP-3) to AL

	SUBB	SP,#4			;Restore SP pointer
	LRET

start:
	MOVW	DP,#x			;Loading DP pointer
	MOV		@x,#0x8			;x=0x8

	MOVW	DP,#buf
	MOV		@buf,#0x1		;buf[0]=0x1
	MOVW	DP,#buf+1
	MOV		@buf+1,#0x2		;buf[1]=0x2
	MOVW	DP,#buf+2
	MOV		@buf+2,#0x3		;buf[2]=0x3
	MOVW	DP,#buf+3
	MOV		@buf+3,#0x4		;buf[3]=0x4

	MOV		AL,@buf+1		;The contents of buf[1] into AL
	MOV		AH,@buf+2		;The contents of buf[2] into AH
	LC		add				;Call add function
	MOV		@x,AL			;The value of the AL to x

LOOP:
	B		LOOP,UNC

	.END
