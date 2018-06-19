#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct stk{
	int top; //Will be incremented everytime an element is inserted, initialized to -1 
			 //to show that the list is empty
	char elem [64][SIZE];
}Stack;

void initialize(Stack *ptr);
void insert(Stack *ptr, char str[]);
void deleteElem (Stack *ptr);
void display(Stack ptr);
char* get(Stack *ptr);

int main (void)
{
	Stack s;
	char* catcher;
	
	initialize (&s);
	
	insert(&s, "Ex1");
	insert(&s, "Ex2");
	insert(&s, "Ex3");
	
	//deleteElem(&s);
	
	display(s);
	
	catcher = get(&s);

	printf("\n");
	display(s);
	printf("\n");
	
	//Two ways to print a string but I opted to use %s
	printf("Returned string: %s", get(&s));
	//puts(get(&s));
	
	free(catcher); //free the catcher after it is used to put the borrowed memory back into the heap
	
	return 0;
}

void initialize (Stack *ptr)
{
	ptr->top = 0;
}

void insert(Stack *ptr, char str[])
{
	if(ptr->top < SIZE){
		strcpy(ptr->elem[ptr->top], str);
		ptr->top++;
	}
}

//Normal way to delete is to just decrement top
void deleteElem (Stack *ptr)
{
	ptr->top--;
}

void display(Stack ptr)
{
	int ctr;
	for(ctr = 0; ctr < ptr.top; ctr++){
		printf("[%d]", ctr);
		puts(ptr.elem[ctr]);
	}
}

//Another way to delete
//This function will get the string at the top of stack and return it
//to the calling function
char* get (Stack *ptr)
{
	char *str = ptr->elem[ptr->top];
	char *ret = (char*)malloc(strlen(str));	//allocate space for the string to be returned
	strcpy(ret, str); //copy the string to the variable to be returned 
	ptr->top--; //decrement to "delete" the element
	return ret;
}
