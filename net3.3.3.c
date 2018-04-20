// [bri@localhost gitcola]$ gcc -o net3.3.2.exe $(mysql_config --cflags) net3.3.2.c $(mysql_config --libs) -lm 
// ./net3.3.2.exe

/*

Machine Fedora25
MariaDB Client version 5.0.12-dev
MariaDB Server version: 10.1.26-MariaDB 
Curl 	7.51.0
PhPMyAdmin 4.6.6
gcc version 6.4.1 20170727 (Red Hat 6.4.1-1) (GCC)

- phpMyAdmin SQL Dump
-- version 4.6.6
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Mar 28, 2018 at 11:47 PM
-- Server version: 10.1.26-MariaDB
-- PHP Version: 7.0.23

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

--
-- Database: `fx`
--

-- --------------------------------------------------------

--
-- Table structure for table `oanda`
--

CREATE TABLE `oanda` (
  `pairsid` int(11) NOT NULL,
  `stamp` bigint(20) NOT NULL,
  `bid` double DEFAULT NULL,
  `ask` double DEFAULT NULL,
  `mid` double DEFAULT NULL COMMENT 'All (bid + ask) / 2 ',
  `lo` double DEFAULT NULL,
  `hi` double DEFAULT NULL,
  `open` double DEFAULT NULL,
  `close` double DEFAULT NULL,
) ENGINE=InnoDB DEFAULT CHARSET=latin1;





net3.1 did a good job with 11 inputs, 12 hidden and 1 output neuron.
But it only did one input.

3.3 needs to read the data from a database, and calculate the inputs for training.
MA5 increase%
MA10 Increase%
MA15 Increase%
StdDev Floor Incrrease%
StdDev Ceiling Increase%
Mid increase%
Hi Increase%
Lo Increase%
Open Increase%
Close Increase%

double ann[13][3]
Array data already holds MA5, MA10 and MA15 data
Original data was more of a "ratio" than a percent
average MA5 for minutes -6 thru -1 minute ago / average past five minutes MA5
average MA10 for minutes -11 thru -1 minute ago / average past ten minutes MA10
average MA15 for minutes -16 thru -1 minute ago / average past 15 minutes MA15
All others are just previous reading / present reading
StdDev Floor Incrfease/Decrease
StdDev Ceiling Increase/Decrease
Mid increase/Decrease
Hi Increase/Decrease
Lo Increase/Decrease
Open Increase/Decrease
Close Increase/Decrease
Mid Increase/Decrease

The original data array
sscanf(row[0], "%lf", &ray[0][i]) ;	// Stamp
sscanf(row[1], "%lf", &ray[1][i]) ;	// Mid
sscanf(row[2], "%lf", &ray[2][i]) ;	// bid will always be < ask
sscanf(row[3], "%lf", &ray[3][i]) ;	// ask
sscanf(row[4], "%lf", &ray[4][i]) ;	// Open
sscanf(row[5], "%lf", &ray[5][i]) ;	// Hi
sscanf(row[6], "%lf", &ray[6][i]) ;	// Lo
sscanf(row[7], "%lf", &ray[7][i]) ;	// Close
data[8][0] = avg(data, 1, 5) ;		// MA5
data[9][0] = avg(data, 1, 10) ;		// MA10
data[10][0] = avg(data, 1, 15) ;	// MA15
data[11][0] = avg(data, 1, length) ;	// MA60

data[12][0] = (data[1][0] - data[1][5]) / 5 ;	// slope5
data[13][0] = (data[1][0] - data[1][10]) / 10 ;	// slope10
data[14][0] = (data[1][0] - data[1][15]) / 15 ;	// slope15
data[15][0] = data[5][0] - data[5][1] ;		// slopeHi

Rather than shrinking array data, I think better to expand it

data[11][0] = MA5 Std Dev Floor
data[12][0] = MA5 Std Dev Ceiling

The inputs would be data 13 = 23
data[13][0] = data[8][1] / data[8][0] MA5 increase
data[14][0] = data[9][1] / data[9][0] MA10 increase
data[15][0] = data[10][1] / data[10]0] MA15 increase
data[16][0] = data[11][1] / data[11][0] Standard Deveiation floor increase
data[17][0] = data[12][1] / data[12][0] Standard Deveiation ceiling increase
data[18][0] = data[1][1] / data[1][0] Mid increase
data[19][0] = data[5][1] / data[5][0] Hi increase
data[20][0] = data[6][1] / data[6]0] Lo increase
data[21][0] = data[4][1] / data[4]0] Open increase
data[22][0] = data[7][1] / data[7]0] Close increase
bid increase
ask increase
This would mean ann would have 10 inputs, 11 hidden, and 1 output
Inputs 6 and 11 are both the mid increase in the original

https://stackoverflow.com/questions/3775032/how-to-update-the-bias-in-neural-network-backpropagation
w[i,j] -= gamma * o[i] * delta[j]
http://page.mi.fu-berlin.de/rojas/neural/
John von Neumann

I've finished net3.3.3.c, but it's a flop.
Some great code, and I learned a lot.
Found a lot of holes and fixed them from the first posted code, but it's still a flop (code speak "a lot of room for improvement")
I get a lot of neuron sums that come up 4 to 20, and these high number equate to almost always sigmoids of 1.
In short, I've read a lot, but have come to conclude the last of some things I read...
Try the learning rate at 7 
Try the learning rate at 3
Keep the initial weights between 1 and 0, though they may not stay that way
start with initial weights less than 0.01
I also read and came to believe that this network is different from every other network, for every other purpose, and there are few golden rules.

I tried adjusting the numbers, and did see increases in places and decreases in other places.
The number of variables is just too overwhelming to be a job for a human.
I've not quit on the neural network, but off to build a "genetic algorithm" that can create "generations" of parameters, feed them into the network, and 
determine the best Bias, WIH and WHO.
While adding little complexity to the code, I could even experiment with different numbers of hidden nodes, more hidden layers would be a bit trickier.

In the end, it may end at a dead end, but the knowledge I've gianed about neural networks, genetic algorithms, AI, and the C language means it will not be pointless.


*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h>	// sleep
//#include </usr/include/mariadb/mysql.h>
#include "/usr/include/mysql/mysql.h"


////////////////////////////////////// Globals ///////////////////////////////////////////////////////////////////
#define inputs 12
#define outputs 1
#define hidden 13 
#define weights 169  //(inputs * hidden) + (hidden * outputs)  ;	//  16*14 + 14*1 = 169  Weights 
#define neurontot 26  // inputs + hidden + outputs = Total number of neurons in the network

#define width 13 	// data array width  	14 data elements with 1 ANN output every minute
#define length 26	// data array length 	for 15 minutes		All 26 used for training, only 15 used during operation

#define LearningRate 3


////////////////////////////////////// Prototypes ////////////////////////////////////////////////////////////////
double avg(double ray[length][width], int, int, int) ;
void backprop(double Sums[], double Outputs[], double WIH[2][inputs * hidden], double WHO[2][hidden], double ann[], double Bias[]) ;
double deriv(double, int) ;
void feedfwd(double Sums[], double Outputs[], double WIH[2][inputs * hidden], double WHO[2][hidden], double ann[], double Bias[]) ;
void feedfwdTraining(double Sums[], double Outputs[], double WIH[2][inputs * hidden], double WHO[2][hidden], double ann[], double Bias[]) ;
void getData(double ray[length][width], double, int) ;
void GetOutcome(double ray[length][width], double ann[]) ;
void getStdDev(double data[length][width], double channel[2], int, int, int whichCol) ;


int main(void)
{
	/*
	Name:  	 	main
	Purpose:  	Initialize a neural network from a database, and calculate weight changes to train, then backtest on DB data
	Arguments:	None
	Called By: 	None
	Calls To: 	feedfwd
				feedfwdTraining
				backprop
	Returns: 	None 	
	Pseudocode:	Initialize the weights
				Call feedfwd
				Call backprop
				print results
	*/
