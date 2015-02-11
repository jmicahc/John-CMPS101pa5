// John Collins
// jomicoll
// cmps101


#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct listNode
{
  int elem;
  struct listNode *prev;
  struct listNode *next;
} listNode;

typedef listNode* Node;


typedef struct ListObj
{
  Node front;
  Node back;
  Node cursor;
  int length;
  int cursorPtr;
} ListObj;


// Constructor
List newList (void)
{
  List L;
  L = malloc (sizeof (ListObj));
  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
  L->length = 0;
  L->cursorPtr = -1;
  return L;
}

// Returns The number of elements in the list.
int length(List L)
{ 
  return L->length;
}

// Returns the index of the cursor element in the list,
//  or returns -1 if the cursor element is undefined.
int getIndex(List L)
{
  return L->cursorPtr;
}


// Returns the index of the cursor element in the list,
 // or returns -1 if the cursor element is undefined.
int getElement(List L)
{
  if (length(L) > 0 && getIndex(L) >= 0)
  {
    return L->cursor->elem;
  }
  else
  {
    if (!length(L) > 0)
      fprintf(stderr, "@getElement: Error, list is empty.\n");
    else
      fprintf(stderr, "@getElement: Error, cursor undefined.\n");
    exit(EXIT_FAILURE);
  }
}


// Returns true if list 1 and list 2 are of length n (where n>=0)
// and consist of same sequence of elements.
int equals(List L1, List L2)
{
  Node top = L1->front;
  Node bot = L2->front;
  while (1)
  {
    if (top == NULL && bot == NULL)
      return 1;
    else if (top == NULL || bot == NULL)
      return 0;
    else if (top->elem != bot->elem)
      return 0;

    top = top->next;
    bot = bot->next;
  }
}

// Precondition: length > 0.
//
//  Returns the front of the list.
int front(List L)
{
  if (length(L) > 0)
  {
    return L->front->elem;
  }
  else
  {
    fprintf(stderr, "@front: Error, empty list.\n");
    exit( EXIT_FAILURE );
  }
}


// Preconditions: length(L) > 0
//
//  Returns the back element of the list.
int back(List L)
{
  if (length(L) > 0)
  {
    return L->back->elem;
  }
  else
  {
    fprintf(stderr, "@front: Error, empty list.\n");
    exit( EXIT_FAILURE );
  }
}

// Preconditions: (1) cursor Index > 0
//                (2) cursor index <= Length(List) - 1
// 
// Moves the cursor backwards (toward the front) once. If the cursor
// moves off the list, it becomes undefined.
void movePrev(List L)
{
  if (getIndex(L)>0 && getIndex(L) <= (length(L) - 1))
  {
    L->cursor = L->cursor->prev;
    L->cursorPtr -= 1;
  }
  else
  {
    L->cursor = NULL;
    L->cursorPtr = -1;
  }
}


// Preconditions: (1) cursor index >= 0
//                (2) cursor index < Length(list) -1
//
// Cursor is set to null of it is moved out of the range
// over which List is defined.
void moveNext(List L)
{
  if (getIndex(L) >= 0 && getIndex(L) < (length(L) -1))
  {
    L->cursor = L->cursor->next;
    L->cursorPtr += 1;
  }
  else
  {
    L->cursor = NULL;
    L->cursorPtr = -1;
  }
}


// Preconditions: (1) i >= 0
//                (2) i <= length() -1
// If i is not an index of the list, the cursor
// becomes undefined.
void moveTo(List L, int i)
{
  if (getIndex(L)==-1)
  {
    L->cursor = L->front;
    if (length(L) > 0) {
        //L->cursor = L->front;
        L->cursorPtr = 0;
    }
  }
  while (getIndex(L)<i && getIndex(L)!=-1)
  {
    moveNext(L);
  }
  while (getIndex(L)>i && getIndex(L)!=-1)
  {
    movePrev(L);
  }
}

// Attaches the given eleement in front of the back element
// of the list. If the list is empty, the first element is created.
void append(List L, int data)
{
  if (L->back != NULL)
  {
    Node temp = malloc (sizeof (listNode)); // malloc (sizeof (struct listNode));
    temp->next = NULL;
    temp->elem = data;
    temp->prev = L->back;
    L->back->next = temp;
    L->back = temp;
  }
  else
  {
    Node first = malloc (sizeof (listNode)); // = malloc (sizeof (struct listNode));
    first->next = NULL;
    first->prev = NULL;
    L->front = first;
    L->front->elem = data;
    L->back = first;
    L->back->elem = data;
  }
  L->length++;
}

//Attaches the given element beind the front of the list. If the
//list is empty, the first element is created.
void prepend(List L, int data)
{
  if (L->front != NULL)
  {
    Node temp = malloc (sizeof (listNode));
    temp->prev = NULL;
    temp->elem = data;
    L->front->prev = temp;
    temp->next = L->front;
    L->front = temp;
  }
  else
  {
    Node first = malloc (sizeof (listNode));
    first->prev = NULL;
    first->next = NULL;
    L->front = first;
    L->front->elem = data;
    L->back = first;
  }
  L->length += 1;
  if (getIndex(L) >= 0)
  {
    L->cursorPtr += 1;
  }
}

