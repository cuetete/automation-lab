
extern int asmfunc(int a);
extern int var;
int gvar=2;

void main(void)
{
	int i=4;
	i=asmfunc(i);	//function asmfunc() return i+5
	var=6;
	i=i+var;

	while(1);
}
