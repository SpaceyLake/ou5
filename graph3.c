
#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

/*
* Implementation of a graph.
*
* Authors: Niklas Hörnblad (c19nhd@cs.umu.se)
*
* Version information:
*   2018-02-06: v1.0, first public version.
*/

// ===========INTERNAL DATA TYPES============

struct node {
	char name[41];
	bool seen;
	dlist *neighbours;
};

struct graph {
	dlist *nodes;
	int edgecount;
	int nodecount;
	int maxnodes;
};

// ===========INTERNAL FUNCTION IMPLEMENTATIONS============

/**
* nodes_are_equal() - Check whether two nodes are equal.
* @n1: Pointer to node 1.
* @n2: Pointer to node 2.
*
* Returns: true if the nodes are considered equal, otherwise false.
*
*/
bool nodes_are_equal(const node *n1,const node *n2)
{
	int i = 0;
	while (n1->name[i] != '\0' && n2->name[i] != '\0') {
		if (n1->name[i] != n2->name[i]) {
			return false;
		}
		i++;
	}
	if (n1->name[i] == '\0' && n2->name[i] == '\0') {
		return true;
	}
	else {
		return false;
	}
}

/**
* graph_empty() - Create an empty graph.
* @max_nodes: The maximum number of nodes the graph can hold.
*
* Returns: A pointer to the new graph.
*/
graph *graph_empty(int max_nodes)
{
	graph *g = malloc(sizeof(graph));
	g->nodes = dlist_empty(NULL);
	g->maxnodes = max_nodes;
	g->nodecount = 0;
	return g;
}

/**
* graph_is_empty() - Check if a graph is empty, i.e. has no nodes.
* @g: Graph to check.
*
* Returns: True if graph is empty, otherwise false.
*/
bool graph_is_empty(const graph *g)
{
	return dlist_is_empty(g->nodes);
}

/**
* graph_has_edges() - Check if a graph has any edges.
* @g: Graph to check.
*
* Returns: True if graph has any edges, otherwise false.
*/
bool graph_has_edges(const graph *g)
{
	return g->edgecount > 0;
}

/**
* graph_insert_node() - Inserts a node with the given name into the graph.
* @g: Graph to manipulate.
* @s: Node name.
*
* Creates a new node with a copy of the given name and puts it into
* the graph.
*
* Returns: The modified graph.
*/
graph *graph_insert_node(graph *g, const char *s)
{
	if (g->nodecount < g->maxnodes) {
		node *n = malloc(sizeof(node));
		n->seen = false;
		n->neighbours = dlist_empty(NULL);
		int i = 0;
		while (s[i] != '\0') {
			n->name[i] = s[i];
			printf("%c", s[i]);
			i++;
		}
		n->name[i] = '\0';
		printf(" ");
		// Iterate over the list. Return first match.
		dlist_pos pos = dlist_first(g->nodes);

		while (!dlist_is_end(g->nodes, pos)) {
			// Inspect the table entry
			node *entry = dlist_inspect(g->nodes, pos);
			// Check if the entry key matches the search key.
			if (nodes_are_equal(n,entry)) {
				printf("Warning: A node with that name already exists in the graph!");
				free(n);
				return g;
			}
			// Continue with the next position.
			pos = dlist_next(g->nodes, pos);
		}
		dlist_insert(g->nodes, n, dlist_first(g->nodes));
		g->nodecount++;
		printf("\ninit %d", n->seen);
		return g;
	}
	else
	{
		printf("Warning: Graph full!");
		return g;
	}
}

/**
* graph_find_node() - Find a node stored in the graph.
* @g: Graph to manipulate.
* @s: Node identifier, e.g. a char *.
*
* Returns: A pointer to the found node, or NULL.
*/
node *graph_find_node(const graph *g, const char *s)
{
	// Iterate over the list. Return first match.

	dlist_pos pos = dlist_first(g->nodes);

	while (!dlist_is_end(g->nodes, pos)) {
		bool check = true;
		// Inspect the table entry
		node *n = dlist_inspect(g->nodes, pos);
		printf("\nname %s", n->name);
		printf(" search %s", s);
		// Check if the entry key matches the search key.
		int i = 0;
		while (n->name[i] != '\0' && s[i] != '\0' && check == true) {
			if (n->name[i] != s[i]) {
				check = false;
			}
			i++;
		}
		if (n->name[i] == '\0' && s[i] == '\0' && check == true) {
			return n;
		}
		// Continue with the next position.
		pos = dlist_next(g->nodes, pos);
	}
	printf("\nWarning: Node does not exist!");
	exit(EXIT_FAILURE);
}

/**
* graph_node_is_seen() - Return the seen status for a node.
* @g: Graph storing the node.
* @n: Node in the graph to return seen status for.
*
* Returns: The seen status for the node.
*/
bool graph_node_is_seen(const graph *g, const node *n)
{
	return n->seen;
}

/**
* graph_node_set_seen() - Set the seen status for a node.
* @g: Graph storing the node.
* @n: Node in the graph to set seen status for.
* @s: Status to set.
*
* Returns: The modified graph.
*/
graph *graph_node_set_seen(graph *g, node *n, bool seen)
{
	n->seen = seen;
	return g;
}