//Preconditions: (1) Length(l) > 0
//               (2) cursor index >= 0
//Inserts the given element in front of the cursor pointer if and
//only if the cursor is defined. Otherwise, an error is printed to stderr
//and the program exits.
void insertBefore(List L, int data)
{
  if (length(L) > 0 && getIndex(L) >= 0)
  {
    if (L->cursor->prev == NULL)
    {
      prepend(L, data);
    }
    else
    {
      Node temp = malloc (sizeof (listNode));
      temp->elem = data;
      temp->next = L->cursor;
      temp->prev = L->cursor->prev;
      L->cursor->prev->next = temp;
      L->cursor->prev = temp;
      L->cursorPtr++;
      L->length++;
    }
  }
  else
  {
    if (!length(L) > 0)
      fprintf(stderr, "Error, empty list.\n");
    else
      fprintf(stderr, "Error, undefined cursor.\n");
    exit( EXIT_FAILURE );
  }
}


// Preconditions: (1) Length > 0
//                (2) cursor index >= 0
void insertAfter(List L, int data)
{
  if (length(L) > 0 && getIndex(L) >= 0)
  {
    if (L->cursor->next == NULL)
    {
      append(L, data);
    }
    else
    {
      Node temp = malloc (sizeof (listNode));
      temp->elem = data;
      temp->prev = L->cursor;
      temp->next = L->cursor->next;
      L->cursor->next->prev = temp;
      L->cursor->next = temp;
      L->length++;
    }
  }
  else
  {
    if (!length(L) > 0)
      fprintf(stderr, "@insertAfter: Error, empty list.\n");
    else
      fprintf(stderr, "@insertAfter: Error, undefined cursor.\n");
    exit ( EXIT_FAILURE );
  }
}


//Sets all of the list pointers to null (undefined).
void clear(List L)
{
  if (length(L) > 0) // NOTE INVARIANT: Length(L) == 1 --> back = front.
  {
    Node temp = L->front->next;
    for (; temp != NULL; temp = temp->next)
    {
      free (temp->prev);
      temp->prev = NULL;
    }
    free (L->back);
    L->front = NULL;
    L->cursor = NULL;
    L->back = NULL;
    L->cursorPtr = -1;
    L->length = 0;
  }
}

// Preconditions: (1) length(List) > 0
// Deletes the front element of the list. If the
// cursor points at the front, it becomes undefiened.
void deleteFront(List L)
{
  if (length(L) > 0)
  {
    if (length(L) == 1)
    {
      clear(L);
    }
    else if (L->cursor == L->front) //precond: front has next
    {
      L->front = L->front->next;
      free (L->cursor);
      L->cursor = NULL;
      L->front->prev = NULL;
      L->cursorPtr = -1;
      L->length--;
    }
    else
    {
      L->front = L->front->next;
      free(L->front->prev);
      L->front->prev = NULL;
      L->cursor--;
      if (L->cursorPtr != -1)
        L->cursorPtr--;
      L->length--;
    }
  }
  else
  {
    fprintf(stderr, "@deleteFront: Error, list is empty.\n");
    exit ( EXIT_FAILURE );
  }
}




// Preconditions: (1) length(List) > 0
// Deletes the front element of the list. If the
// cursor points at the front, it becomes undefiened.
void deleteBack(List L)
{
  if (length(L) > 0)
  {
    if (length(L) == 1)
    {
      clear(L);
    }
    else if (L->cursor == L->back)
    {
      L->back = L->back->prev;
      free (L->cursor);
      L->cursor = NULL;
      L->back->next =NULL;
      L->cursorPtr = -1;
      L->length--;
    }
    else
    {
      L->back = L->back->prev;
      free (L->back->next);
      L->back->next = NULL;
      L->length--;
    }
  }
  else
  {
    fprintf(stderr, "@deleteBack: Error, list is empty.");
    exit ( EXIT_FAILURE );
  }
}


// Deletes the cursor element. The list is
// patched up around it.
void delete(List L)
{
  if (length(L) > 0 && getIndex(L)>= 0)
  {
    if (L->cursor==L->front)
    {
      deleteFront(L);
    }
    else if (L->cursor==L->back)
    {
      deleteBack(L);
    }
    else
    {
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      free (L->cursor);

      L->length--;
      L->cursorPtr = -1;
    }
  }
  else
  {
    if (!length(L)>0)
      fprintf(stderr, "@delete: Error, list empty.\n");
    else
      fprintf(stderr, "@delete: Error, cursor undefined.\n");
    exit( EXIT_FAILURE );
  }
}

// Frees all memory associated with list.
void freeList(List *pL)
{
  clear(*pL);
  free(*pL);
  *pL = NULL;
}


//Creates a deep copy of this list and returns it to the caller.
List copyList(List L)
{
  List newList = malloc(sizeof (ListObj));
  for (Node curr = L->front; curr != NULL; curr = curr->next)
  {
    append(newList, curr->elem);
  }
  newList->length = L->length;
  return newList;
}

// Writes a string represntation of the list to the given file,
// one line per item.
void printList(FILE *out, List L)
{
  Node curr = L->front;
  for (; curr != L->back && curr != NULL; curr = curr->next)
  {
    fprintf( out, "%d ", curr->elem);
  }
  if (L->back!=NULL)
  {
    fprintf( out,"%d", curr->elem);
  }
}
