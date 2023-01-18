/*
Neta Cohen 
325195774
17/1/2023
Ex4
*/

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <limits.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

int long_a;
pnode myGraph;
int myWeight;

/*
Declared in Graph.h:
int shortsPath(pnode, int, int);
void TSP(pnode);
*/


// ShortestPath by dijkstra and helper functions:

dijkstra_P dijkstra_construction(pnode one, int makor)
{
    dijkstra_P root = NULL;
    dijkstra_P *dgk_p = &root;

    while (one != NULL)
    {                                       
        (*dgk_p) = (dijkstra_P)malloc(sizeof(dijkstra_P));
        if ((*dgk_p) == NULL)
        {
            printf("error");
            exit(0);
        }                                                                                                                   
        (*dgk_p)->node = one;
        if (one->node_num == makor)
        {                                        
            (*dgk_p)->weight = 0;
        }
        else
        {                                       
            (*dgk_p)->weight = INT_MAX;
        }
                                                                                                                                                               
        (*dgk_p)->infor = 0;
        (*dgk_p)->next = NULL;
        dgk_p = &((*dgk_p)->next);
        one = one->next;
    }                                    
                           
    return root;
}

// # removing by dijkstra #
void dijkstra_remove(dijkstra_P dijkstra)
{                                                                                   
    while (dijkstra != NULL)
    {                                                                                                                                                 
        dijkstra_P djk_p = dijkstra;
        dijkstra = dijkstra->next;                                          
        free(djk_p);
    }

}

dijkstra_P dijkstraP(dijkstra_P root, int recognize)
{                                                                                               
    while (root != NULL)                                                                    
    {                                                                       
        if (root->node->node_num == recognize)                                                                      
        {                                                                   
            return root;                                                                
        }                                                                   
        root = root->next;                                                          
    }   
                                                                                                 
    return NULL;                                                                    
}


// Helper function for shortsPath:
dijkstra_P Small_node(dijkstra_P root)                                      
{                                               
    dijkstra_P vertex = NULL;                               
    while (root != NULL)                                            
    {                                                       
        if ((!root->infor && root->weight < INT_MAX) && (vertex == NULL || vertex->weight < root->weight))
        {                                                   
            vertex = root;                                                      
        }                                                       
        root = root->next;                                                                      
    }                                                                       
    if (vertex != NULL)                                                                                 
    {                                                                       
       vertex->infor = 1;                                                                           
    }                                                                                                   
    return vertex;  
                                                                                                                          
}                                                                   

// # Function to find shortest Path in the graph #                                                               
int shortesPath(pnode root, int star, int end)                                                                                           
{                                                                                                   
    dijkstra_P pdijk_1 = dijkstra_construction(root, star);                                                                                          
    dijkstra_P d = Small_node(pdijk_1);                                                                 
    while (d != NULL)                                                                       
    {                                                           
        pedge edge = d->node->edges;   
                                                                                     
        while (edge != NULL)                                                          
        {                                                                   
            dijkstra_P node_1 = dijkstraP(pdijk_1, edge->endpoint->node_num);                                                      
            int newDist = d->weight + edge->weight;                                                               
            if (node_1->weight > newDist)                                                                           
            {                                                                                                   
               node_1->weight = newDist;                                                                            
            }                                                                               
            edge = edge->next;                                                             
        }  
                                                                                 
        d = Small_node(pdijk_1);                                                         
    }                                                    

    int length = dijkstraP(pdijk_1,end)->weight;                                                    
    if (length == INT_MAX)                                   
    {                                                                     
        length = -1;                                                      
    }                                                                 
    dijkstra_remove(pdijk_1);
    return length;                                                                       

}                                                                             



// TSP Algorithm function and helper functions:

void swap(int *array, int x, int y)                                                 
{                                                      
    int temp =array[x];                                            
    array[x] = array[y];                                                
   array[y] = temp;                                                      
} 


void cpy_deep(int *f, int *t, int array_len)                                   
{                                               
    for (int i = 0; i < array_len; i++)                                
    {
        t[i] = f[i];                                         
    }
}
                                                

void calculation_p(int *array, int array_len)
{
    int x = 0;
    for (int i = 0; i < array_len - 1; ++i)
    {
        int len = shortsPath(myGraph,array[i], array[i + 1]);
        if (len == -1)
        {
            x = INT_MAX;
            return;
        }
       x += len;
    }
    if (x < myWeight)
    {
        myWeight = x;
    }
}


void permotion(int s, int *arr, int array_len)
{
    // Finishing condition
    if (s == array_len - 1)
    {
        calculation_p(arr, array_len);
        return;
    }               

    for (int i = s; i < array_len; ++i)
    {
        int *tmp_array = (int *)(calloc(array_len, sizeof(int)));
        cpy_deep(arr, tmp_array, array_len);
        swap(tmp_array, s, i);
        // Recursive call
        permotion(s + 1, tmp_array,array_len);
        free(tmp_array);
    }

}


// # The TSP Algorithm #
void TSP(pnode root)
{
    long_a = -1;
	myWeight = INT_MAX;
    myGraph = root;
    scanf("%d", &long_a);

    int *myArr= (int *)(calloc(long_a, sizeof(int)));
    for (int i = 0; i < long_a; i++)
    {
        scanf("%d", &myArr[i]);
    }
                             
    int *arrCopy = (int *)(calloc(long_a, sizeof(int)));
    cpy_deep(myArr, arrCopy, long_a);
    permotion(0, arrCopy, long_a);
    free(myArr);
    free(arrCopy);
    if (myWeight == INT_MAX)
    {
        myWeight = -1;
    }
                      
    printf("TSP shortest path: %d \n", myWeight);

}
