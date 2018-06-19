#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5

typedef struct {
	int counter; //Increments everytime an element is inserted into the list
	int front;
	int rear;
	char elements [SIZE];
}ArrayQueue;

void initialize(ArrayQueue *queue);
void enqueue (ArrayQueue *, char );
void display (ArrayQueue );
char dequeue (ArrayQueue *);
int isFull (ArrayQueue);
int isEmpty (ArrayQueue);

int main (void)
{
	ArrayQueue aq;
	initialize(&aq);
	
	enqueue(&aq, 'c');
	enqueue(&aq, 'd');
	enqueue(&aq, 'e');
	enqueue(&aq, 'f');
	
	dequeue(&aq);
	display(aq);
	
	return 0;
}

void initialize(ArrayQueue *queue)
{
	queue->counter = 0; //Setting the queue to empty
	queue->front = queue->rear = -1; 
}

void enqueue (ArrayQueue *queue, char elem)
{
	if(isFull(*queue) == 0){
		queue->rear = (queue->rear+1) % SIZE;
		queue->elements[queue->rear] = elem;
		
		if(queue->front == -1){
			queue->front = queue->rear;
		}

		queue->counter++;
	}
}

char dequeue (ArrayQueue *queue)
{
	char ret = '\n';
	if(isEmpty(*queue) == 0){
		ret = queue->elements[queue->front];
		queue->front = (queue->front+1) % SIZE;
		queue->counter--;
		if(queue->counter == 0){
			queue->rear = queue->front = -1;
		}
	}

	return ret;
}

//Function to check if the queue is empty
//returns 1 if it is and 0 if there is still space
int isEmpty(ArrayQueue queue)
{
	return (queue.counter == 0)?1:0;
}

//Function to check if the queue is full
//returns 1 if it is and 0 if there is still space
int isFull(ArrayQueue queue)
{
	return (queue.counter == SIZE)?1:0;
}

//Since this is a queue, we can't display it like how we would normally display an array
//Everytime we display an element, we have to dequeue it from the list
//to be able to access the next element
void display(ArrayQueue queue)
{
	while(queue.counter != 0){
		printf("%c, " ,dequeue(&queue));
	}
	printf("\b\b ");
}
