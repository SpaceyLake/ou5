
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
	char *name;
	bool *seen;
};

struct graph {
	dlist *nodes;
	dlist *edges;
};

struct edge {
	node *n1;
	node *n2;
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
	return n1->name == n2->name;
}

/**
* graph_empty() - Create an empty graph.
* @max_nodes: The maximum number of nodes the graph can hold.
*
* Returns: A pointer to the new graph.
*/
graph *graph_empty(int max_nodes)
{
	graph *g = calloc(max_nodes, sizeof(node));
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
	return dlist_is_empty(g->edges);
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
	// Iterate over the list. Return first match.

	dlist_pos pos = dlist_first(g->nodes);

	while (!dlist_is_end(g->nodes, pos)) {
		// Inspect the table entry
		node *entry = dlist_inspect(g->nodes, pos);
		// Check if the entry key matches the search key.
		if (*(entry->name) == *s) {
			// If yes, return the corresponding value pointer.
			printf("Warning: A node with that name already exists in the graph!");
			return g;
		}
		// Continue with the next position.
		pos = dlist_next(g->nodes, pos);
	}

	node *n = malloc(sizeof(node));
	*(n->name) = *s;
	n->seen = false;
	dlist_insert(g->nodes, n, dlist_first(g->nodes));
	return g;
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
		// Inspect the table entry
		node *entry = dlist_inspect(g->nodes, pos);
		// Check if the entry key matches the search key.
		if (*(entry->name) == *s) {
			// If yes, return the corresponding value pointer.
			return entry;
		}
		// Continue with the next position.
		pos = dlist_next(g->nodes, pos);
	}
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
	*(n->seen) = seen;
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
	struct edge *e = malloc(sizeof(struct edge));
	e->n1 = n1;
	e->n2 = n2;
	dlist_insert(g->edges, e, dlist_first(g->edges));
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

	dlist_pos pos = dlist_first(g->edges);

	while (!dlist_is_end(g->edges, pos)) {
		// Inspect the table entry
		struct edge *e = dlist_inspect(g->edges, pos);

		if (*(e->n1->name)==*(n->name) || *(e->n2->name)==*(n->name)) {
			dlist_remove(g->edges, pos);
			free(e);
		}

		// Continue with the next position.
		pos = dlist_next(g->edges, pos);
	}

	// Iterate over the list. Return first match.

	pos = dlist_first(g->nodes);

	while (!dlist_is_end(g->nodes, pos)) {
		// Inspect the table entry
		node *entry = dlist_inspect(g->nodes, pos);

		if (*(entry->name)==*(n->name)) {
			dlist_remove(g->nodes, pos);
			free(n);
		}

		// Continue with the next position.
		pos = dlist_next(g->nodes, pos);
	}
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

	dlist_pos pos = dlist_first(g->edges);

	while (!dlist_is_end(g->edges, pos)) {
		// Inspect the table entry
		struct edge *e = dlist_inspect(g->edges, pos);

		if ((*(e->n1->name)==*(n1->name) && *(e->n2->name)==*(n2->name))
		|| (*(e->n2->name)==*(n1->name) && *(e->n1->name)==*(n2->name))) {
			dlist_remove(g->edges, pos);
			free(e);
		}

		// Continue with the next position.
		pos = dlist_next(g->edges, pos);
	}
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
	dlist *neighbours;
	// Iterate over the list. Return first match.

	dlist_pos pos = dlist_first(g->edges);

	while (!dlist_is_end(g->edges, pos)) {
		// Inspect the table entry
		struct edge *e = dlist_inspect(g->edges, pos);

		if (*(e->n1->name)==*(n->name) && *(e->n2->name)!=*(n->name)) {
			dlist_insert(neighbours, e->n2, dlist_first(neighbours));
		}
		else if (*(e->n2->name)==*(n->name) && *(e->n1->name)!=*(n->name)) {
			dlist_insert(neighbours, e->n1, dlist_first(neighbours));
		}

		// Continue with the next position.
		pos = dlist_next(g->edges, pos);
	}
	return neighbours;
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
	dlist_pos pos = dlist_first(g->edges);

	while (!dlist_is_end(g->edges, pos)) {
		// Inspect the key/value pair.
		struct edge *e = dlist_inspect(g->edges, pos);
		// Move on to next element.
		pos = dlist_next(g->edges, pos);
		// Deallocate the table entry structure.
		free(e);
	}

	// Iterate over the list. Destroy all elements.
	pos = dlist_first(g->nodes);

	while (!dlist_is_end(g->nodes, pos)) {
		// Inspect the key/value pair.
		node *n = dlist_inspect(g->nodes, pos);
		// Move on to next element.
		pos = dlist_next(g->nodes, pos);
		// Deallocate the table entry structure.
		free(n);
	}

	// Kill what's left of the list...
	dlist_kill(g->nodes);
	dlist_kill(g->edges);
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