double SH[hidden] ;					// 13 Hidden Sums + 1 Output Sum
double Outputs[hidden+outputs] ;			// 13 Hidden Outputs + 1 Output Layer output

double WIH[2][inputs * hidden]  ;	// Weight Input to Hidden (12*13=)156 ([0][x] holds currrent weights, [1][x] holds previous weights)
double WHO[2][hidden]  ;			// Weight Output to Hidden 13 ([0][x] holds currrent weights, [1][x] holds previous weights)
double Bias[hidden+outputs]  ;		// 13 hidden layer bias + 1 Output Bias
double Sums[hidden+outputs] ;		// 13 Sums into Hidden [0-12] + 1[13] Sum into Output layer
double ann[inputs+outputs] ;		// 12 Inputs + 1 desired output for training 
double data[length][width] ;		// Stamp, mid, bid, ask, open, hi, lo, close, MA5, MA10, MA15, MA5 Std Dev Floor, MA5 Std Dev Ceiling, output (13, but stamp isn't an input)
double channel[2] ;					// Used to return St Dev floor and ceiling
double randnum = 0 ;
double prevout = 0 ;
double best = 0 ;
double loops = 0 ;
double loops2 = 0 ;
double loops3 = 0 ;
int randint = 0 ;
int i = 0 ;
int j = 0 ;
int epochs = 0 ;
int output = 0 ;
int keepers = 0 ;
int Training = 0 ; // During Training(1) ann will be 0 - 14 to predict 25.  During operation, ann will be 10 - 25 with no expected output


	best = (unsigned long)time(NULL) ; 
	printf("%lu\n", (unsigned long)time(NULL)) ; 
	srand(time(NULL)) ;
	
	randnum = (double) rand() ;
	randint = (int)randnum ;
	
	for (i=0; i<(inputs * hidden); i++)	// Initialize Weights Input to Hidden (WIH)
	{
		
		while (randnum > 1)
			randnum /= 10 ;
		
		WIH[0][i] = randnum ;
		
		//printf("%lf\n", randnum) ;
		randnum = (double)rand() ;
	}
	
	//printf("WIH\n") ;
	//for (i=0; i<inputs*hidden; i++)
	//{
	//		if (i % 13 == 0)
	//			printf("\n\n%lf, ", WIH[0][i]) ;
	//		else
	//			printf("%lf, ", WIH[0][i]) ;
	//}
	//printf("\n") ;

	for (i=0; i<hidden; i++)	// Initialize Weights Hidden to Output (WHO)
	{
		
		while (randnum > 1)
			randnum /= 10 ;
		
		WHO[0][i] = randnum ;
		
		//printf("%lf\n", randnum) ;
		randnum = (double)rand() ;
	}
	
	//printf("WHO\n") ;
	//for (i=0; i<hidden; i++)
	//{
	//	if (i % 13 == 0)
	//		printf("\n\n%lf, ", WHO[0][j]) ;
	//	else
	//		printf("%lf, ", WHO[0][i]) ;
	//}
	//printf("\n") ;
	
	for (i=0; i<hidden+outputs; i++)	// Initialize Bias
	{
		while (randnum > 0.95)
			randnum /= 10 ;
		
		Bias[i] = randnum ;
		
		//printf("%lf\n", randnum) ;
		randnum = (double)rand() ;
	}
	
	//printf("\nBias\n") ;
	//for (j=0; j<hidden+outputs; j++)
	//	printf("%lf, ", Bias[j]) ;
	//printf("\n") ;

	
	
	
	
	Training = 1 ;
	
	if (Training == 1)
		{
		data[0][0] = 0 ;
		
		for (epochs=0; epochs < 7000; epochs++)
		{
			getData(data, data[0][0], 26) ;	// newest stamp always [0][0]
			
			
			// When calling getStdDev for training (26 minutes) the first 15 minutes is 11 - 25, the second 15 minutes is 10 - 24, and the 10 minutes into the future is 0
			data[11][8] = avg(data, 1, 11, 5) ;		// MA5					1506594911, 150.919556, 150.910000, 150.933000, 150.922000, 150.937500, 150.906000, 150.922000, 150.936781, 150.917347, 150.863445, 150.778126, 150.948764, 0.500000, 
			data[11][9] = avg(data, 1, 11, 10) ;	// MA10					1506594851, 150.909265, 150.912000, 150.932000, 150.931000, 150.941000, 150.885000, 150.921000, 150.944346, 150.905216, 150.852378, 150.764332, 150.940423, 0.500000, 
			data[11][10] = avg(data, 1, 11, 15) ;	// MA15					1506594792, 150.925761, 150.921000, 150.941000, 150.951500, 150.963000, 150.907000, 150.931500, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.500000, 
													//						1506594731, 150.959714, 150.940000, 150.963000, 150.960000, 150.993000, 150.942000, 150.950500, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.500000, 
			getStdDev(data, channel, 11, 26, 1) ;	//						1506594674, 150.969609, 150.949000, 150.971000, 150.965000, 150.990500, 150.954000, 150.959500, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.500000, 
			//printf("%lf	%lf\n", channel[0], channel[1]) ;
			
			data[11][11] = channel[0] ; 			// StDev Floor			1506594611, 150.957382, 150.954000, 150.976000, 150.952000, 150.969500, 150.936000, 150.963500, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.500000, 
			data[11][12] = channel[1] ; 			// StDev Ceiling		1506594551, 150.935012, 150.940000, 150.964000, 150.916500, 150.982000, 150.906000, 150.951000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.500000, 
													//						1506594492, 150.910357, 150.906000, 150.927000, 150.893500, 150.931000, 150.881000, 150.910000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.500000, 
			data[10][8] = avg(data, 1, 10, 5) ;		//	MA5					1506594431, 150.865748, 150.881000, 150.906000, 150.834000, 150.903000, 150.822000, 150.888500, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.500000, 
			data[10][9] = avg(data, 1, 10, 10) ;	// MA10					1506594371, 150.821062, 150.822000, 150.846000, 150.811000, 150.841000, 150.798000, 150.834500, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.500000, 
			data[10][10] = avg(data, 1, 10, 15) ;	// MA15					1506594312, 150.798255, 150.798000, 150.824000, 150.781000, 150.816000, 150.765000, 150.811000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.500000, 
													//						1506594251, 150.751332, 150.768000, 150.794000, 150.712500, 150.779000, 150.701000, 150.779000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.500000, 
			getStdDev(data, channel, 10, 25, 1) ;	//						1506594194, 150.715379, 150.701000, 150.724000, 150.748500, 150.757000, 150.683500, 150.711500, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.500000, 
			data[10][11] = channel[0] ; 			// StDev Floor			1506594134, 150.754935, 150.740000, 150.757000, 150.760500, 150.772000, 150.742000, 150.751000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.500000, 
			data[10][12] = channel[1] ; 			// StDev Ceiling		1506594076, 150.758302, 150.749000, 150.772000, 150.764500, 150.809000, 150.726500, 150.764500, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.500000, 
			
			//for (i=0; i<length; i++)
			//{
			//	for (j=0; j<width; j++)
			//		if (j == 0)
			//			printf("%.0lf, ", data[i][j]) ;
			//		else
			//			printf("%lf, ", data[i][j]) ;
			//	printf("\n") ;
			//}
			
			ann[0] = data[10][8] / data[11][8] ;	// Get ratio of MA5 / previous MA5
			ann[1] = data[10][9] / data[11][9] ;	// Get the ratio of MA10 / previous MA10
			ann[2] = data[10][10] / data[11][10] ;	// Get the ratio of MA15 / previous MA15
			ann[3] = data[10][11] / data[11][11] ;	// 	Get the ratio of StDev Floor / previous StDev Floor
			ann[4] = data[10][12] / data[11][12] ;	// Get the ratio of StDev Ceeiling / previous StDev Ceiling
			ann[5] = data[10][1] / data[11][1] ;	// Get the ratio of Mid / previous Mid
			ann[6] = data[10][2] / data[11][2] ;	// Get the ratio of Bid / previous Bid
			ann[7] = data[10][3] / data[11][3] ;	// Get the ratio of Ask / previous Ask
			ann[8] = data[10][4] / data[11][4] ;	// Get the ratio of Open / previous Open
			ann[9] = data[10][5] / data[11][5] ;	// Get the ratio of Hi / previous Hi
			ann[10] = data[10][6] / data[11][6] ;	// Get the ratio of Lo / previous Lo
			ann[11] = data[10][7] / data[11][7] ;	// Get the ratio of Close / previous Close
			if (data[10][12] < data[0][1])			// If StDev Ceiling < Mid 10 minutes into the future
				ann[inputs] = 1 ;						// Output target 1	Go Long
			else if (data[10][11] > data[0][1])		// If StDev Floor > Mid 10 minutes into the future
				ann[inputs] = 0 ;						// Output target 0	Go Short
			//else									// Else is flat within StDev
			//	ann[12] = 0.5 ;						// Output target 0.5
			
			//printf("ann target %lf\n", ann[12]) ;
			//for (i=0; i<inputs+outputs; i++)
			//	printf("%lf, ", ann[i]) ;
			//printf("\n") ;
			
			loops = 0 ;
			loops2 = 0 ;
			loops3 = 0 ;
			if (ann[inputs] == 1)
			{
				Outputs[hidden] = 0.675 ;
				//while (Outputs[hidden] < 0.9 && loops < 50)
				while (Outputs[hidden] < 0.9)
				{
					feedfwdTraining(Sums, Outputs, WIH, WHO, ann, Bias) ;
					
					if (loops3 == 1000)
					{
						//printf("yTarget: %lf	Output: %lf\n", ann[inputs], Outputs[hidden]) ;
						loops3 = 0 ;
					}
					
					if (Outputs[hidden] < 0.9)
					{
						backprop(Sums, Outputs, WIH, WHO, ann, Bias) ;
						//printf("Bias[0] %lf	Output[13] %lf\n", Bias[0], Outputs[hidden]) ;
					}
					//else
					//{
					//	loops = 100000 ;
					//}
					loops3++ ;
					loops2++ ;
					loops++ ;
					//printf("Target %lf  Output %.12lf %.0lf loops\n", ann[inputs], Outputs[hidden], loops2) ;
				}
			}
			else if (ann[inputs] == 0)
			{
				
				Outputs[hidden] = 0.325 ;
				//while (Outputs[hidden] > 0.1 && loops < 50)
				while (Outputs[hidden] > 0.1)
				{
					//printf("xTarget: %lf	Outputs[hidden]: %lf\n", ann[inputs], Outputs[hidden]) ;
					feedfwdTraining(Sums, Outputs, WIH, WHO, ann, Bias) ;
					
					if (loops3 == 1000)
					{
						//printf("xTarget: %lf	Output: %lf\n", ann[inputs], Outputs[hidden]) ;
						loops3 = 0 ;
					}
					
					if (Outputs[hidden] > 0.1)
					{
						backprop(Sums, Outputs, WIH, WHO, ann, Bias) ;
						//printf("Bias[0] %lf	Output[13] %lf\n", Bias[0], Outputs[hidden]) ;
					}
					//else
					//{
					//	loops = 50 ;
					//}
					loops3++ ;
					loops2++ ;
					loops++ ;
					//printf("Target %lf  Output %.12lf %.0lf loops\n", ann[inputs], Outputs[hidden], loops2) ;
				}
			}
			printf("Target %lf  Output %.12lf %.0lf loops\n", ann[inputs], Outputs[hidden], loops2) ;
		}
	}
	
	printf("WIH\n") ;
	for (i=0; i<inputs*hidden; i++)
	{
			if (i % 13 == 0)
				printf("\n\n%lf, ", WIH[0][i]) ;
			else
				printf("%lf, ", WIH[0][i]) ;
	}
	printf("\n") ;
	
	printf("WHO\n") ;
	for (i=0; i<hidden; i++)
	{
		if (i % 13 == 0)
			printf("\n\n%lf, ", WHO[0][j]) ;
		else
			printf("%lf, ", WHO[0][i]) ;
	}
	printf("\n") ;
	
	printf("\nBias\n") ;
	for (j=0; j<hidden+outputs; j++)
		printf("%lf, ", Bias[j]) ;
	printf("\n") ;
	
	printf("Begin Time: %.0lf\n", best) ;
	printf("%lu	%.2lf Seconds\n\nStart Backtesting\n", (unsigned long)time(NULL), (unsigned long)time(NULL)-best) ;
	
	//return(0) ;
	
	data[0][0] = 1514845138 ;	// First 16 minutes of 2018 market (4:16PM Monday)
	
		for (epochs=0; epochs < 90; epochs++)
		{
			if (epochs == 0)
			{
				getData(data, data[0][0], 16) ;	// newest stamp always [0][0]
				
				// When calling getStdDev for training (26 minutes) the first 15 minutes is 11 - 25, the second 15 minutes is 10 - 24, and the 10 minutes into the future is 0
				data[1][8] = avg(data, 1, 1, 5) ;		// MA5
				data[1][9] = avg(data, 1, 1, 10) ;		// MA10
				data[1][10] = avg(data, 1, 1, 15) ;	// MA15
				
				getStdDev(data, channel, 1, 16, 1) ;	//	double ray[length][width], double channel[2], int startRow, int stopRow, int whichCol)
				
				data[1][11] = channel[0] ; 			// StDev Floor
				data[1][12] = channel[1] ; 			// StDev Ceiling
			}
			else
				getData(data, data[0][0], 1) ;	// newest stamp always [0][0]
			
			data[0][8] = avg(data, 1, 0, 5) ;		// MA5
			data[0][9] = avg(data, 1, 0, 10) ;		// MA10
			data[0][10] = avg(data, 1, 0, 15) ;	// MA15
			
			//printf("%lf	%lf\n", channel[0], channel[1]) ;
			
			getStdDev(data, channel, 0, 15, 1) ;	//	double ray[length][width], double channel[2], int startRow, int stopRow, int whichCol)
			data[0][11] = channel[0] ; 			// StDev Floor
			data[0][12] = channel[1] ; 			// StDev Ceiling
			
			//for (i=0; i<length; i++)		// Print data array
			//{
			//	for (j=0; j<width; j++)
			//		if (j == 0)
			//			printf("%.0lf, ", data[i][j]) ;
			//		else
			//			printf("%lf, ", data[i][j]) ;
			//	printf("\n") ;
			//}
			
			ann[0] = data[0][8] / data[1][8] ;	// Get ratio of MA5 / previous MA5
			ann[1] = data[0][9] / data[1][9] ;	// Get the ratio of MA10 / previous MA10
			ann[2] = data[0][10] / data[1][10] ;	// Get the ratio of MA15 / previous MA15
			ann[3] = data[0][11] / data[1][11] ;	// 	Get the ratio of StDev Floor / previous StDev Floor
			ann[4] = data[0][12] / data[1][12] ;	// Get the ratio of StDev Ceeiling / previous StDev Ceiling
			ann[5] = data[0][1] / data[1][1] ;	// Get the ratio of Mid / previous Mid
			//printf("%lf / %lf = %lf\n", data[0][2], data[1][2], data[0][2] / data[1][2]) ;
			ann[6] = data[0][2] / data[1][2] ;	// Get the ratio of Bid / previous Bid	**** 152.106000 / 152.114000 = 0.999947408, not 1.00000
			ann[7] = data[0][3] / data[1][3] ;	// Get the ratio of Ask / previous Ask
			ann[8] = data[0][4] / data[1][4] ;	// Get the ratio of Open / previous Open
			ann[9] = data[0][5] / data[1][5] ;	// Get the ratio of Hi / previous Hi
			ann[10] = data[0][6] / data[1][6] ;	// Get the ratio of Lo / previous Lo
			ann[11] = data[0][7] / data[1][7] ;	// Get the ratio of Close / previous Close
			
			//printf("\n\nAnn\n") ;
			//for (j=0; j<inputs; j++)
			//	printf("%lf, ", ann[j]) ;
			//printf("\n") ;
			
			feedfwd(Sums, Outputs, WIH, WHO, ann, Bias) ;
			//backprop(Sums, Outputs, WIH, WHO, ann, Bias) ;
			
			GetOutcome(data, ann) ;
			printf("%.0lf Output %lf	Current %lf	Outcome %lf\n", data[0][0], Outputs[hidden], data[0][1], ann[inputs]) ;
		}	// End for (epochs=0; epochs < 7000; epochs++)
