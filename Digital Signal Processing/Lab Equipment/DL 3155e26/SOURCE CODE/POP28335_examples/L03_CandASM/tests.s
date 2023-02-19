



;//###########################################################################
;//
;//  Ver  |   date	  |   name   | Description of changes
;// ===== |===========|=======================================================
;//  1.00 |2003.03.22 |KongDebao | 
;//  	  | 		  |		 	 | 
;//       |           |      	 | 
;//###########################################################################

		.global _gvar		;must be have underlined before the variable name
		.global _asmfunc	;Declared as a global variable
		.bss	_var,1		;apply a word space for var
		.global _var		;Declared as external variables
    
_asmfunc:
    	MOVZ	DP,#_gvar
		ADDB	AL,#5
		MOV		@_gvar,AL
		LRETR

		.end