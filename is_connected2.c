
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "queue.h"
//gcc -std=c99 -Wall -I../datastructures-v1.0.8.2/datastructures-v1.0.8.2/include -o is_connected2 is_connected.c graph3.c ../datastructures-v1.0.8.2/datastructures-v1.0.8.2/src/dlist/dlist.c ../datastructures-v1.0.8.2/datastructures-v1.0.8.2/src/queue/queue.c ../datastructures-v1.0.8.2/datastructures-v1.0.8.2/src/list/list.c
bool find_path(graph *g, node *src, node *dest) {
	queue *q = queue_empty(NULL);
	g = graph_node_set_seen(g, src, true);
	q = queue_enqueue(q, src);
	printf("Hej");
	while (!queue_is_empty(q)) {
		node *n = queue_front(q);
		q = queue_dequeue(q);
		dlist *neighbourSet = graph_neighbours(g, n);
		dlist_pos pos = dlist_first(neighbourSet);
		while (!dlist_is_end(neighbourSet, pos)) {
			node *entry = dlist_inspect(neighbourSet, pos);
			pos = dlist_next(neighbourSet, pos);
			if (!graph_node_is_seen(g, entry)) {
				g = graph_node_set_seen(g, entry, true);
				q = queue_enqueue(q, entry);
			}
		}
	}
	if (graph_node_is_seen(g, dest)) {
		return true;
	}
	else {
		return false;
	}
}

void user_interaction(const graph *g, char *srcstr, char *deststr)
{
	char instr[82];
	const char quitstr[5] = "quit\0";
	printf("Enter origin and destination (quit to exit): ");
	scanf("%[^\t\n]", instr);
	int i = sscanf(instr, "%40s %40s", srcstr, deststr);
	printf("%d", i);
	if (!strcmp(srcstr, quitstr)) {
		printf("quitting!");
	}
	else {
		printf("src = %s, dest = %s", srcstr, deststr);
	}
}

int main(int argc, char const *argv[]) {
	graph *g = graph_empty(8);
	g = graph_insert_node(g, "UME");
	g = graph_insert_node(g, "BMA");
	g = graph_insert_node(g, "MMX");
	g = graph_insert_node(g, "GOT");
	g = graph_insert_node(g, "PJA");
	g = graph_insert_node(g, "LLA");
	g = graph_insert_edge(g, graph_find_node(g, "UME"), graph_find_node(g, "BMA"));
	g = graph_insert_edge(g, graph_find_node(g, "BMA"), graph_find_node(g, "UME"));
	g = graph_insert_edge(g, graph_find_node(g, "BMA"), graph_find_node(g, "MMX"));
	g = graph_insert_edge(g, graph_find_node(g, "MMX"), graph_find_node(g, "BMA"));
	g = graph_insert_edge(g, graph_find_node(g, "BMA"), graph_find_node(g, "GOT"));
	g = graph_insert_edge(g, graph_find_node(g, "GOT"), graph_find_node(g, "BMA"));
	g = graph_insert_edge(g, graph_find_node(g, "LLA"), graph_find_node(g, "PJA"));
	g = graph_insert_edge(g, graph_find_node(g, "PJA"), graph_find_node(g, "LLA"));
	char srcstr[41];
	char deststr[41];
	user_interaction(g, srcstr, deststr);
	if (find_path(g, graph_find_node(g, srcstr), graph_find_node(g,deststr))) {
		printf("There is a path from %s to %s", srcstr, deststr);
	}
	else {
		printf("There is no path from %s to %s", srcstr, deststr);
	}
	return 0;
}
