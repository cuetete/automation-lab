#include <stdio.h>
#include <math.h>

#define PI 3.1415926

float sindat[1024];

float sin_fun(int i)
{
	return 100*sin(i/1024.0*2*PI);
}

void main(void)
{
	int i=0;
	for(i=0;i<1024;i++)
		sindat[i]=sin_fun(i);
}