return 0 ;
}

double avg(double ray[length][width], int col, int startRow, int howMany)
{
int i = 0 ;
double tmpdbl = 0 ;
	
	for (i=startRow; i<startRow + howMany; i++)
	{
		//printf("ray3i = %lf\n", ray[3][i]) ;
		tmpdbl = tmpdbl + ray[i][col] ;
	}
	
	
	//printf("tmpdbl = %lf	num = %d	", tmpdbl, num) ;
	tmpdbl = tmpdbl / howMany ;
	//printf("Returning %lf\n", tmpdbl) ;
	return(tmpdbl) ;
}


void backprop(double Sums[hidden + outputs], double Outputs[hidden + outputs], double WIH[2][inputs * hidden], double WHO[2][hidden], double ann[hidden + outputs], double Bias[(inputs * hidden) + hidden])
{
	/*
	Name:		backprop
	Purpose:	Calculate network weight adjustments
	Arguments:	Sums[]: an array to hold the hidden neuron input sums, and the output layer input sum
				Outputs[]: an array to hold the hidden layer neuron outputs, and the output layer (network) output
				WIH[2][inputs * hidden]: an array to hold the input to hidden weights (New wieghts[0][x], old weights [1][x])
				WHO[2][hidden]: an array to hold the hidden to output weights (New wieghts[0][x], old weights [1][x])
				ann[]: 12 network inputs and 1 network expected output
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
double deltainwt = 0 ;	// Delta Input Weights

int i = 0 ;
int j = 0 ;
int k = 0 ;
int m = 0 ;

	margerror = Outputs[hidden] - ann[hidden] ;	// Calculate Margin of Error
	
	deltaoutwt = deriv(Sums[hidden], 0) * margerror ;	// Calculate Delta Output Weights
	//printf("Margin of Error: %lf	Delta Weight Out: %.20lf\n", margerror, deltaoutwt) ;	// These are always negative
	
	//for (i=0; i<(inputs*hidden)+hidden; i++)
	//	printf("%lf, ", Weights[0][i]) ;
	//printf("\n\n") ;
	
	//memmove(&Weights[0][1], &Weights[0][0], ((inputs * hidden) + hidden) * sizeof(double)) ;
	memmove(&WIH[1][0], &WIH[0][0], (inputs * hidden) * sizeof(double)) ;
	memmove(&WHO[1][0], &WHO[0][0], hidden * sizeof(double)) ;
	
	//printf("BackProp WIH") ;
	//for (i=0; i<(inputs*hidden); i++)
	//	if (i % 13 == 0)
	//		printf("\n\n%lf, ", WIH[1][i]) ;
	//	else
	//		printf("%lf, ", WIH[1][i]) ;
	//printf("\n\n") ;
	
	j = 0 ;
	
	for (i=0; i<hidden+outputs; i++)		// Calculate hidden weight (WHO) changes
	{
		//printf("Target: %lf	Output: %lf\n", ann[hidden], Outputs[hidden]) ;
		//printf("LearningRate(%.1lf) * deltaoutwt(%lf) * Outputs[%d](%lf)) = ", LearningRate, deltaoutwt, i, Outputs[i]) ;
		if (ann[inputs] < Outputs[hidden])	// If target < output, Going Down
		{
			WHO[0][i] -= LearningRate * deltaoutwt * Outputs[i] ;
			Bias[i] -= LearningRate * deltaoutwt ;
		}
		else
		{
			WHO[0][i] += LearningRate * deltaoutwt * Outputs[i] ;
			Bias[i] += LearningRate * deltaoutwt ;
		}

		//printf("%lf\n", WHO[0][i]) ;
	}
		
	//for (i=0; i<(inputs*hidden)+hidden; i++)
	//	printf("%lf, ", Weights[i][1]) ;
	//printf("\n\n") ;
	
			// i will range between 0 - 12 (hidden 13)
			// j will range between 0 - 11 (inputs 12)
	k = 0 ;	// k will range between 0 - 156 (inputs * hidden)
	for (i=0; i<inputs; i++)									// Calculate input weight changes
	{
		deltainwt = deltaoutwt / WIH[1][k] * deriv(Sums[i], 0) ;
		
		for (j=0; j<hidden; j++)
		{
			if (ann[inputs] < Outputs[hidden])	// If target < output, Going Down
			{
				WIH[0][k] -= LearningRate * deltaoutwt * Outputs[i] ;
				WIH[0][k] -= LearningRate * deltaoutwt ;
			}
			else
			{
				WIH[0][k] += LearningRate * deltaoutwt * Outputs[i] ;
				WIH[0][k] += LearningRate * deltaoutwt ;
			}
			k++ ;
		}
	}
	
	//for (i=0; i<weights; i++)
	//	if (Weights[0][i] != Weights[1][i])
	//		printf("%lf, ", Weights[0][i]) ;
	//printf("\n\n") ;
}




double deriv(double in, int selection)
{
	/*
	Name:  		deriv
	Purpose: 	Depending on parameters, returns either a derivative or derivative inverse
	Arguments:	in
				selection
	Called By: 	feedfwd
				feedfwdTraining
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
	
	sigmoid = 1.0/(1.0 + exp(-in));         // sigmoid = Sigmoid(in) 
	
	//printf("in = %lf sigmoid = %lf\n", in, sigmoid) ;
	
	if (selection == 1)
		return (sigmoid) ;
	else
		siginverse = sigmoid * (1.0 - sigmoid) ;
		//printf("Sigmoid Inverse = %lf\n", siginverse) ;
		return (siginverse) ;
}


void feedfwd(double Sums[hidden + outputs], double Outputs[hidden + outputs], double WIH[2][inputs * hidden], double WHO[2][hidden], double ann[hidden + outputs], double Bias[(inputs * hidden) + hidden])
{
	/*
	Name:		feedfwd	//No IF statements like feedfwdTraining
	Purpose:	Calculate sums and outputs of network
	Arguments:	Sums[]: an array to hold the hidden neuron input sums, and the output layer input sum
				Outputs[]: an array to hold the hidden layer neuron outputs, and the output layer output
				WIH[][2]: an array to hold the Input to Hidden weights [0][x] and old weights [1][x]
				WHO[][2]: an array to hold the Hidden to Output weights [0][x] and old weights [1][x]
				ann[]: 11 network inputs and 1 network expected output
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

	//printf("wt[0]\n") ;
	//for (i=0; i<weights; i++)
	//	printf("%lf, ", Weights[0][i]) ;
	//printf("\n") ;
	
	//printf("FeedFwd ann\n") ;
	//for (i=0; i<hidden; i++)
	//	if (i % 13 == 0)
	//		printf("\n\n%lf, ", ann[i]) ;
	//	else
	//		printf("%lf, ", ann[i]) ;
	//printf("\n\n") ;
	
	k = 0 ;
	for (i=0; i<hidden; i++)	// Calculate hidden layer sums
	{
		Sums[i] = 0 ;
		for (j=0; j<inputs; j++)
		{
			//printf("IHSums[%d] %lf += %lf * %lf = ", i, Sums[i], WIH[0][k], ann[j]) ;
			Sums[i] += WIH[0][k] * ann[j] ;
			//printf("%lf\n", Sums[i]) ;
			k++ ;
		}
		Sums[i] += Bias[i] ;	// Add a Bias
		printf("%lf\n", Sums[i]) ;
		//printf("Sums %lf	Bias %lf\n", Sums[i], Bias[i]) ;
	}

	//printf("Sums\n") ;
	//for (i=0; i<hidden; i++)
	//	printf("%lf	", Sums[i]) ;
	//printf("\n\n") ;
	
	for (i=0; i<hidden; i++)	// Calculate hidden outs
	{
		//if (Sums[i] > 1)	//	Neuron fires
		Outputs[i] = deriv(Sums[i], 1) ;
		printf("Hidden Output[%d] %lf\n", i, Outputs[i]) ;
	}
	//printf("\n") ;
	
	Sums[hidden] = 0 ;
	for (i=0; i<hidden; i++)		// Calculate output neuron input sum
		Sums[hidden] += Outputs[i] * WHO[0][i] ;
	//printf("Sums[%d] = %lf\n", hidden, Sums[hidden]) ;
	
	Sums[hidden] += Bias[hidden] ;	// Add the output Bias
	//printf("Sums[hidden] %lf	ANN Output	%lf\n", Sums[hidden], Outputs[hidden]) ;
	
	// Calculate network output
	Outputs[hidden] = deriv(Sums[hidden], 1) ;
	//printf("ANN Output	%lf\n", Outputs[hidden]) ;
	
	//for (i=0; i<hidden+outputs; i++)
	//	printf("%lf ", Sums[i]) ;
	//printf("\n") ;
	//exit(0) ;
}


void feedfwdTraining(double Sums[hidden + outputs], double Outputs[hidden + outputs], double WIH[2][inputs * hidden], double WHO[2][hidden], double ann[hidden + outputs], double Bias[(inputs * hidden) + hidden])
{
	/*
	Name:		feedfwdTraining
	Purpose:	Calculate sums and outputs of network.  Training is almost the same as feedfwd except feedfwd has no IT statements, as it doesn't know the outcome
	Arguments:	Sums[]: an array to hold the hidden neuron input sums, and the output layer input sum
				Outputs[]: an array to hold the hidden layer neuron outputs, and the output layer output
				WIH[][2]: an array to hold the Input to Hidden weights [0][x] and old weights [1][x]
				WHO[][2]: an array to hold the Hidden to Output weights [0][x] and old weights [1][x]
				ann[]: 11 network inputs and 1 network expected output
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

	//printf("wt[0]\n") ;
	//for (i=0; i<weights; i++)
	//	printf("%lf, ", Weights[0][i]) ;
	//printf("\n") ;
	
	//printf("FeedFwd ann\n") ;
	//for (i=0; i<hidden; i++)
	//	if (i % 13 == 0)
	//		printf("\n\n%lf, ", ann[i]) ;
	//	else
	//		printf("%lf, ", ann[i]) ;
	//printf("\n\n") ;
	
	k = 0 ;
	for (i=0; i<hidden; i++)	// Calculate hidden layer sums
	{
		Sums[i] = 0 ;
		for (j=0; j<inputs; j++)
		{
			//printf("Sums[%d] %lf += %lf * %lf = ", i, Sums[i], Weights[i][0], ann[j]) ;
			Sums[i] += WIH[0][k] * ann[j] ;
			k++ ;
		}
		Sums[i] += Bias[i] ;	// Add a Bias
	}
	
	//printf("Sums\n") ;
	//for (i=0; i<hidden; i++)
	//	printf("%lf	", Sums[i]) ;
	//printf("\n\n") ;
	
	for (i=0; i<hidden; i++)	// Calculate hidden outs
	{
		Outputs[i] = deriv(Sums[i], 1) ;
		if (Outputs[hidden] == 1)
			if (Outputs[i] > Bias[i])
				Outputs[i] = 0 ;	// Neuron doesn't fire
		if (Outputs[hidden] == 0)
			if (Outputs[i] < Bias[i])
				Outputs[i] = 0 ;	// Neuron doesn't fire
		//if (Outputs[hidden] == 0.5)	? How would one determine if a neuron fires for a middle output of 0.5?
		//	if (Outputs[i] > Bias[i])
		//		Outputs[i] = 0 ;	// Neuron doesn't fire
	}
	
	Sums[hidden] = 0 ;
	for (i=0; i<hidden; i++)		// Calculate output neuron input sum
		Sums[hidden] += Outputs[i] * WHO[0][i] ;
	//printf("Sums[%d] = %lf\n", hidden, Sums[hidden]) ;
	
	Sums[hidden] += Bias[hidden] ;	// Add the output Bias
	
	// Calculate network output
	Outputs[hidden] = deriv(Sums[hidden], 1) ;
	//printf("Sums[hidden] %lf	ANN Output	%lf\n", Sums[hidden], Outputs[hidden]) ;
	
	//for (i=0; i<hidden+outputs; i++)
	//	printf("%lf ", Sums[i]) ;
	//printf("\n") ;
	//exit(0) ;
}

void getData(double ray[length][width], double startTime, int howMany)
{
	/*
	Name:		getData
	Purpose:	Fills an array with data from a database
	Arguments:	ray[]: The array to fill
				startTime: Get data starting from when
				howMany: How many to add to the array.  Typically either 1 or 15
	Called By:	main
	Calls To: 	None
	Returns:	None	
	Pseudocode:	Make DB connection
				Query
				If adding data for just 1 minute
					MemMove the array down 1 row
				Insert queried data as appropriate
	*/
int i = 0 ;
char sql[300] ;
char *server = "192.168.1.5" ;
char *user = "bri" ;
char *password = "x" ;
char *database = "fx";
double pairsid = 8 ;


	MYSQL *con ;
	MYSQL_RES *res ;
	MYSQL_ROW row ;
	con = mysql_init(NULL) ;

	// Connect to database
	if (!mysql_real_connect(con, server, user, password, database, 0, NULL, 0)) 
	{
		fprintf(stderr, "DB Connect Error %s\n", mysql_error(con)) ;
		exit(1);
	}
	
	sprintf(sql, "SELECT * FROM (SELECT stamp, mid, bid, ask, open, hi, lo, close FROM oanda WHERE pairsid = %.0lf AND stamp > %.0lf ORDER BY stamp LIMIT %d) AS alias ORDER BY stamp DESC", pairsid, startTime, howMany) ;
	
	if (mysql_query(con, sql)) 
	{
		fprintf(stderr, "Error running query %s\n", mysql_error(con)) ;
		exit(1) ; 
	}
	
	res = mysql_store_result(con) ;	
	
	if (howMany == 1)
		memmove(&ray[1][0], &ray[0][0], (length-1)*width*sizeof(double)) ;
	
	//printf("SQL returned %d rows\n", mysql_num_rows(res)) ;
	
	if (mysql_num_rows(res) > 0)
	{
		i = 0 ;
		while ((row = mysql_fetch_row(res)) != NULL)
		{
			sscanf(row[0], "%lf", &ray[i][0]) ;	// Stamp
			sscanf(row[1], "%lf", &ray[i][1]) ;	// Mid
			sscanf(row[2], "%lf", &ray[i][2]) ;	// bid will always be < ask
			sscanf(row[3], "%lf", &ray[i][3]) ;	// ask
			sscanf(row[4], "%lf", &ray[i][4]) ;	// Open
			sscanf(row[5], "%lf", &ray[i][5]) ;	// Hi
			sscanf(row[6], "%lf", &ray[i][6]) ;	// Lo
			sscanf(row[7], "%lf", &ray[i][7]) ;	// Close
			
			ray[i][8] = 0 ;
			ray[i][9] = 0 ;
			ray[i][10] = 0 ;
			ray[i][11] = 0 ;
			ray[i][12] = 0 ;
			
			//printf("Row %d %.0lf	%lf	%lf	%lf	%lf	%lf %lf	%lf\n", i, ray[0][i], ray[1][i], ray[2][i], ray[3][i], ray[4][i], ray[5][i], ray[6][i], ray[7][i]) ;
			
			i++ ;
		}
	}
	mysql_free_result(res) ;
	mysql_close(con) ;
}

