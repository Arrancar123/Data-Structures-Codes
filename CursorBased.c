#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define SIZE 10
#define EMPTY -2
#define Null -1

typedef struct node{
	int elem;
	int next;
}Node;

typedef Node VirtualHeap [SIZE];

int allocate(VirtualHeap );
void insertFirst(int *, VirtualHeap, int );
void insertLast(int *, VirtualHeap, int );
void insertUnique(int *, VirtualHeap, int );
int deleteElem(int *, VirtualHeap, int );
void initializeHeap(VirtualHeap );
void display(int , VirtualHeap );
int isFound(int , VirtualHeap, int );
int getCommon(int, int, VirtualHeap );

int main (void)
{
	VirtualHeap VH;
	int start = Null, catcher;
	
	initializeHeap(VH);
	
	insertFirst(&start, VH, 5);
	insertFirst(&start, VH, 7);
	insertLast(&start, VH, 2);
	insertFirst(&start, VH, 5);
	insertLast(&start, VH, 9);

	display(start, VH);

	catcher = deleteElem(&start, VH, 5);
	printf("\n%d\n\n", catcher);
	
	insertLast(&start, VH, 4);
	
	display(start, VH);
	
	return 0;
}

//Initializes all "next" fields of the list to EMPTY, which is -2
void initializeHeap(VirtualHeap VH)
{
	int ctr;
	for(ctr = 0; ctr < SIZE; ctr++){
		VH[ctr].next = EMPTY;
	}
}

int isFound(int start, VirtualHeap VH, int element)
{
	for(; start != -1 && VH[start].elem != element; start = VH[start].next){}
	return (start != -1)?start: Null;
}

//Since we cannot use the malloc function in a cursor based list
//we have to make our own malloc function, which is allocate
//It returns the index whose "next" field is set as EMPTY
//and that is where we insert the next element
int allocate(VirtualHeap VH)
{
	int space = Null, ctr;
	for(ctr = 0; ctr < SIZE && VH[ctr].next != EMPTY; ctr++){}
	return (VH[ctr].next == EMPTY)? ctr: space;
}

//insertFirst and insertLast functions are based off of Linked List
void insertFirst(int *start, VirtualHeap VH, int elem)
{
	int temp;
	temp = allocate(VH);
	if(temp != -1){
		VH[temp].elem = elem;
		VH[temp].next = *start;
		*start = temp;
	}
}

void insertLast(int *start, VirtualHeap VH, int elem)
{
	int temp, *trav;
	for(trav = start; *trav != -1; trav = &(VH[*trav].next)){}
	temp = allocate(VH);
	if(temp != -1){
		VH[temp].elem = elem;
		VH[temp].next = *trav;
		*trav = temp;
	}
}

//Function to insert unique elements into the list, making sure there are no duplicates
void insertUnique(int *start, VirtualHeap VH, int element)
{
	int found = isFound(*start, VH, element);
	if(found == -1){
		insertFirst(start, VH, element);
	}else{
		printf("Element already exists in list!\n");
	}
}

//Function returns 1 element is deleted and 0 if it isn't in the list
int deleteElem(int *start, VirtualHeap VH, int elem)
{
	int *trav, temp;
	for(trav = start; *trav != -1 && VH[*trav].elem != elem; trav = &(VH[*trav].next)){}
	if(VH[*trav].elem == elem){
		temp = *trav;
		*trav = VH[*trav].next;
		VH[temp].next = EMPTY;
		return 1;
	}else{
		return 0;
	}
}

void display(int start, VirtualHeap VH)
{
	int ctr;
	for(ctr = start; ctr != -1; ctr = VH[ctr].next){
		printf("Index: [%d] -- Elem: %d -- Next: [%d]\n", ctr, VH[ctr].elem, VH[ctr].next);
	}
}

//Function to get common element from two lists and insert them to a new list
int getCommon(int listOne, int listTwo, VirtualHeap VH)
{
	int common = Null;
	
	for(; listOne != Null; listOne = VH[listOne].next){
		if(isFound(listTwo, VH, VH[listOne].elem) != Null){
			insertUnique(&common, VH, VH[listOne].elem);
		}
	}
	
	return common;
}
