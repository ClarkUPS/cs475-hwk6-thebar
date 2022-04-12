/*
 * bartender.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "bartender.h"

/**
 * Code for bartender thread.
 * Do not touch.
 */
void* bartender(void* args)
{

	int i;
	for (i = 0; i<num_threads; i++)
	{
		waitForCustomer();
		makeDrink();
		receivePayment();
	}
	return NULL;
}

/**
 * Waits in a closet until a customer enters.
 */
void waitForCustomer()
{
	//TODO - synchronize
	printf("\t\t\t\t\t\t\t\t\t\t\t| Bartender\n");
		//Semephone triggered by customer entering
	sem_post(barQueue_S); //post to bar queue thus rasing the value form 0 to 1 allowing one customer in!
	sem_wait(customerArival_S); //Await a customers signal that they have arived

}


/**
 * When a customer places an order it takes the Bartender
 * a random amount of time between 5 ms and 1000 ms to make the drink.
 */
void makeDrink()
{
	sem_wait(customerOrder_S); //wait for order to be requested.

	//TODO - synchronize
		//Random time 5 ms and 1000 ms
	int mixologyTime = rand() % (1000 + 1 - 5) + 5;
	usleep(mixologyTime);
	
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\tBartender\n");

	sem_post(makingDrink_S); //Post that the drink is done
}


/**
 * Gets payment from the correct customer
 */
void receivePayment()
{
	//TODO - synchronize
	//at the register waiting for customer to pay
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\tBartender\n");

	sem_wait(paying_S);
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\t\tBartender\n");
	
	sem_post(customerGoodToGo_S); //confirm the payment has been secured before the customer is good to go
	
	sem_wait(customerReadyToGo_S); //wait for customer to print that they are leaving and post that they are leaving
	
	
	
}
