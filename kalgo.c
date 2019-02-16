#include<stdio.h>
#include<stdlib.h>

struct Edge{
	int src, dest, weight, selected;
};//this is to store the edges in the graph

struct Graph{
	int V, E;
	struct Edge *edge;
};//this is for graph

struct Graph *graph;//create an instance

void init(struct Graph **temp, int V, int E){//this basically acts like a constructor
		int cond = (V*(V-1)) / 2;
		if(E > cond || V == 1){
			printf("Invalid graph specs\n");
			exit(1);
		}
		(*temp) = (struct Graph*)malloc(sizeof(struct Graph));
		(*temp)->V = V;
		(*temp)->E = E;
		(*temp)->edge = (struct Edge*)malloc(E * (sizeof(struct Edge)));
}

void insert(int src, int dest, int weight){
		static int i;
		if(src < 0 || src > graph->V-1 || dest < 0 || dest > graph->V-1){
			/* 
				Basically we are checking if the src and dest entered by the user is out of bounds
			*/
			printf("Invalid src to dest\n");
			exit(1);
		}
		graph->edge[i].src = src;
		graph->edge[i].dest = dest;
		graph->edge[i].weight = weight;
		graph->edge[i].selected = 0;
		/*  
			assigning selected property of all edges to zero, as we havent
			 applied KRUSKAL'S ALGO yet.
		  */
		i++;
}

void createGraph(){//this is to add edges to the graph
		int j, s, d, w;
		for(j = 0 ; j < graph->E ; j++){
			printf("Enter src, dest, weight of %dth edge : ", j+1);
			scanf("%d %d %d", &s, &d, &w);
			insert(s, d, w);
		}
		printf("\n");
}

void printGraph(struct Graph *temp){
	int j;
	for(j = 0 ; j < temp->E ; j++)//prints the source, weight, destination of each edge 
		printf("%d----->%d----->%d\n", temp->edge[j].src, temp->edge[j].weight, temp->edge[j].dest);
	printf("\n");
}

void swap(int i1, int i2){//swapping the edges based on their edge weight
	struct Edge temp = graph->edge[i1];
	graph->edge[i1] = graph->edge[i2];
	graph->edge[i2] = temp;
}

void sort(){//sort the edges in ascending order which is essential for KRUSKAL'S ALGORITHM
	int j,k;//basic bubble sort
	for(j = 0 ; j < graph->E ; j++)
		for(k = 0 ; k < graph->E - j - 1 ; k++)
			if(graph->edge[k].weight > graph->edge[k+1].weight)
				swap(k , k + 1);
}

void findMST(){//the whole logic for the KRUSKAL'S ALGORITHM lies here
	struct Graph* temp;
	printf("After Applying Kruskals algo : \n\n");
	printf("Order of selection is : \n\n");
	sort();
	init(&temp, graph->V, graph->V - 1);
	int selected[graph->E];//this array is first inintialised to zeros
	//then it is assigned 1 when the corresponding edges has been visited
	int i;
	for(i = 0 ; i < graph->E ; i++)
		selected[i] = 0;	
	int count = 0, edges = 0, src, dest;
	while(edges < temp->E){
		for(i = 0 ; i < graph->E ; i++){
			src = graph->edge[i].src;
			dest = graph->edge[i].dest;
			if(selected[src] == 1 && selected[dest] == 1 && graph->edge[i].selected == 1)
			/* 
				here im checking if the source and the destination point of an edge has been selected
				If it has been selected then we can ignore that edge, because we have already considered it  
			*/
				continue;
			else{
				selected[src] = selected[dest] = graph->edge[i].selected = 1;
				temp->edge[count++] = graph->edge[i];
				/* 
					If the edge is not selected , then we need to consider that edge, and make its
					source and destination point as one, including the "selected" attribute
				 */
				break;
			}
		}
		edges++;
	}
	printGraph(temp);
}

int main(void){
	//first call init() then createGraph()
	//init() initialises the global graph object
	//createGraph() prompts for user input
	//findMST() applies KRUSKAL's ALGORITHM on the graph
	init(&graph, 4, 5);
	createGraph();
	printGraph(graph);
	findMST();//try to eliminate loop problem
	return 0;
}
