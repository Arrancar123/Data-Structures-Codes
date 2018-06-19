#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

typedef int node;

typedef struct cell{
	node data;
	struct cell *RC;
	struct cell *LC;
}*Tree;

typedef enum{
	TRUE, FALSE
}boolean;

void insertChild(Tree *, node );
void displayPostOrder(Tree );
void displayPreOrder(Tree );
void displayInOrder(Tree );
void deleteLeaf(Tree *, node );
boolean isMember (Tree , node);

int main(void)
{
	Tree T;
	T = NULL;
	boolean catcher;
	
	insertChild(&T, 10);
	insertChild(&T, 5);
	insertChild(&T, 7);
	insertChild(&T, 14);
	insertChild(&T, 12);
	insertChild(&T, 18);
	insertChild(&T, 15);
	insertChild(&T, 43);
	insertChild(&T, 90);
	insertChild(&T, 72);
	insertChild(&T, 54);
	
	deleteLeaf(&T, 54);
	
	printf("Postorder : ");
	displayPostOrder(T);
	printf("\n\nPreorder : ");
	displayPreOrder(T);
	printf("\n\nInorder : ");
	displayInOrder(T);
	
	catcher = isMember(T, 72);
	(catcher == TRUE)? printf("\n\nElement Found"): printf("\n\nElement Not found");
	
	getch();
	return 0;
}

void deleteLeaf(Tree *T, node leaf)
{
	Tree *trav, temp;
	
	for(trav = T; *trav!=NULL && (*trav)->data != leaf; ){
		trav = (leaf > (*trav)->data) ? &(*trav)->RC : &(*trav)->LC;
	}
	if(*trav!=NULL){
		temp = *trav;
		if((*trav)->RC == NULL){
			*trav = temp->LC;
		}else if((*trav)->LC == NULL){
			*trav = temp->RC;
		}else{
			for(trav = &(*trav)->RC; (*trav)->LC != NULL; trav = &(*trav)->LC){}
			temp->data = (*trav)->data;
			temp = *trav;
			*trav = temp->LC;
		}
		free(temp);
	}
}

void insertChild(Tree *T, node leaf)
{
	Tree *trav, temp;
	for(trav = T; *trav!=NULL ; )
	{
		trav = (leaf < (*trav)->data) ? &(*trav)->LC : &(*trav)->RC;
	}
	if((*trav) == NULL){
		temp =(Tree)malloc(sizeof(struct cell));
		if(temp!=NULL){
			temp->data = leaf;
			temp->LC = NULL;
			temp->RC = NULL;
			*trav = temp;
		}
	}
}

void displayInOrder(Tree T)
{
	if(T == NULL){
		return;
	}
	displayInOrder(T->LC);
	printf("%d  ", T->data);
	displayInOrder(T->RC);
}

void displayPreOrder(Tree T)
{
	if(T == NULL){
		return;
	}
	printf("%d  ", T->data);
	displayPreOrder(T->LC);
	displayPreOrder(T->RC);
}

void displayPostOrder(Tree T)
{
	if(T == NULL){
		return;
	}
	displayPostOrder(T->LC);
	displayPostOrder(T->RC);
	printf("%d  ",T->data);
}

boolean isMember (Tree T, node elem)
{
	Tree trav;
	for(trav = T; trav != NULL && trav->data != elem; ){
		trav = (elem > trav->data)? trav->RC: trav->LC;
	}
	return (trav != NULL)? TRUE: FALSE;
}