void GetOutcome(double ray[length][width], double ann[hidden])
{
	/*
	Name:		GetOutcome
	Purpose:	Used during backtesting, to get the price 10 minutes past ray[0][0] time
	Arguments:	ray[]: The array of data
	Called By:	main
	Calls To: 	None
	Returns:	Double, the mid price 600 seconds from ray[0][0]
	Pseudocode:	Make DB connection
				Query
				return the result
	*/
int i = 0 ;
char sql[300] ;
char *server = "192.168.1.5" ;
char *user = "bri" ;
char *password = "x" ;
char *database = "fx";
double pairsid = 8 ;


	MYSQL *con ;
	MYSQL_RES *res ;
	MYSQL_ROW row ;
	con = mysql_init(NULL) ;

	// Connect to database
	if (!mysql_real_connect(con, server, user, password, database, 0, NULL, 0)) 
	{
		fprintf(stderr, "DB Connect Error %s\n", mysql_error(con)) ;
		exit(1);
	}
	
	sprintf(sql, "SELECT mid FROM oanda WHERE pairsid = %.0lf AND stamp > %.0lf ORDER BY stamp LIMIT 1", pairsid, ray[0][0] + 600) ;
	//printf("%s\n", sql) ;
	
	if (mysql_query(con, sql)) 
	{
		fprintf(stderr, "Error running query %s\n", mysql_error(con)) ;
		exit(1) ; 
	}
	
	res = mysql_store_result(con) ;	
	
	//printf("SQL returned %d rows\n", mysql_num_rows(res)) ;
	
	if (mysql_num_rows(res) > 0)
	{
		row = mysql_fetch_row(res) ;
		//printf("Mid = %s\n", row[0]) ;
		sscanf(row[0], "%lf", &ann[inputs]) ;		// Used for target during training
	}
	else
		ann[inputs] = -99 ;
	
	//printf("GetOutcome returning %lf\n", ray[0][inputs]) ;
	mysql_free_result(res) ;
	mysql_close(con) ;
}


