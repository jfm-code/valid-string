# Valid Parenthesis String Solver

This project provides a solution to the Valid Parenthesis String problem using two different implementations of a stack data structure in C:

- Stack implemented using an Array (stack_array.c)
- Stack implemented using a Linked List (stack_linkedlist.c)

## Problem Description
The Valid Parenthesis String problem involves determining if a string containing just the characters (, ), {, }, [ and ] is a valid string. A string is considered valid if:

- Open brackets must be closed by the same type of brackets.
- Open brackets must be closed in the correct order.
- Every close bracket has a corresponding open bracket of the same type.

## Test Cases
The following test cases are included in main.c to verify the correctness of the stack implementations for solving the Valid Parenthesis String problem:

 - ([]) -> Yes
- (([{}]))) -> No
- ([()[]()])() -> Yes
- {[]) -> No
- [[} -> No
- )[ -> No
- [()]{}{[()()]()}([()[]()])() -> Yes
- [(]) -> No
- {()}[] -> Yes
  
These test cases will check if the given sequences of brackets are balanced, ensuring the stack implementation correctly solves the Valid Parenthesis String problem.
