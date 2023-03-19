# ADT 
#### Task 1 - CPP Course<br/>
## Introduction <br/>
In this assignment, I implement a general adaptive array in the C language.<br/>
An adaptive array is an array that changes its size so that any reference to a non-negative index is normal, when a reference is made to an index where no value has been placed then NULL is returned.<br/>
## Implementation explanation:<br/>
I instantiated the structure with an array of variable size.<br/>
That is, we will save an array of general pointers and every time we receive a placement to an index larger than our array, then we will copy the array to a large enough memory so that this reference will be valid.<br/> In addition, I made sure to keep the size of the current array in the structure and in addition Pointers to user functions for copying and deleting members.<br/>
## Author <br/>
Batel Cohen<br/>
## Acknowledgements<br/>
https://github.com/cpp-exercises/ADT
