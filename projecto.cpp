#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>


typedef struct node {
	int index;
	int lowIndex;
	int value;
} Node;

std::stack<int> nodeStack;
std::vector<std::vector<Node> > nodes;
std::vector<std::vector<int> > adjacencias;
int index = 0;

void tarjanAlgorithm() {
	for(int i = 0; i < adjacencias.size(); i++) {
		strongConnect(i);
	}

}


int main()
{
    int N; // number of persons
    int P; // number of adjacencias
    
    std::cout << "[Number of Persons] [Number of adjacencias]" << std::endl;
    //read N and read P;
    std::cin >> N >> P;
    
    //initialize the share vector equal to number of person
    nodes = std::vector<std::vector<Node> > (N);

    std::cout << "For each share: [Person a] [Person b]" << std::endl;
    //for each share, read
    for(int i = 0 ; i < P ; i++){
		//person u adjacencias what it receives with person v
		int u, v;
		std::cin >> u >> v;
		Node node;
		node.index = -1;
		node.lowIndex = -1;
		node.value = v;

		nodes[u] = node;
		adjacencias[u-1].push_back(v);
	}
	
	//for each share, print
	for(std::vector<std::vector<Node> >::size_type u = 0; u != adjacencias.size(); u++) {
		for(std::vector<Node>::size_type v = 0; v != adjacencias[u].size(); v++) {
			std::cout << "Person " << u+1 << " adjacencias what it receives with person " << adjacencias[u][v] << std::endl;
		}
	}
	
	/* rest of the code */
	tarjanAlgorithm();
    return 0;
} 
