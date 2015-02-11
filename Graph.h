#include "List.h"

#ifndef NIL
#define NIL 0
#ifndef INF
#define INF -1
#ifndef UNDEF
#define UNDEF -3


//define type Graph
typedef struct GraphObj* Graph;


/*** Constructors-Destructors ***/


// Returns a Graph pointing to a newly crewated GRaphObj representing a
// graph having n vertices on no edges.
Graph newGraph(int n);


// Frees all dynamic memory associated with Graph *pG, then
// sets the handle *pG to NULL
void freeGraph(Graph* G);

/*** Access functions***/

// Returns the "order" field value.
int getOrder(Graph G);


// Returns the "Size" field value.
int getSize(Graph G);


// Returns the source vertex most recently used in function BFS(),
// or NIL if BFS() has not yet been called.
int getSource(Graph G);

// Returns the parent of vertex u in the Breadth=First tree
// created by BFS(), or NIL if BFS() has not yet been called.
int getParent(Graph G, int u);

// Returns the discover time of vertex u after DFS.
int getDiscover(Graph G, int u);

// Returns the vfinish time of vertext u after DFS
int getFinish(Graph G, int u);

// Returns the distance from the most recent BFS source to vertex
// u, or INF if BFS() has not yet been called. Functions getPath()
// appends to the List L the vertices of a shortest path in G from
// source to u, or appends to L the value NIL if no such point exists.
int getDist(Graph G, int u);


// Appends to the List L the vertices of a shortest path in G
// from source to u, or appends to L the value NIL if no such
// path exists.
void getPath(List L, Graph G, int u);


/*** Manipulation prodedures ***/

// Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G);

//Inserts a new edge joining u to v, i.e. us is added to the Adjacency
//List of v, and v is to the adjacency List of u.
void addEdge(Graph G, int u, int v);


//Inserts a new disrected edge from u to v, i.e. v is added to the 
//adjacency List of u (but not u to the adjacency List of V).
void addArc(Graph G, int u, int v);

// Runs the BFS algoritghm on the Graph G witbh source s, setting
// the color, distance, parent, and osurce fields of G accordingly.
void BFS(Graph G, int s);

// Precondition: (1) getLength(s)==getOrder(G)
//
// Performs depth first search on G.
void DFS(Graph G, List S);


/*** Other operations ***/

// returns a reference to a new graph object representing the
// transpose of G. Trans(G) is obtained by reversing the directions on
// all edges of G.
Graph transpose(Graph G);

//Prints the adjacency list representation of G to
//file pointed to by out.
void printGraph(FILE* out, Graph G);


#endif
#endif
#endif
