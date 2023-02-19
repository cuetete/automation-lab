#include <stdio.h>    
   
#define    Qx    3   
#define    Qy    3    
#define    Qz    3  
  
//in the fixed example,the default value of Q is 3. 
//The range of date is [-4096,4095.875]     

int fixed_add(int x,int y)
{    
	long temp;   
	int  z;
      
	temp=y<<(Qx-Qy);     
	temp+=x;   
	if (Qx>=Qz)
	{   
		z=temp>>(Qx-Qz);   
	}   
	else
	{   
		z=temp<<(Qz-Qx);    
	}    
            
	return z;   
}   
   
int fixed_sub(int x,int y)
{   
	long temp;   
	int  z;  
      
	temp=y<<(Qx-Qy);     
	temp=x-temp;   
	if (Qx>=Qz)
	{   
		z=temp>>(Qx-Qz);   
	}   
   	else 
   	{   
       	z=temp<<(Qz-Qx);    
   	} 
   	   
   	return z;   
}         
   
int fixed_mul(int x,int y)
{   
	long temp;   
   	int  z;   

   	temp=(long)x;   
   	z=(temp*y)>>(Qx+Qy-Qz);   
      
   	return z;   
}  
    
int fixed_div(int x,int y)
{   
	long temp;   
	int  z;   

	temp=(long)x;   
   	z=(temp<<(Qz-Qx+Qy))/y;   
      
   	return z;   
}      
   
double float_add(double x,double y)
{   
	double z;   
   	z=x;     
   	z+=y;   
   	return z; 
}  
   
double float_sub(double x,double y)
{     
    double z;   
   	z=x;     
   	z-=y;   
   	return z;   
}      
   
double float_mul(double x,double y)
{   
   	double z;   
   	z=x;     
   	z*=y;   
   	return z;   
}      
   
double float_div(double x,double y)
{   
   	double z;   
   	z=x;     
   	z/=y;   
   	return z;   
}     
    
int float_fixed(double x)
{   
   	int i;   
   	int n;   
     
   	for(i=0;i<Qx;i++)
   	{   
		x*=2;   
   	}   
   	n=(int)x;   
   	return n;              
}   
     
double fixed_float(int x)
{   
	int i;   
   	double n; 
   	  
   	n=x;   
   	for(i=0;i<Qx;i++)
   	{   
		n/=2;   
	}    
   	return n;            
}   

void main()
{    
    int fix_add=0,fix_sub=0,fix_mul=0,fix_div=0,fix_n=0;   
    double floa_add=0,floa_sub=0,floa_mul=0,floa_div=0,float_n=0; 
       
    for(;;)
    {         
        fix_add=fixed_add(2556,40);   
        fix_sub=fixed_sub(1134,202);   
        fix_mul=fixed_mul(188,188);   
        fix_div=fixed_div(188,18);   
        floa_add=float_add(2.5e3,1.2e3);   
        floa_sub=float_sub(2.0e2,3.0e2);   
        floa_mul=float_mul(2.0e2,3.0e2);   
        floa_div=float_div(2.0e4,2.0e2);   
        fix_n=float_fixed(9.735e1);   
        float_n=fixed_float(1557);   
    }   
} 
