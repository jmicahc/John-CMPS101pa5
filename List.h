// John Collins
// jomicoll
// 10/22/2014

//#ifndef _LIST_H_INCLUDE_
//#define _LIST_H_INCLUDE_

typedef struct ListObj* List;

//List constructor
List newList(void);

// Frees all memory associated with list.
void freeList(List* pL);

// Access functions -----------------------------------------------------------

// Returns the length of the list, which is exactly the number of 
// elements starting at 1.
int length(List L);

// Returns the index of the pointer, or -1 if no such pointer exists.
int getIndex(List L);

// Returns the front of the list.
int front(List L);

// Returns the back of the list.
int back(List L);

// Returns the element pointed at by the cursor
int getElement(List L);

// Returns true if the sequence of integers defined by A, matches
// the sequence defined by B.
int equals(List A, List B);

// Manipulation procedures ----------------------------------------------------

// Returns the list to the empty state.
void clear(List L);

// Moves the cursor to i, or sets it to -1 
// if is not a valid index.
void moveTo(List L, int i);

// Moves the cursor 1 step towards the front.
void movePrev(List L);

// Moves the cursor 1 step towards the back
void moveNext(List L);

// adds data behind front of list
void prepend(List L, int data);

// adds data behind back of list.
void append(List L, int data);

// Adds data immidiately before cusor position,
// if cursor is defined. Else, error is printed and
// program exits.
void insertBefore(List L, int data);

// Inserts data immidiately after cursor position.
void insertAfter(List L, int data);

// Deletes the front element of the list.
void deleteFront(List L);

// Deletes the back element of the list.
void deleteBack(List L);

// Deletes the cursor and its assocated data.
void delete(List L);

// Other operations -----------------------------------------------------------

//prints a character representation of the List. to
//file pointed at by 'out'.
void printList(FILE *out, List L);

//Returns a pointer to a deep copy of the List.
List copyList(List L);

//#endif
