#include "status.h"

typedef void* STACK;

void clear_keyboard_buffer();

STACK stack_init_default();

Status stack_push(STACK hStack, char c);
char stack_top(STACK hStack);
Status stack_pop(STACK hStack);
Boolean stack_is_empty(STACK hStack);
Boolean check_string(char str[]);

Status stack_destroy(STACK* hStack);
