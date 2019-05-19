//Author: Akash Magnadia
//Class: CS 211
//Programming Assignment 2

#include <stdio.h>
#include <stdlib.h>

/* typical C boolean set-up */
#define TRUE 1
#define FALSE 0

struct stack {
	char*    darr;  /* pointer to dynamic array  */
	int     allocated;  /* amount of space allocated */
	int     inUse; /* top of stack indicator
			  - counts how many values are on the stack   */
};


void init(struct stack* s)
{
	s->allocated = 2;
	s->darr = (char*)malloc(sizeof(int) * s->allocated);
	s->inUse = 0;
}

void push(struct stack* s, char val)
{ //replace using for loop
	if (s->inUse >= s->allocated) { //if need more space increment it by 2
		s->allocated += 2; //increment allocated by 2
		char *tempArray = NULL;
		tempArray = (char*)malloc(s->allocated * sizeof(char));

		int i; //for the for loop
		int loopSize; //how many times to run the loop
		loopSize = s->allocated - 2;
		for (i = 0; i < loopSize; i++) {
			tempArray[i] = s->darr[i];
		}
		s->darr = (char*)malloc(s->allocated * sizeof(char)); //make room for memory in s->darr

		//copy back the data to s->darr from tempArray
		loopSize = s->allocated - 2;
		for (i = 0; i < loopSize; i++) {
			s->darr[i] = tempArray[i];
		}
		
		free(tempArray); //free up the memory after the transfer is done
	}
	s->darr[s->inUse] = val; //put the char at the very end(towards right)
	s->inUse = s->inUse + 1; //increment size by one as one space was used
}

int isEmpty(struct stack* s)
{
	if (s->inUse == 0)
		return TRUE;
	else
		return FALSE;
}


int top(struct stack* s)
{
	return (s->darr[s->inUse - 1]);
}


int pop(struct stack* s)
{
	char topValue;
	//struct Stack *top;

	if (s == NULL)
	{
		printf("Stack overflow n");
		getchar();
		exit(0);
	}

	topValue = s->darr[s->inUse - 1]; //second to the last value
	
	//takes the end and theoretically removes it 
	s->inUse = s->inUse - 1; //memory still there but decreases the size
	return topValue;
}


void clear(struct stack* s)
{
	while (isEmpty(s) == FALSE)
	{
		char value = top(s);
		//printf("The top value on the stack is %d\n", value);

		pop(s);
	}

	//printf("The stack is now empty\n");
}

int size(struct stack* s) {
	return s->inUse;
}

int allocated(struct stack* s) {
	return s->allocated;
}

void freeUp(struct stack* s) {
	free(s->darr);
}

int isMatchingPair(char character1, char character2)
{
	if (character1 == '(' && character2 == ')')
		return TRUE;
	else if (character1 == '{' && character2 == '}')
		return TRUE;
	else if (character1 == '[' && character2 == ']')
		return TRUE;
	else if (character1 == '<' && character2 == '>')
		return TRUE;
	else
		return FALSE;
}



int main(int argc, char** argv)
{
	struct stack st1; //typedef lets you call stuff without struct
	int debugMode; //debugging mode
	debugMode = FALSE;
	int i;
	for (i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0) {
			debugMode = TRUE;
		}
	}

	char input[301];
	int index; //keep track of the original index that is being checked
	char popped; //holds the value that has been popped
	popped = NULL; //initialize popped to null

	int openBracket; //if the missing an open bracket
	openBracket = FALSE;
	int expecting; //if expecting a different closed bracket
	expecting = FALSE;

	if (debugMode == TRUE) {
		printf("DEBUGGING MODE ACTIVATED!!!!\n"); //let user know they are in debug mode
	}

	init(&st1);

	/* set up an infinite loop */
	while (1)
	{
		index = -1; //reset index with offset by 1 to left
		/* get line of input from standard input */
		printf("\nEnter input to check or q to quit\n");
		fgets(input, 300, stdin);

		/* remove the newline character from the input */
		int i = 0;
		while (input[i] != '\n' && input[i] != '\0')
		{
			i++;
		}
		input[i] = '\0';

		/* check if user enter q or Q to quit program */
		if ((strcmp(input, "q") == 0) || (strcmp(input, "Q") == 0))
			break;

		int j; //how many times it has been inputed which is i times
		for (j = 0; j < i; j++) {
			index++; //go to the next position
			if ((input[j] == '{') || (input[j] == '(') || (input[j] == '[') || (input[j] == '<')) {
				push(&st1, input[j]);
				if (debugMode == TRUE) {
					printf("Pushed: %c\n", input[j]);
				}
			}

			if ((input[j] == '}') || (input[j] == ')') || (input[j] == ']') || (input[j] == '>')) {
				if (size(&st1) == 0) { //not balanced - case for missing open bracket
					if (debugMode == TRUE) {
						printf("Expression Not Balanced\n");
						//printf("Unbalance detected\nExpression Not Balanced just like my life\n");
					}
					openBracket = TRUE;
					break;
				}
				
				popped = pop(&st1);
				if (debugMode == TRUE) {
					printf("Popped: %c\n", input[j]);
				}
				if (!isMatchingPair(popped, input[j])) { //not balanced - case for expecting a different closed bracket
					if (debugMode == TRUE) {
						printf("Expression Not Balanced\n");
						//printf("Unbalance detected\nExpression Not Balanced just like my life\n");
					}
					expecting = TRUE;
					break;
				}
			}
		}

		printf("%s\n", input);

		if (openBracket) { // case for missing open bracket
			openBracket = FALSE; //reset 
			char missingChar; //holds the char that is missing
			for (i = 0; i < index; i++) {
				printf(" ");
			} 

			//determines which open bracket is missing
			if (isMatchingPair('{', input[j])) {
				missingChar = '{';
			}
			else if (isMatchingPair('(', input[j])) {
				missingChar = '(';
			}
			else if (isMatchingPair('[', input[j])) {
				missingChar = '[';
			}
			else {
				missingChar = '<';
			} 

			printf("^ missing %c\n", missingChar);
		}
		else if (expecting) { // case for expecting a different closed bracket
			expecting = FALSE; //reset 
			char expectingChar; //holds the char that is missing
			for (i = 0; i < index; i++) {
				printf(" ");
			}

			//determines which open bracket is missing
			if (isMatchingPair(popped, '}')) {
				expectingChar = '}';
			}
			else if (isMatchingPair(popped, ')')) {
				expectingChar = ')';
			}
			else if (isMatchingPair(popped, ']')) {
				expectingChar = ']';
			}
			else {
				expectingChar = '>';
			}

			printf("^ expecting %c\n", expectingChar);
		} 
		else if (size(&st1) != 0) { //if the list is not empty - case for missing closed bracket

			char endMissingChar; //holds the char that is missing
			index++; //exception cause needs to point to empty space at the end
			for (i = 0; i < index; i++) {
				printf(" ");
			}

			popped = top(&st1);
			//determines which open bracket is missing
			if (isMatchingPair(popped, '}')) {
				endMissingChar = '}';
			}
			else if (isMatchingPair(popped, ')')) {
				endMissingChar = ')';
			}
			else if (isMatchingPair(popped, ']')) {
				endMissingChar = ']';
			}
			else {
				endMissingChar = '>';
			}

			printf("^ missing %c\n", endMissingChar);
		}
		else {
			printf("Expression is balanced\n");
		}

		clear(&st1); //clears the loop for the next run
		/* run the algorithm to determine is input is balanced */

	}

	freeUp(&st1);
	printf("\nGoodbye\n");
	return 0;
}