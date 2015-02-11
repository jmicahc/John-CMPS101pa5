// John Collins
// jomicoll
// CMPS101, Assignment 5
//
//-----------------------------------------------------------------------------
// GraphClient.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[])
{
   int i;
   int n=8;


   List S = newList();
   
   Graph G = newGraph(n);

   for(i = 1; i <= n; i++) 
     append(S, i);

   addArc(G, 1,7);
   addArc(G, 1,2);
   addArc(G, 2,4);
   addArc(G, 2,6);
   addArc(G, 3,4);
   addArc(G, 3,1);
   addArc(G, 3,7);
   addArc(G, 3,1);
   addArc(G, 3,3);
   addArc(G, 6,4);
   addArc(G, 6,2);
   addArc(G, 8,1);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   printGraph(stdout, G);

   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   Graph T = transpose(G);
   Graph C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   for(i = 1; i <= n; i++){
      fprintf(stdout, "%d: discover: %2d. Finsih: %2d. Parent: %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}


