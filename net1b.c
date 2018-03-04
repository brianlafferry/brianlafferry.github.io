// [bri@localhost gitcola]$ gcc -o net1a.exe net1a.c -lm
// ./net1a.exe

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

////////////////////////////////////// Globals ///////////////////////////////////////////////////////////////////
#define inputs 2
#define outputs 1
#define hidden 3 
#define weights 9  //(inputs * hidden) + (hidden * outputs)  ;	//  9 Weights 
#define neurontot 6  // inputs + hidden + outputs = Total number of neurons in the network
#define neuronup 4 // 4 upper level neurons (non-input)

////////////////////////////////////// Prototypes ////////////////////////////////////////////////////////////////
double deriv(double, int) ;
void feedfwd(double sums[], double outs[], double wt[][2], double inout[]) ;
void backprop(double sums[], double outs[], double wt[][2], double inout[]) ;



int main(void)
{
	/*
	Name:  	 	main
	Purpose:  	This version will initialize a neural network, and calculate weight changes for 1 epoch
	Arguments:	None
	Called By: 	None
	Calls To: 	feedfwd
				backprop
	Returns: 	None 	
	Pseudocode:	Initialize the weights
				Call feedfwd
				Call backprop
				print results
	*/
double sums[neuronup] ;	// 4
double outs[neuronup] ;	// 4
double wt[weights][2]  ;	//  9 Weights 
double inout[3] = {1, 1, 0} ; // 2 inputs and the target
double randnum = 0 ;
double prevout = 0 ;
int randint = 0 ;
int i = 0 ;
int j = 0 ;
int k = 0 ;
int output = 0 ;
	
	srand(time(NULL)) ;
	
	/*
	wt[0][1] = 0.8 ;
	wt[1][1] = 0.4 ;
	wt[2][1] = 0.3 ;
	wt[3][1] = 0.2 ;
	wt[4][1] = 0.9 ;
	wt[5][1] = 0.5 ;
	wt[6][1] = 0.3 ;
	wt[7][1] = 0.5 ;
	wt[8][1] = 0.9 ;
	

	wt[6][0] = 0 ;
	wt[7][0] = 0 ;
	wt[8][0] = 0 ;
	*/
	
	
	printf("Inputs: %.0lf	%.0lf\n", inout[0], inout[1]) ;
	printf("Expected Output: %.0lf\n", inout[2]) ;
	
	for (k=0; k<1000; k++)
	{
		randnum = (double) rand() ;
		randint = randnum ;
		
		for (i=0; i<9; i++)
		{
			
			while (randnum > 1)
				randnum /= 10 ;
			wt[i][1] = randnum ;
			//printf("%lf\n", randnum) ;
			randnum = (double)rand() ;
		}
		
		output = 0 ;
		for (j=0; j<1000; j++)
		{
			feedfwd(sums, outs, wt, inout) ;
			backprop(sums, outs, wt, inout) ;
			
			if (j % 1 == 0 && output == 0 && outs[3] > 0.93)
			{
				printf("prevout: %lf	out=%lf\n", prevout, outs[3]) ;
				printf("Output: %lf\n", outs[3]) ;
				printf("Margin of error %lf\n", inout[2] - outs[3]) ;
				printf("  Old Weight | New Weight\n  -----------------------\n") ;
				for (i=0; i<weights; i++)
					if (wt[i][1] > 9.9)
						printf("    %.1lf | %lf\n", wt[i][1], wt[i][0]) ;
					else
						printf("    %.1lf	     | %lf\n", wt[i][1], wt[i][0]) ;
				
				printf("\n") ;
				output = 1 ;
				j = 1000001 ;
			}
			
			if (prevout > outs[3] || outs[3] > 400)
				j = 1000001 ;
				
			if (prevout == outs[3])
				j = 1000001 ;
			else
			{
				prevout = outs[3] ;			
				memmove(&wt[0][1], &wt[0][0], 9*sizeof(double)) ;
			}
		}
		
		if (outs[3] > 0.93)
		{
			printf("%d loops\n", j) ;
			printf("Output: %lf\n", outs[3]) ;
			printf("Margin of error %lf\n", inout[2] - outs[3]) ;
			printf("  Old Weight | New Weight\n  -----------------------\n") ;
			for (i=0; i<weights; i++)
				printf("    %.1lf	     | %lf\n", wt[i][1], wt[i][0]) ;

			printf("\n") ;
			outs[3] = 0 ;
		}
	}


		output = 0 ;
		for (j=0; j<1000; j++)
		{
			feedfwd(sums, outs, wt, inout) ;
			backprop(sums, outs, wt, inout) ;
			
			if (j % 1 == 0 && output == 0 && outs[3] > 0.93)
			{
				printf("prevout: %lf	out=%lf in the second round\n", prevout, outs[3]) ;
				printf("Output: %lf\n", outs[3]) ;
				printf("Margin of error %lf\n", inout[2] - outs[3]) ;
				printf("  Old Weight | New Weight\n  -----------------------\n") ;
				for (i=0; i<weights; i++)
					if (wt[i][1] > 9.9)
						printf("    %.1lf | %lf\n", wt[i][1], wt[i][0]) ;
					else
						printf("    %.1lf	     | %lf\n", wt[i][1], wt[i][0]) ;
				
				printf("\n") ;
				output = 1 ;
				//j = 1000001 ;
			}
			
			//if (prevout > outs[3] || outs[3] > 400)
			if (prevout > outs[3])
				j = 1000001 ;
				
			if (prevout == outs[3])
				j = 1000001 ;
			else
			{
				prevout = outs[3] ;			
				memmove(&wt[0][1], &wt[0][0], 9*sizeof(double)) ;
			}
		}
		
			printf("%d loops at the end\n", j) ;
			printf("Output: %lf\n", outs[3]) ;
			printf("  Old Weight | New Weight\n  -----------------------\n") ;
			for (i=0; i<weights; i++)
				printf("    %.1lf	     | %lf\n", wt[i][1], wt[i][0]) ;

			printf("\n") ;
			outs[3] = 0 ;
	

	printf("Finished %d iterations in the second part\n", j) ;
return 0 ;
}



