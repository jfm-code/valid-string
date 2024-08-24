#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "logger.h"

struct node;
typedef struct node Node;
struct node
{
	char data;
	Node* next;
};

struct stack
{
	Node* top;
};
typedef struct stack Stack;

STACK stack_init_default()
{
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL)
	{
		LOG_DEBUG("stack_init_default - malloc failed in pStack\n");
		return NULL;
	}

	pStack->top = NULL;
	LOG_DEBUG("Successful creating stack %p\n", pStack);
	return pStack;
}

Status stack_push(STACK hStack, char c)
{
	Stack* pStack = (Stack*)hStack;
	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
	{
		LOG_DEBUG("stack_push - malloc failed in temp\n");
		return FAILURE;
	}
	temp->data = c;
	temp->next = pStack->top;
	pStack->top = temp;
	return SUCCESS;
}

char stack_top(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	if(stack_is_empty(pStack) == FALSE)
		return pStack->top->data;
}

Status stack_pop(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	if (stack_is_empty(pStack) == FALSE)
	{
		Node* temp = pStack->top;
		pStack->top = pStack->top->next;
		free(temp);
		return SUCCESS;
	}
	else
		return FAILURE;
}

Boolean stack_is_empty(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	if (pStack->top == NULL)
		return TRUE;
	else
		return FALSE;
	
}

Status stack_destroy(STACK* hStack)
{
	Stack* pStack = (Stack*) *hStack;
	Node* current_node = pStack->top;
	Node* next_node = pStack->top;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	free(pStack);
	*hStack = NULL;
	return SUCCESS;
	/*
	In the old stack_destroy function, I am only freeing the Stack struct itself, 
	but I am not freeing the Node structs inside Stack struct that were created using malloc. 
	This will result in memory leaks.To properly free the memory, I should traverse 
	the linked list and free each node.
	*/
}

Boolean check_string(char str[])
{
	STACK hStack = stack_init_default();
	Boolean flag = FALSE;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
			stack_push(hStack, str[i]);
		else
		{
			if (str[i] == ')')
			{
				if (stack_top(hStack) == '(')
				{
					flag = TRUE;
					stack_pop(hStack);
				}
				else return FALSE;
			}
			else if (str[i] == '}')
			{
				if (stack_top(hStack) == '{')
				{
					flag = TRUE;
					stack_pop(hStack);
				}
				else return FALSE;
			}
			else if (str[i] == ']')
			{
				if (stack_top(hStack) == '[')
				{
					flag = TRUE;
					stack_pop(hStack);
				}
				else return FALSE;
			}
		}
	}
	if (flag == TRUE && stack_is_empty(hStack) == TRUE)
	{
		stack_destroy(&hStack);
		return TRUE;
	}
	else
	{
		stack_destroy(&hStack);
		return FALSE;
	}
}

void clear_keyboard_buffer()
{
	char c;
	scanf("%c", &c);
	while (c != '\n')
	{
		scanf("%c", &c);
	}
}
