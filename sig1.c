// Sigmoid http://www.cs.bham.ac.uk/~jxb/INC/nn.html
// [bri@localhost neural]$ gcc -o sig1.exe sig1.c -lm
// [bri@localhost neural]$ ./sig1.exe
// Will always return a number between 0 and 1


#include <stdio.h>
#include <math.h>

int main(void)
{
double in = 0.731059 * (0.557819 + 0.8) * 0.774380 ; //1.233212 ; //-0.53 ; // (0.731059*0.3)+(0.785835*0.5)+(0.689974*0.9) ;
double out = 0 ;
double sigderivative = 0 ;
	
	out = 1.0/(1.0 + exp(-in));         /* Out = Sigmoid(In) */
	
	printf("in = %lf Out = %lf\n", in, out) ;
	
	sigderivative = out * (1.0 - out) ;
	printf("Sigmoid Derivative = %lf\n", sigderivative) ;

return 0 ;
}


