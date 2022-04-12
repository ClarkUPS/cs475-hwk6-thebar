/*
 * globals.h
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

int num_threads;	// number of customer threads
int now_serving;	// customer's ID who is being served

//TODO - declare some semaphores
sem_t* barQueue_S;
sem_t* customerArival_S;
sem_t* customerOrder_S;
sem_t* makingDrink_S;
sem_t* paying_S;
sem_t* customerReadyToGo_S;
sem_t* customerGoodToGo_S;

#endif /* GLOBALS_H_ */
