/*
Neta Cohen 
325195774
17/1/2023
Ex4
*/
#include <stdio.h> 
#include <stdlib.h> 
#include "graph.h"
#include <string.h>
#include <ctype.h>
#include <limits.h>

/*
Declared in Graph.h:
void build_graph (pnode*);
void insert_node (pnode*);
void delete_node(pnode*);
void printGraph(pnode);
void deleteGraph(pnode*);
*/

// # function that builds the graph #
void build_graph(pnode *root) 
{
    deleteGraph(root);
    int nodesNum = 0;
    // Getting number of nodes in the gragh from user
    scanf("%d", &nodesNum);
    char node = 'A';
    // Gettting nodes from user and inserting them
    scanf("%c", &node);
    for (int i = 0; i < nodesNum; i++)
    {
        scanf("%c", &node);
        insert_node(root);
    }
}

//helper function for insert_node
// # function that return pointer to node by his id #
pnode get_node(int nodeID, pnode *root)
{
    pnode temp = *root;
    while (temp != NULL)
    {
        if (temp->node_num == nodeID)
        {
            return temp;
        }
        else
        {
            temp = temp->next;
        }
    }
    return NULL;
}

// # function that inserts a node to graph #
void insert_node(pnode *root)
{
    int nodeID = -1;
    // getting id of the node the user want to insert
    scanf("%d", &nodeID);
    // checking wether this node already exists 
    pnode node_exists = get_node(nodeID,root);
    // if node doesn't exist
    if (node_exists == NULL)
    {
        node_exists = (pnode)malloc(sizeof(node));
        if (node_exists == NULL)
        {
            return;
        }
        node_exists->node_num = nodeID;
        node_exists->next = *root;
        node_exists->edges = NULL;
        *root = node_exists;
    }
    // if node exists
    else
    {
        pedge pdg = node_exists->edges;
        while (pdg != NULL)
        {
            pedge temp = pdg->next;
            free(pdg);
            pdg = temp;
        }
        node_exists->edges = NULL;
    }

    int dst = -1; //desteny
    pedge *new_e = &(node_exists->edges);
    int d = scanf("%d", &dst);

    while (d != 0 && d != EOF)
    {
        pnode dst_node = get_node(dst, root);
        if (dst_node== NULL)
        {
            dst_node = (pnode)malloc(sizeof(node));
            if (dst_node == NULL)
            {
                return;
            }
            dst_node->node_num = dst;                                                   
            dst_node->edges = NULL;
            dst_node->next = *root;                             
            *root =dst_node;
        }

        // getting the weight from user
        int weight = -1;
        scanf("%d", &weight);

        *new_e = (pedge)malloc(sizeof(edge));
        if ((*new_e) == NULL)
        {
            return;
        }
        (*new_e)->weight = weight;
        (*new_e)->endpoint = dst_node;
        (*new_e)->next = NULL;
        new_e = &((*new_e)->next);
        d = scanf("%d", &dst);
    }

}

// # function that deletes node from the graph #
void delete_node(pnode *root)
{ 
    int nodeID;
	scanf("%d", &nodeID);
	pnode copy = *root;
	while (copy != NULL) 
    {
		if ((copy->edges != NULL) && (copy->edges->endpoint->node_num == nodeID))
        {
			pedge new = copy->edges;
			copy->edges = copy->edges->next;
			free(new);                                                                      
		}
		copy = copy->next;
	}

	pnode temp1 = *root, next = *root;
	next = temp1->next;

	while (next) 
    {
		if (next->node_num == nodeID) 
        {
			temp1->next = next->next;
			free(next);
			next = temp1;
		}
		else 
        {
			temp1 = next;
			next = temp1->next;
		}
	}

}

// # function that prints the graph #
void printGraph(pnode root) 
{
    // starting with root node 
    pnode temp = root;
    // while there are more nodes 
    while (temp != NULL)                    
    {
        printf("Node %d: ", temp->node_num); 
        pedge edgs = temp->edges;  
        // while there are more edges           
        while (edgs != NULL)
        {
            // print node ID and weight                                
            printf("D= %d: W= %d, ", edgs->endpoint->node_num, edgs->weight);
            edgs = edgs->next;
        }
        printf("\n");
        temp = temp->next;
    } 
}

// # function that deletes the graph #                                             
void deleteGraph(pnode* root)
{
    // starting with root node                               
    pnode temp = *root; 
    // while there are more nodes                                  
    while (temp !=  NULL) 
    {
        pedge edgs = temp->edges;
        // while there are more edges                           
        while (edgs != NULL)
        {
            pedge temp1 = edgs;
            edgs = edgs->next;
            free(temp1);            
        }
        pnode temp2 = temp;
        temp = temp->next;
        free(temp2);
    }               

    *root = NULL;
                                     
}