/**
* graph_reset_seen() - Reset the seen status on all nodes in the graph.
* @g: Graph to modify.
*
* Returns: The modified graph.
*/
graph *graph_reset_seen(graph *g)
{
	// Iterate over the list. Return first match.

	dlist_pos pos = dlist_first(g->nodes);

	while (!dlist_is_end(g->nodes, pos)) {
		// Inspect the table entry
		node *entry = dlist_inspect(g->nodes, pos);

		entry->seen = false;

		// Continue with the next position.
		pos = dlist_next(g->nodes, pos);
	}
	return g;
}

/**
* graph_insert_edge() - Insert an edge into the graph.
* @g: Graph to manipulate.
* @n1: Source node (pointer) for the edge.
* @n2: Destination node (pointer) for the edge.
*
* NOTE: Undefined unless both nodes are already in the graph.
*
* Returns: The modified graph.
*/
graph *graph_insert_edge(graph *g, node *n1, node *n2)
{
	// Iterate over the list. Return first match.

	dlist_pos pos = dlist_first(n1->neighbours);

	while (!dlist_is_end(n1->neighbours, pos)) {
		// Inspect the table entry
		node *n = dlist_inspect(n1->neighbours, pos);

		if (nodes_are_equal(n,n2)) {
			printf("Warning: Edge already exist!");
			return g;
		}

		// Continue with the next position.
		pos = dlist_next(n->neighbours, pos);
	}
	dlist_insert(n1->neighbours, n2, dlist_first(n1->neighbours));
	g->edgecount++;
	return g;
}

/**
* graph_delete_node() - Remove a node from the graph.
* @g: Graph to manipulate.
* @n: Node to remove from the graph.
*
* Returns: The modified graph.
*
* NOTE: Undefined if the node is not in the graph.
*/
graph *graph_delete_node(graph *g, node *n)
{
	// Iterate over the list. Return first match.

	dlist_pos pos = dlist_first(g->nodes);

	while (!dlist_is_end(g->nodes, pos)) {
		// Inspect the table entry
		node *ni = dlist_inspect(g->nodes, pos);
		graph_delete_edge(g, ni, n);
		// Continue with the next position.
		pos = dlist_next(g->nodes, pos);
	}

	// Iterate over the list. Return first match.

	pos = dlist_first(g->nodes);

	while (!dlist_is_end(g->nodes, pos)) {
		// Inspect the table entry
		node *ni = dlist_inspect(g->nodes, pos);

		if (nodes_are_equal(ni, n)) {
			dlist_remove(g->nodes, pos);
			free(n);
			g->nodecount--;
		}

		// Continue with the next position.
		pos = dlist_next(g->nodes, pos);
	}

	return g;
}

/**
* graph_delete_edge() - Remove an edge from the graph.
* @g: Graph to manipulate.
* @n1: Source node (pointer) for the edge.
* @n2: Destination node (pointer) for the edge.
*
* Returns: The modified graph.
*
* NOTE: Undefined if the edge is not in the graph.
*/
graph *graph_delete_edge(graph *g, node *n1, node *n2)
{
	// Iterate over the list. Return first match.

	dlist_pos pos = dlist_first(n1->neighbours);

	while (!dlist_is_end(n1->neighbours, pos)) {
		// Inspect the table entry
		node *n = dlist_inspect(n1->neighbours, pos);

		if (nodes_are_equal(n,n2)) {
			dlist_remove(n1->neighbours, pos);
			g->edgecount--;
		}

		// Continue with the next position.
		pos = dlist_next(n1->neighbours, pos);
	}
	return g;
}

/**
* graph_choose_node() - Return an arbitrary node from the graph.
* @g: Graph to inspect.
*
* Returns: A pointer to an arbitrayry node.
*
* NOTE: The return value is undefined for an empty graph.
*/
node *graph_choose_node(const graph *g)
{
	node *n = dlist_inspect(g->nodes, dlist_first(g->nodes));
	return n;
}

/**
* graph_neighbours() - Return a list of neighbour nodes.
* @g: Graph to inspect.
* @n: Node to get neighbours for.
*
* Returns: A pointer to a list of nodes. Note: The list must be
* dlist_kill()-ed after use.
*/
dlist *graph_neighbours(const graph *g,const node *n)
{
	return n->neighbours;
}

/**
* graph_kill() - Destroy a given graph.
* @g: Graph to destroy.
*
* Return all dynamic memory used by the graph.
*
* Returns: Nothing.
*/
void graph_kill(graph *g)
{
	// Iterate over the list. Destroy all elements.
	dlist_pos pos = dlist_first(g->nodes);

	while (!dlist_is_end(g->nodes, pos)) {
		// Inspect the key/value pair.
		node *n = dlist_inspect(g->nodes, pos);
		// Move on to next element.
		pos = dlist_next(g->nodes, pos);
		// Deallocate the table entry structure.
		dlist_kill(n->neighbours);
		free(n);
	}

	// Kill what's left of the list...
	dlist_kill(g->nodes);
	// ...and the table.
	free(g);
}

/**
* graph_print() - Iterate over the graph elements and print their values.
* @g: Graph to inspect.
*
* Iterates over the graph and prints its contents.
*
* Returns: Nothing.
*/
void graph_print(const graph *g)
{

}
