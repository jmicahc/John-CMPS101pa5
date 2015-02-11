// John Collins
// Jomicoll
// 11/24/2014
// Programming Assignment 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

// Return frequency of a character in a string.
int getfrequency(char str[160], char c)
{
  int count = 0;

  for (int m = 0; str[m]; m++)
  {
    if (str[m] != c)
      count++;
  }
  return count;
}

// Returns a pointer to an integer array of numbers
// parsed from 'line' based on 'delim'.
int* getlnums(char line[160], char delim)
{
  int index;
  int i = 0;

  int freq = getfrequency(line, delim);
  int *nums = malloc(sizeof(int) * (freq + 1)); //# separators = n - 1.

  for (char *e = strchr(line, delim); e != NULL; e = strchr(line, delim) )
  {
    index = (int) (e - line);
    line[index] = '\0';
    nums[i++] = atoi(line);
    line = (line + index * (sizeof(char))) + 1;
  }
  nums[i++] = atoi(line);
  return nums;
}

//Builds graph based upon input file format specified in 
//Assignment specification. No preconditions are checked.
Graph buildGraph(FILE *f_in)
{
  int order;
  char buf[160];

  if (fgets(buf, sizeof(buf), f_in) != NULL)
    order = atoi(buf);

  Graph G = newGraph(order);

  //add edges
  while (fgets(buf, sizeof(buf), f_in) != NULL)
  {
    int *nums = getlnums(buf, ' ');
    if (nums[0] != 0)
    {
      addArc(G, nums[0], nums[1]);
      free (nums);
    }
    else
    {
      free (nums);
      return G;
    }
  }
  fprintf(stderr, "Error occurred when reading file, \
      no '0 0' line found. Exiting");
  exit ( EXIT_FAILURE );
}


// Precondition: file pointer points to the line after the
//               first '0 0' row.
//
// Function for doing dirty work. Prints assigment specific 
// information. Nothing in this function is robust.
void printOutput(Graph G, FILE* f_out)
{
  fprintf(f_out, "Adjacency list representation of G:\n");
  printGraph(f_out, G);
  fprintf(f_out, "\n");

  List S = newList();
  for (int i = 1; i <= getOrder(G); i++)
    append(S, i);

  DFS(G, S);
  Graph trans = transpose(G);
  DFS(trans, S);

  int num_components = 0;
  for (moveTo(S, 0); getIndex(S) != -1; moveNext(S))
      if (getParent(trans, getElement(S)) == NIL)
          num_components++;
  fprintf(f_out, "G contains %d strongly connected components:\n", num_components);

  List *C = malloc(sizeof(List) * num_components);
  int i = -1;
  for (moveTo(S, 0); getIndex(S) != -1; moveNext(S))
  {
    if (getParent(trans, getElement(S)) == NIL)
      C[i+=1] = newList();
    append(C[i], getElement(S));
  }
  for (int i = num_components-1; i >= 0; i--)
  {
    fprintf(f_out, "Component %d: ", num_components - i);
    printList(f_out, C[i]);
    freeList(&C[i]);
    fprintf(f_out, "\n");
  }
  freeList(&S);
  free(C);
  freeGraph(&G);
  freeGraph(&trans);
}


int main(int argc, char **argv)
{
  if (argc != 3)
  {
    fprintf(stderr, "Error, wrong number of arguments\n");
    exit ( EXIT_FAILURE );
  }
  FILE *f_in;
  FILE *f_out;

  f_in = fopen(argv[1], "r");
  f_out = fopen(argv[2], "w");

  if (!f_in || !f_out)
  {
    fprintf(stderr, "Error when opening file. It may not exist\n");
    exit ( EXIT_FAILURE );
  }

  Graph G = buildGraph(f_in);
  printOutput(G, f_out);
  fclose(f_in);
  fclose(f_out);
  exit ( EXIT_SUCCESS );
}

