#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "logger.h"

struct stack
{
	int size;
	int capacity;
	char* data; //an array to store characters
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

	pStack->data = (char*)malloc(sizeof(char*) * 10); //creating space for 10 characters
	if (pStack->data == NULL)
	{
		LOG_DEBUG("stack_init_default - malloc failed in pStack->data\n");
		free(pStack);
		return NULL;
	}

	pStack->size = 0;
	pStack->capacity = 10;
	LOG_DEBUG("Successful creating stack %p\n", pStack);
	return pStack;
}

Status stack_push(STACK hStack, char c)
{
	Stack* pStack = (Stack*)hStack;
	//resizing the stack
	if (pStack->size >= pStack->capacity)
	{
		char* temp = (char*)malloc(sizeof(char) * pStack->capacity * 2);
		if (temp == NULL)
		{
			LOG_DEBUG("stack_push - malloc failed in temp\n");
			return FAILURE;
		}
		else
		{
			//copying values
			for (int i = 0; i < pStack->size; i++)
			{
				temp[i] = pStack->data[i];
			}
			free(pStack->data);
			pStack->data = temp;
			pStack->capacity *= 2;
		}
	}
	//start pushing
	pStack->data[pStack->size] = c;
	pStack->size++;
	return SUCCESS;
}

char stack_top(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	if(stack_is_empty(pStack) == FALSE)
		return pStack->data[pStack->size - 1];
}

Status stack_pop(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	if (stack_is_empty(pStack) == FALSE)
	{
		pStack->size--;
		return SUCCESS;
	}
	else
		return FAILURE;
}

Boolean stack_is_empty(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	LOG_DEBUG("stack_is_empty - the current size is %d\n", pStack->size);
	if (pStack->size <= 0)
		return TRUE;
	else
		return FALSE;
}

Status stack_destroy(STACK* hStack)
{
	Stack* pStack = (Stack*) *hStack;
	free(pStack->data);
	free(pStack);
	*hStack = NULL;
	LOG_DEBUG("Destroying stack...\n");
	return SUCCESS;
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
