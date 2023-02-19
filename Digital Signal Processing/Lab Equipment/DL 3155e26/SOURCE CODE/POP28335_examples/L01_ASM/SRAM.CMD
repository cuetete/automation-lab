-stack 0x400
-e start
MEMORY
{
PAGE 0 : 
   PRAMH0     : origin = 0x3f8000, length = 0x001200       
         
PAGE 1 : 
   /* SARAM                     */     
   RAMM0    : origin = 0x000000, length = 0x000400
   RAMM1    : origin = 0x000400, length = 0x000400
   /* SARAM                    */     
   DRAMH0     : origin = 0x3f9200, length = 0x000a00          
}
 
 
SECTIONS
{
   /* Allocate program areas: */
   .reset           : > PRAMH0,      PAGE = 0
   .text            : > PRAMH0,      PAGE = 0
   .cinit           : > PRAMH0,      PAGE = 0

   /* Allocate data areas: */
   .stack           : > RAMM1,       PAGE = 1
   .bss             : > DRAMH0,      PAGE = 1
   .ebss            : > DRAMH0,      PAGE = 1
   .const           : > DRAMH0,      PAGE = 1
   .econst          : > DRAMH0,      PAGE = 1      
   .sysmem          : > DRAMH0,      PAGE = 1
}