void getStdDev(double ray[length][width], double channel[2], int startRow, int stopRow, int whichCol)
{
	/*
	Name:		getStdDev
	Purpose:	Gets standard deviation of 15 numbers
	Arguments:	ray[]: Array of data
				channel[]: Array to hold the floor and ceiling
				whichCol: Get St Dev of which column
	Called By:	main
	Calls To: 	None
	Returns:	None	
	Pseudocode:	Find the mean of the column
				Fill tmpray with each element minus the mean
				Square each element of tmpray
				Get the mean of the squared differences
				Fill array channel with the floor and ceiling
				
				Note: When calling, stopRow will not be included.  
	*/
int i = 0 ;
int j = 0 ;
double tmpdbl = 0 ;
double avg = 0 ;
double tmpray[stopRow - startRow - 1] ;

	tmpdbl = 0 ;
	for (j=startRow; j<stopRow; j++)	// Work out the Mean (the simple average of the numbers)
		tmpdbl += ray[j][whichCol] ;
	avg = tmpdbl / (stopRow - startRow) ;
	
	//printf("Avg = %lf\n", avg) ;
	
	for (j=0; j<stopRow - startRow; j++)	// For each number: subtract the Mean
	{
		//printf("ray[%d][%d] (%lf) - %lf = ", j, whichCol, ray[j+startRow][whichCol], avg) ;
		tmpray[j] = ray[i+startRow][whichCol] - avg ;
		//printf("%lf\n", tmpray[j]) ;
	}
	
	//printf("tmpray with avg subtracted\n") ;
	//for(i=0; i<stopRow-startRow-1; i++)
	//	printf("%lf ", tmpray[i]) ;
	//printf("\n") ;
	
	tmpdbl = 0 ;
	
	for (j=0; j<stopRow - startRow; j++)	// For each number: square the result
	{
		tmpray[j] = tmpray[j] * tmpray[j] ;
		//printf("tmpray[%d] %lf\n", j, tmpray[j]) ;
		tmpdbl += tmpray[j] ;
	}
	
	tmpdbl /= (stopRow - startRow - 1) ;
	
	//printf("tmpdbl = %lf\n", tmpdbl) ;
	//printf("After squaring\n") ;
	//for(i=0; i<stopRow-startRow; i++)
	//	printf("%lf ", tmpray[i]) ;
	//printf("\n") ;
	
	
	tmpdbl = 0 ;
	for (j=0; j<stopRow - startRow; j++)	// Then work out the mean of those squared differences.
		tmpdbl += tmpray[j] ;
	tmpdbl /= (stopRow - startRow) ;
	
	//printf("Mean of the squares %lf	avg %lf	sqrt %lf\n", tmpdbl, avg, sqrt(tmpdbl)) ;
	
	
	channel[0] = (avg - sqrt(tmpdbl)) ;
	channel[1] = (avg + sqrt(tmpdbl)) ;
}



