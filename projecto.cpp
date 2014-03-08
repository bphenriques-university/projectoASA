#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>

static int index = 0;

class Node{
	int _index;
	int _lowIndex;
	int _value;
	
	public:
		Node(int value){
			_index = index++;
			_lowIndex = -1;
			_value = value;
		}
		
		int getIndex() { return _index; }
		int getLowIndex() { return _lowIndex; }
		int getValue() { return _value; }
		
};

std::stack<int> nodeStack;

std::vector<Node*> nodes;
std::vector<std::vector<int> > adjacencias;

void tarjanAlgorithm(int u) {
	//for(unsigned int i = 0; i < adjacencias.size(); i++) {
	//	strongConnect(i);
	//}

}


int main(){
    int N, P; // number of persons number of shares link
    
    std::cout << "[Number of Persons] [Number of adjacencias]" << std::endl;
    //read N and read P;
    scanf("%d %d", &N, &P);

    //initialize the share vector equal to number of person
    nodes = std::vector<Node*> (N+1);
    adjacencias = std::vector<std::vector<int> > (N+1);
	
	std::cout << "For each share: [Person a] [Person b]" << std::endl;
    
    //for each share, read
    for(int i = 0 ; i < P ; i++){
		//person u adjacencias what it receives with person v
		int u, v;
		scanf("%d %d", &u, &v);
		
		nodes[u] = new Node(v);
		adjacencias[u].push_back(v);
	}
	
	//for each share, print
	for(std::vector<std::vector<int> >::size_type u = 0; u != adjacencias.size(); u++) {
		for(std::vector<int>::size_type v = 0; v != adjacencias[u].size(); v++) {
			std::cout << "Person " << u << " adjacencias what it receives with person " << adjacencias[u][v] << std::endl;
		}
	}
	
	for(std::vector<int>::size_type u = 1; u != nodes.size(); u++) {
			if(nodes[u]->getIndex() == -1){
				continue;
			}
			tarjanAlgorithm(u);
	}
    return 0;
} 