void backprop(double sums[neuronup], double outs[neuronup], double wt[weights][2], double inout[neuronup])
{
	/*
	Name:		backprop
	Purpose:	Calculate network weight adjustments
	Arguments:	sums[]: an array to hold the neuron input sums
				outs[]: an array to hold the neuron outputs
				wt[][]: a 2d array to hold the new weights [x][0] and old weights [x][1]
				inout[]: 2 network inputs and 1 network expected output
	Called By:	main
	Calls To: 	deriv
	Returns:	None
	Pseudocode:	Calculate Margin of Error
				Calculate Delta Output Weights
				Calculate hidden weight changes
				Calculate input weight chnges
	*/

double margerror = 0 ;	// Margin of Error
double deltaoutwt = 0 ;	// Delta Output Weight
double deltainwt = 0 ;

int i = 0 ;
int j = 0 ;
int k = 0 ;

	margerror = inout[2] - outs[3] ;	// Calculate Margin of Error
	deltaoutwt = deriv(sums[3], 0) * margerror ;	// Calculate Delta Output Weights
	
	j = 0 ;
	for (i=6; i<9; i++)		// Calculate hidden weight changes
		wt[i][0] = wt[i][1] - (deltaoutwt / outs[j++]) ;
		
	j = 3 ;	
	k = 6 ;
	for (i=0; i<6; i++)		// Calculate input weight chnges
	{
		deltainwt = deltaoutwt / wt[6][1] * deriv(sums[0], 0) ;
		wt[i][0] = wt[i][1] - deltaoutwt / wt[k][1] * deriv(sums[i], 0) ;
		wt[j][0] = wt[j][1] - deltaoutwt / wt[k][1] * deriv(sums[i], 0) ;
		j++ ;
		k++ ;
	}
}




double deriv(double in, int selection)
{
	/*
	Name:  		deriv
	Purpose: 	Depending on parameters, returns either a derivative or derivative inverse
	Arguments:	in
				selection
	Called By: 	feedfwd
				backprop
	Calls To: 	math.h
	Returns: 	double 	
	Pseudocode:	Calculate a derivative
				if second parameter = 1
					return derivative
				else
					calculate inverse
					return inverse
	*/

double sigmoid = 0 ;
double siginverse = 0 ;
	
	sigmoid = 1.0/(1.0 + exp(-in));         /* sigmoid = Sigmoid(in) */
	
	//printf("in = %lf sigmoid = %lf\n", in, sigmoid) ;
	
	siginverse = sigmoid * (1.0 - sigmoid) ;
	//printf("Sigmoid Inverse = %lf\n", siginverse) ;
	
	if (selection == 1)
		return (sigmoid) ;
	else
		return (siginverse) ;
}


void feedfwd(double sums[neuronup], double outs[neuronup], double wt[weights][2], double inout[neuronup])
{
	/*
	Name:		feedfwd
	Purpose:	Calculate sums and outputs of network
	Arguments:	sums[]: an array to hold the neuron input sums
				outs[]: an array to hold the neuron outputs
				wt[][]: a 2d array to hold the new weights [x][0] and old weights [x][1]
				inout[]: 2 network inputs and 1 network expected output
	Called By:	main
	Calls To: 	deriv
	Returns:	None	
	Pseudocode:	Calculate hidden layer sums
				Calculate hidden outs
				Calculate output neuron input sum
				Calculate network output
	*/
int i = 0 ;
int j = 0 ;
int k = 0 ;

	//printf("wt[1]\n") ;
	//for (i=0; i<weights; i++)
	//	printf("%lf	", wt[i][1]) ;
	//printf("\n") ;
	
	//printf("\ninout	%lf	%lf	%lf\n\n", inout[0], inout[1], inout[2]) ;
	
	j = 0 ;
	k = 3 ;
	for (i=0; i<hidden; i++)	// Calculate hidden layer sums
	{
		sums[i] = (wt[j++][1] * inout[0]) + (wt[k++][1] * inout[1]) ;
		//printf("(%lf * %lf) + (%lf * %lf) = %lf\n", wt[1][j], inout[0], wt[1][k], inout[1], sums[i]) ;
	}

	//printf("sums\n") ;
	//for (i=0; i<hidden; i++)
	//	printf("%lf	", sums[i]) ;
	//printf("\n\n") ;
	
	// Calculate hidden outs
	for (i=0; i<hidden; i++)
		outs[i] = deriv(sums[i], 1) ;
	
	// Calculate output neuron input sum
	sums[3] = (outs[0] * wt[6][1]) + (outs[1] * wt[7][1]) + (outs[2] * wt[8][1]) ;
	
	//printf("In feedfwd sums[3] = %lf\n", sums[3]) ;
	// Calculate network output
	outs[3] = deriv(sums[3], 1) ;
	
}