/*

https://github.com/dougszumski/NNet
http://neuralnetworksanddeeplearning.com/
http://neuralnetworksanddeeplearning.com/chap1.html

git clone https://github.com/dougszumski/NNet/tree/master
git clone https://github.com/MichalDanielDobrzanski/DeepLearningPython35
http://www.deeplearningbook.org/

Try as I might, the answer always came out very near 1.  This is as expected since there was no <i>bias</i> used.  The <i>bias</i> (AKA activation point AKA threshold) determines if the neuron activates or doesn't activate.
When all the neurons activate, the answer should be near 1.  When none, or few, of the neurons activate, the network output should be near 0.  Like adjusting the weights, the bias is also adjusted at the same time, but with a slightly different formula.
Technically, the bias is always 1, and it's the weight that gets adjusted.  But if the <i>bias</i> is always 1, and everyone knows that 1 * anything = that same thing, I just think of the weight as the bias.


https://stackoverflow.com/questions/3775032/how-to-update-the-bias-in-neural-network-backpropagation

backpropagation computes partial derivatives of the error function E (aka cost, aka loss)
∂E/∂w[i,j] = delta[j] * o[i]
where w[i,j] is the weight of the connection between neurons i and j, j being one layer higher in the network than i, and o[i] is the output (activation) of i

These values can then be used in weight updates, e.g.
// update rule for vanilla online gradient descent
w[i,j] -= gamma * o[i] * delta[j]
where gamma is the learning rate.

update rule for bias weights is
bias[j] -= gamma_bias * delta[j]
where bias[j] is the weight of the bias on neuron j, the multiplication with 1 can obviously be omitted, and gamma_bias may be set to gamma or to a different value.

These formulas would server to lower the weight and bias, use += to increase the weight and bias

backpropagation computes partial derivatives of the error (desired  - output) function E (AKA cost, AKA loss)
delta[j] = ∂E/∂w[i,j] = delta[j] * o[i]
where w[i,j] is the weight of the connection between neurons i and j, j being one layer higher in the network than i, and o[i] is the output of i

This values can then be used in weight updates, e.g.
w[i,j] -= LearningRate * output[i] * delta[j]

update rule for bias weights is
bias[j] -= LearningRate * delta[j]

Weight adjustments figure in the output of the neuron, while the bias is independant of the outputs
Adjustments to the bias adjust if the neuron will fire or not

The bias determines if the neuron will fire or not.
If the output > bias, the neuron fires (enter the output in Outputs[x] array)
Else enter a 0 in Outputs[x] array because the neuron didn't fire, so it's output won't contribute to the Sums[x] array as an input to the next layer.

Increasing the depth (more hidden layers) increases processing times exponentially, with some accuracy gain.
Increasing the width (more neurons in the hidden layer) increases the processing times linearly, with some accuracy gain.

Below is the best resource I've found to date explaining the changes/interactions of changing weights and bias'
http://neuralnetworksanddeeplearning.com/chap4.html

https://takinginitiative.wordpress.com/2008/04/23/basic-neural-network-tutorial-c-implementation-and-source-code/
Now I’ve seen various implementations and wait for it… here comes an OO rant: I don’t understand why people feel the need to encapsulate everything in classes. 
The most common implementation of a neural network I’ve come across is the one where each neuron is modeled as an object and the neural network stores all these 
objects. Now explain to me that advantages of such an approach? All you’re doing is wasting memory and code space. There is no sane reason to do this apart from 
trying to be super OO.


*/

