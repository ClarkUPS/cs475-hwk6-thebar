/*
 * TheBar.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "customer.h"
#include "bartender.h"

void printBanner();
void init();
void cleanup();


//Semaphores:
sem_t* barQueue_S;
sem_t* customerArival_S;
sem_t* customerOrder_S;
sem_t* makingDrink_S;
sem_t* paying_S;
sem_t* customerReadyToGo_S;
sem_t* customerGoodToGo_S; 


/**
 * Main function
 * argc = number of arguments (only two)
 * argv = argumetns
 */
int main(int argc, char **argv)
{
	//Preprocessing input:
	if(argc < 2 || argc > 2){
		printf("Usage: ./thebarSol <num customers>\n");
		return 0;
	}
	int threadCount = atoi(argv[1]); //convert and run checks on

	if(threadCount < 1 || threadCount > 100){
		printf("Usage: ./thebarSol <num customers>\nPlease choose a value greater than 1 and less than 100\n\n");
		return 0;
	}

	srand(time(NULL));

	num_threads = threadCount; //save to global
	printf("\nNumber of threads: %d\n", threadCount); //REMOVE

	printBanner();
	
	// initialize semaphores
	init();

	// TODO - fire off customer thread
	pthread_t threads[threadCount]; //testing only one thread
	unsigned int threadId[threadCount];
	
	int i;
	for(i = 0; i < threadCount; i++){
		//threads[i] = i;
		threadId[i] = i;

		//printf("fire off: %d", idNum);

		pthread_create(&threads[i], NULL, customer, &threadId[i]); //Not sure if I should also pass in i for args REMOVE
	}
	
	
	// TODO - fire off bartender thread
	
	//Bartender Threads:
	pthread_t bartenderThread;
	pthread_create(&bartenderThread,NULL, bartender, &threadCount);
	
	
	// TODO - wait for all threads to finish
	
	//Join threads back after compleation
	for(int i =0; i < threadCount; i++){
		pthread_join(threads[i],NULL);
	}
	
	//Bartender Thread join
	pthread_join(bartenderThread,NULL);

	

	cleanup(); // cleanup and destroy semaphores
	return 0;
}

/**
 * Prints the activity banner.
 * Do not touch.
 */
void printBanner()
{
	printf("Customer:\t\t\t\t\t\t\t\t\t\t| Employee:\n");
	printf("Traveling\tArrived\t\tOrdering\tBrowsing\tAt Register\tLeaving");
	printf("\t| Waiting\tMixing Drinks\tAt Register\tPayment Recv\n");
	printf("----------------------------------------------------------------------------------------+");
	printf("-----------------------------------------------------------\n");
}

/**
 * Create and initialize semaphores
 */
void init()
{
	// TODO - unlink semaphores
	sem_unlink("/barQueue_S");
	sem_unlink("/customerArival_S");
	sem_unlink("/customerOrder_S;");
	sem_unlink("/makingDrink_S");
	sem_unlink("/paying_S");
	sem_unlink("/customerReadyToGo_S");
	sem_unlink("/customerGoodToGo_S");

		//Open semaphoers
	barQueue_S = sem_open("/barQueue_S", O_CREAT, 0600 , 0); //inital signal sent by bar tender signaling that there is an opening
	customerArival_S = sem_open("/customerArival_S", O_CREAT, 0600, 0); //Siganl by a customer that has entered the bar to the bar tender
	customerOrder_S = sem_open("/customerOrder_S;", O_CREAT, 0600, 0);
	makingDrink_S = sem_open("/sem_t* makingDrink_S", O_CREAT, 0600, 0);
	paying_S = sem_open("/paying_S", O_CREAT, 0600, 0);
	customerReadyToGo_S = sem_open("/customerReadyToGo_S", O_CREAT, 0600, 0);
	customerGoodToGo_S = sem_open("/customerGoodToGo_S", O_CREAT, 0600,0);
	// TODO - create semaphores
}

/**
 * Cleanup and destroy semaphores
 */
void cleanup()
{
	// TODO - close semaphores
	sem_close(customerArival_S);
	sem_unlink("/customerArival_S");
	
	sem_close(customerOrder_S);
	sem_unlink("/customerOrder_S;");
	
	sem_close(barQueue_S);
	sem_unlink("/barQueue_S");

	sem_close(makingDrink_S);
	sem_unlink("/makingDrink_S");

	sem_close(paying_S);
	sem_unlink("/paying_S");

	sem_close(customerReadyToGo_S);
	sem_unlink("/customerReadyToGo_S");

	sem_close(customerGoodToGo_S);
	sem_unlink("/customerGoodToGo_S");
}
