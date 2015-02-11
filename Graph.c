// John Collins
// jomicoll
// 11/24/2014
// Programming Assignment 4


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj
{
  int order;
  int size;

  // Source of most recient DFS call.
  int source;

  // pointer to an array of Lists whose ith element contains the neighbors of
  // vertex i.
  List *neighbors;

  // pointer to an array of ints whose ith element is the color of vertex i.
  int *colors;

  //pointer to an array of ints whose ith element is the parent of vetex i.
  int *parents;

  // pointer to an array of ints whose ith lement is the distance from the (most recent)
  // source to vertex i.
  int *sources;

  // a poitner to an array of ints whose ith element is the start times after
  // (most recent) DFS.
  int *discover;

  // a pointer to an array of ints whose ith element is the finish time after
  // (most recent) DFS.
  int *finish;
} GraphObj;



/*** Constructors-Destructors ***/

// Returns a Graph pointing to a newly creating GraphObj representing a graph
// having n vertices on n edges.
Graph newGraph(int n)
{
  Graph graph = malloc (sizeof (GraphObj));
  graph->source = NIL;

  // BFS fields
  graph->neighbors = malloc (sizeof(List) * (n + 1));
  graph->colors = malloc (sizeof (int) * (n + 1));
  graph->parents = malloc (sizeof (int) * (n + 1));
  graph->sources = malloc (sizeof (int) * (n + 1));

  // DFS fields
  graph->discover = malloc (sizeof(int) * ( n + 1));
  graph->finish = malloc (sizeof(int) * (n + 1));

  graph->size = 0;
  graph->order = n;
  for (int i = 1; i <= n; i++)
  {
    graph->neighbors[i] = newList();
    graph->colors[i] = 0;
    graph->parents[i] = 0;
    graph->sources[i] = INF;
    graph->discover[i] = UNDEF;
    graph->finish[i] = UNDEF;
  }
  return graph;
}

//  Fress all dynamic memory associated with the Graph *pg, then sets the handle
//  *pG to NULL.
void freeGraph(Graph *pG)
{
  for (int i = 1; i <= (*pG)->order; i++)
  {
    freeList(&(*pG)->neighbors[i]);
  }
  free ((*pG)->colors);
  free ((*pG)->neighbors);
  free ((*pG)->parents);
  free ((*pG)->sources);
  free ((*pG)->discover);
  free ((*pG)->finish);
  free (*pG);
  *pG = NULL;
}



/*** Access Functions ***/



// Returns the "Order" field value.
int getOrder(Graph G)
{
  return G->order;
}

// Retruns the "Size" field value.
int getSize(Graph G)
{
  return G->size;
}

// Returns the source vertex most recently used in function BFS(),
// or NIL if BFS() has not yet been called.
int getSource(Graph G)
{
  return G->source;
}

// Precondition: 1 <= u <= getOrder(G).
//
// Returns the parent of vertex u in the Breadth-First tree created
// by BFS(), or NIL if BFS() has not yet been called.
int getParent(Graph G, int u)
{
  if (1 <= u && u <= getOrder(G))
    return G->parents[u];
  else
  {
    fprintf(stderr, "@getParent: error, given vertex is not defined.\n");
    exit ( EXIT_FAILURE );
  }
}

// Returns the discover time of vertex u after DFS.
int getDiscover(Graph G, int u)
{
  if (1 <= u && u <= getOrder(G))
    return G->discover[u];
  else
  {
    fprintf(stderr, "@getDiscover: error, given vertex is not in graph.\n");
    exit ( EXIT_FAILURE );
  }
}

// Returns the finish time of vertex u after DFS);
int getFinish(Graph G, int u)
{
  if (1 <= u && u <= getOrder(G))
    return G->finish[u];
  else
  {
    fprintf(stderr, "@getFinish: error, given vertex is not in graph.\n");
    exit ( EXIT_FAILURE );
  }
}

// Precondition: 1 <= u <= getOrder(G).
//
// Returns the the distance from the most recent BFS source to vertex
// u, or INF if BFS() has not yet been called.
int getDist(Graph G, int u)
{
  if (1 <= u && u <= getOrder(G))
  {
    return G->sources[u];
  }
  else
  {
    fprintf(stderr, "@getDist: error, given vertex is not in graph.\n");
    exit ( EXIT_FAILURE );
  }
}

// Precondition: getSource(G) != NIL
//
// *** this function must be called before getPath() ***
//
// Appends to the List L the vertices of a shortest path in G
// from source to u, or appends to L the value NIL if no such path exists.
void getPath(List L, Graph G, int u)
{
  if (getSource(G) != NIL)
  {
    int v = u;

    for (int i = 1; i < G->sources[u] + 1; i++)
    {
      prepend(L, v);
      v = G->parents[v];
    }
  }
  else
  {
    fprintf(stderr, "@getPath: error, BFS was not called most recently..");
    exit ( EXIT_FAILURE );
  }
}


/*** Manipulation Proceddures ***/



// Deletes all edges of G, restoring it to its original (no edge) state.
// Note, this is called a null graph in graph theory literature).
void makeNull(Graph G)
{
  for (int i = 1; i <=G->order; i++)
  {
    clear(G->neighbors[i]);
    G->colors[i] = 0;
    G->parents[i] = 0;
    G->sources[i] = NIL;
  }
}

