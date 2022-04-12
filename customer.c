/*
 * customer.c
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
#include "customer.h"

/**
 * This is what the thread will call.
 * Do not touch.
 */
void* customer(void* args)
{
	

	unsigned int *custID = (unsigned int*) args;
	//printf("\nCustomer: %d", *custID); //REMOVE
	custTravelToBar(*custID);
	custArriveAtBar(*custID);
	custPlaceOrder();
	custBrowseArt();
	custAtRegister();
	custLeaveBar();
	return NULL;
}


/**
 * Each customer takes a random amount of time between 20 ms and 5000 ms to travel to the bar.
 */
void custTravelToBar(unsigned int custID)
{
	int travelTime = rand() % (5000 + 1 - 20) + 20;
	printf("Cust %u\t\t\t\t\t\t\t\t\t\t\t|\n", custID);

	usleep(travelTime); //Sleep for a time
	//TODO - synchronize: Do I need to sync anyting here?
	//SLEEP
}


/**
 * If there is already another customer in the bar the current customer has
 * to wait until bar is empty before entering.
 */
void custArriveAtBar(unsigned int custID)
{
	//TODO - synchronize

	sem_wait(barQueue_S); //Wait till the bar tender has signled they are ready for a new occupent
	now_serving = custID; //Set global once through semaphore
	printf("\t\tCust %u\t\t\t\t\t\t\t\t\t|\n", custID);
	
	//Allows the bartender to contenue
	sem_post(customerArival_S); //Let the bar tender know that they have arived/they are ready to order
}


/**
 * The customer in the bar places an order
 */
void custPlaceOrder()
{
	//TODO - synchronize
	sem_post(customerOrder_S); //Post order, allow the bar tender to go out and make the drink

	printf("\t\t\t\tCust %u\t\t\t\t\t\t\t|\n", now_serving);
}


/**
 * The customer in the bar can browse the wall art for a random amount of time between 3ms and 4000ms.
 */
void custBrowseArt()
{
	//TODO - synchronize
	printf("\t\t\t\t\t\tCust %u\t\t\t\t\t|\n", now_serving);

	int browseArt = rand() % (4000 + 1 - 3) + 3; //random sleep length
	usleep(browseArt);
}


/**
 * If their drink is not ready by the time they are done admiring the art they must wait
 * until the bartender has finished. When the bartender is finished, the customer pays.
 *
 */
void custAtRegister()
{
	//TODO - synchronize
	sem_wait(makingDrink_S); //Wait for drink to be made.
	
	printf("\t\t\t\t\t\t\t\tCust %u\t\t\t|\n", now_serving);

	sem_post(paying_S); //Pay for the drink. Bartender awating the payment
}


/**
 * The customer in the bar leaves the bar.
 */
void custLeaveBar()
{
	//TODO - synchronize
	
	
	sem_wait(customerGoodToGo_S);//Customer has been given the go ahead to leave by barkeep
	
	printf("\t\t\t\t\t\t\t\t\t\tCust %u\t|\n", now_serving);
	
	sem_post(customerReadyToGo_S);//Customer signals that they are ready to go and has thus paied their tab so they head out
	
	
	
	
	
	
}
