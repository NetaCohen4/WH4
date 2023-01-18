/*
Neta Cohen 
325195774
17/1/2023
Ex4
*/

#ifndef GRAPH_
#define GRAPH_


typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ 
{
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ 
{
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;


typedef struct Dijkstra 
{
    pnode node;
    int weight;
    int infor;
    struct Dijkstra *next;
} dijkstra, *dijkstra_P;


void build_graph(pnode*);
void insert_node(pnode*);
void delete_node(pnode*);
void printGraph(pnode);
void deleteGraph(pnode*);
int shortsPath(pnode, int, int);
void TSP(pnode);



#endif

