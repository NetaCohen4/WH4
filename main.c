/*
Neta Cohen 
325195774
17/1/2023
Ex4
*/

#include <stdio.h> 
#include <stdlib.h> 
#include "graph.h" 
#include <math.h>
#include <ctype.h>
#include <limits.h>



int main()
{
    pnode help = NULL;
    pnode *root = &help;
    char ch;

    while (scanf("%c", &ch) != EOF)
    {
        // Users choises:

        // Building the graph
        if (ch == 'A') 
        {
            build_graph(root);
        }

        // Add node to the graph
        else if (ch == 'B')
        {
            insert_node(root);
        }

        // Delete node from the graph
        else if (ch == 'D')
        {
            delete_node(root);
        }

        // Find shortest path between two given nodes
        else if (ch == 'S')
        {
            int src = -1, dest = -1;
            scanf("%d %d", &src, &dest);
            int dis = shortsPath(*root, src, dest);
            printf("Dijsktra shortest path: %d \n", dis);
        }

        // Find shortest path that passes through given nodes
        else if (ch == 'T') 
        {
            TSP(*root);
        }
    }

    // Delete the gragh before exitting
    deleteGraph(root);

    return 0;
}
