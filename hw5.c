#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct to hold the input taps
typedef struct tapList
	{

		int tap;
		struct tapList * next; 
	}myList;

//prototype
int genRand (int seed, int numOfRands, FILE *outputfile);
int getBit(int seed, int taps);

struct tapList *head = NULL;

int main (int argc, char * argv[])

{
int seed, tap1, randNums;
FILE * fOut = fopen(argv[2], "w");

//variables of type tapList (see above struct)
struct tapList *temp;
struct tapList *node;

//taking the commandline number (which reads in as a string) and converts to an integer
seed = atoi(argv[1]);

//Error checking to make sure seed is a positive number
	if (seed < 0)
	{

		fprintf(stderr, "Invalid argument, please enter a number greater than 0\n");
			return (0);
	}

//User prompts for taps
printf("Please enter your taps and use -1 to end your input: \n");
while (scanf("%d", &tap1) == 1){

	if (tap1 == -1)
		break;

	if (tap1 < 0 || tap1 > 31 )
	{
		fprintf(stderr, "Tap1 was out of bounds, enter a number between 0-31\n");
		return (0);
	}
	//creating node in memory
	node = malloc( sizeof(myList) );
	
	//store input into node
	node -> tap = tap1;
	//setting next node to null
	node -> next = NULL;

	//if there's nothing in head, set head to node
	if(head == NULL){

		head = node;

	}
	//else set temp equal to head and temp equal to next
	else{
		temp = head;
		//if temp next is NULL, set temp next to node
		if(temp -> next == NULL)
		{
			temp -> next = node;
		}
		//else if there is a duplicate input, break out of program
		else
		{
			if(temp -> tap == tap1)
			{
				break;
			}
		
		temp = temp -> next;
		}

	}


}

//prompt user for amount of random numbers
printf("Please enter a number greater than 0 that you would like generated\n");
scanf("%d", &randNums);

//error check for random numbers (x>0)

if (randNums < 0 )
{
	fprintf(stderr, "You must enter a number greater than 0\n");
	printf("Please  re-enter a number greater than 0 that you would like generated\n");
	scanf("%d", &randNums);		

}

	//call random generator here
	
	genRand(seed, randNums, fOut);
	fclose(fOut);
	return 0;

}

//function to call 
int genRand (int base, int numOfRands, FILE *output)
{
	int i, feedBack, random;
	int prev, curr;
	int ptap, ctap;
	struct tapList *temp;
	int seed = base;
	int tap31 = 31;
	int statikTap;
	temp = head;

	//setting ptap to the current tap
	ptap = temp -> tap;
	//calling getBit to find which bit the taps is looking at 
	prev = getBit(seed, ptap);
	//getting the 31st bit and setting it to statikTap
	statikTap = getBit(seed, tap31);
	
	//for loop to step through given number of random numbers requested by user
	for (i=0; i < numOfRands; i++)
	{
		//if temp -> next is not null then set new temp to next, current tap to next-> tap and then get bit for current
		if(temp -> next != NULL){

			temp = temp -> next;
			ctap = temp -> tap;
			curr = getBit(seed, ctap);

		}
		//XOR prev, curr, and stakTap to get feedback bit
		feedBack = prev ^ curr ^ statikTap;
		
		//shift the seed once to the left
		random = seed << 1;
		//add feedback bit to 0th bit
		random = random  | feedBack;
		//printout to file
		fprintf(output, "%d\n", random);
		//set seed to new random number
		seed = random;


	}
}

//a function to utilize a mask and a flag to get the bit we need to work with to store in feedback
int getBit(int seed, int taps)
	{
		int mask , flag;

		mask = 1 << taps;

		flag = mask & seed;

		if(flag == 0)
		{
			return 0;
		}	
		else
			return 1;

	}