// Preconditions: (1) 1 <= u <= getOrder(G).
//               (2) 1` <= v <= getOrder(G).
//
// Inserts a new edge joining u to v, i.e. u is added to the Adjacency
// List of v, and v to the adjacency List of u.
void addEdge(Graph G, int u, int v)
{
  // NOTE: implementation must maintain these lists in sorted order
  // by increasing vertex labels.
  if ( 1 <= u  && u <= getOrder(G) && 1 <= v && v <= getOrder(G)) 
  {
    List L;
    int e;
    int uv[2] = {u, v};
    for (int i = 0; i < 2; i++) 
    {
      L = G->neighbors[uv[i]];
      e = (i == 1) ? uv[0] : uv[1];
      for (moveTo(L, 0); getIndex(L) != -1; moveNext(L))
      {
        if (getElement(L) > e)
        {
          insertBefore(L, e);
          break;
        }
        else
          moveNext(L);
      }
      if (getIndex(L) == -1)
        append(L, e);
    }
  }
  else
  {
    fprintf(stderr, "Error, arguments u or v are not defined");
    exit ( EXIT_FAILURE );
  }
}


// Preconditions: (1) 1 <= u <= getOrder(G).
//               (2) 1 <= v <= getOrder(G).
//
// Inserts a new directed edge from u to v, i.e. v is added to the
// adjacency List of u (but not u to the adjacency List of V).
void addArc(Graph G, int u, int v)
{
  if ( 1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G))
  {
    List L = G->neighbors[u];
    for (moveTo(L, 0); getIndex(L) != -1; moveNext(L)) 
    {
      if (getElement(L) > v)
      {
        insertBefore(L, v);
        break;
      }
      else
        moveNext(L);
    }
    if (getIndex(L) == -1)
      append(L, v);
  }
  else
  {
    fprintf(stderr, "Error, arguments u or v are not defined");
    exit ( EXIT_FAILURE );
  }
}

// Runs the BFS algorithm on the Graph G with source s, setting the
// color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s)
{
  G->source = s;
  for (int i = 1; i <= G->order; i++)
  {
    G->colors[i] = 0;
    G->parents[i] = NIL;
    G->sources[i] = INF;
  }
  G->colors[s] = 1;
  G->sources[s] = 0;
  G->parents[s] = NIL;
  List Q = newList();

  append(Q, s);
  moveTo(Q, 0);

  while (length(Q) > 0)
  {
    int u = front(Q);
    deleteFront(Q);
    List adj = G->neighbors[u];
    for (moveTo(adj, 0); getIndex(adj) != -1; moveNext(adj))
    {
      int v = getElement(adj);
      if (G->colors[v] == 0)
      {
        G->colors[v] = 1;
        G->sources[v] = G->sources[u] + 1;
        G->parents[v] = u;
        append(Q, v);
      }
    }
    G->colors[u] = 2;
  }
  freeList(&Q);
}

// Private helper funciton for DFS
void VISIT(Graph G, List S,  int  u, int *time)
{
  *time = *time + 1;
  G->discover[u] = *time;
  G->colors[u] = 1;
  List adj = G->neighbors[u];
  for (moveTo(adj, 0); getIndex(adj) != -1; moveNext(adj))
  {
    int v = getElement(adj);
    if (G->colors[v] == 0)
    {
      G->parents[v] = u;
      VISIT(G, S, v, time);
      prepend(S, v);
    }
  }
  G->colors[u] = 2;
  *time += 1;
  G->finish[u] = *time;
}

// Preconditions: getLength(s) == getOrder(G)
//
// Performs depth first search on G in order given by S.
//
// S has two purposes. First, it specifies the order in which vertices are 
// processed in the main loop. Second, upon completion of DFS, S contains an ordering
// of vertices in decreasing finish times. So for every vertex that is popped
// from front of S (i.e. every call to visit), one is append to back of S.
void DFS(Graph G, List S)
{
  if (length(S) == G->order)
  {
    for (int u = 1; u <= G->order; u++)
    {
      G->colors[u] = 0;
      G->parents[u] = NIL;
    }
    int time = 0;

    for (moveTo(S, 0); getIndex(S) != -1; moveNext(S))
    {
      int u = getElement(S);

      if (G->colors[u] == 0)
      {
        VISIT(G, S, u, &time);
        prepend(S, u);
      }
    }
    for (int i = 0; i < G->order; i++)
      deleteBack(S);
  }
  else
  {
    fprintf(stderr, "@DFS: erorr, S and G are different lengths.");
    exit ( EXIT_FAILURE );
  }
}



/*** Other operations ***/

// Returns a reference to a new graph which is a copy of G.
Graph copyGraph(Graph G)
{
  Graph nG = newGraph(G->order);
  for (int i = 1; i <= G->order; i++)
  {
    nG->neighbors[i] = copyList(G->neighbors[i]);
    nG->colors[i] = G->colors[i];
    nG->parents[i] = G->parents[i];
    nG->sources[i] = G->sources[i];
    nG->finish[i] = G->finish[i];
    nG->discover[i] = G->discover[i];
  }
  nG->source = G->source;
  nG->size = G->size;
  return nG;

}



// Returns a reference to a new Graph object representing the
// transpose of G. Trans(G) is obtained by reversing the directions
// on all edges of G.
Graph transpose(Graph G)
{
  Graph trans = newGraph(G->order);
  for (int i = 1; i <= G->order; i++)
  {
    List L = G->neighbors[i];
    for (moveTo(L, 0); getIndex(L) != -1; moveNext(L))
    {
      int u = getElement(L);
      addArc(trans, u, i);
    }
  }
  return trans;
}

// prints the adjacency list representation of G to the file pointed 
// to by out.
void printGraph(FILE* out, Graph G)
{
  List L;
  for (int i = 1; i <= G->order; i++)
  {
    L = G->neighbors[i];
    fprintf(out, "%d: ", i);
    printList(out, L);
    fprintf(out, "\n");
  }
}
