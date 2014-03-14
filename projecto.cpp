#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>

#define UNDEFINED -1

int global_index = 0;
int global_scc_id = 0;

class Node{
	int _index;
	int _lowIndex;
	int _scc_id;
	bool _inStack;
	
	public:
		Node(){
			_index = UNDEFINED;
			_lowIndex = UNDEFINED;
			_scc_id = UNDEFINED;
			_inStack = false;
		}
		
		inline void setup() { _index = global_index; _lowIndex = _index; global_index++; }
		inline int getIndex() { return _index; }
		inline int getLowIndex() { return _lowIndex; }
		inline int getScc() { return _scc_id; }
		inline void setLowIndex(int index) { _lowIndex = index ; }
		inline void setInStack(bool b) { _inStack = b;}
		inline void setScc(int scc) { _scc_id = scc;}
		inline bool isInStack() { return _inStack;}
};



int numberOfSCC = 0;
int sccMaxSize = 0;
int numberOfIsolatedSCC = 0;

std::stack<int> nodeStack;
std::vector<Node*> nodes; //posicao 0 nao usada
std::vector<std::vector<int> > adjacencias; //posicao 0 nao usada

std::vector<int> raizes_scc_ambiguos;



void strongconnect(int u) {
	Node* raiz = nodes[u];

	raiz->setup();
	nodeStack.push(u);
	raiz->setInStack(true);
	

	for(std::vector<int>::size_type v = 0; v < adjacencias[u].size(); v++) {

		int vizinho = adjacencias[u][v];
		Node* noVizinho = nodes[vizinho];

		if(noVizinho->getIndex() == UNDEFINED){
			strongconnect(vizinho);
			raiz->setLowIndex(std::min(raiz->getLowIndex(), noVizinho->getLowIndex()));
		}
		else if (noVizinho->isInStack()){
			raiz->setLowIndex(std::min(raiz->getLowIndex(), noVizinho->getIndex()));
		}
	}
  
	if(raiz->getLowIndex() == raiz->getIndex() ){
		numberOfSCC++;
		int currentSCCSize = 0;
		int poppedNodeIndex = 0;
		Node* node = NULL;
		std::cout << "--- popping ---" << std::endl;
		do {
			poppedNodeIndex = nodeStack.top();
			std::cout << poppedNodeIndex << std::endl;
			nodeStack.pop();
			nodes[poppedNodeIndex]->setInStack(false);
			node = nodes[poppedNodeIndex];
			currentSCCSize++;
			node->setScc(numberOfSCC);
		} while(raiz->getIndex() != node->getIndex());

		node->setScc(numberOfSCC);
		
		sccMaxSize = std::max(sccMaxSize, currentSCCSize);
	}
	
	//tracks sccs
	if(adjacencias[u].size() > 1){
		raizes_scc_ambiguos.push_back(u);
	}
}

int verifica_scc_isolado(int raiz){
	int id_scc = nodes[raiz]->getScc();
	std::cout << "--- no a analisar se vai fora : " << raiz << "---\n";
	
	for(std::vector<int>::size_type v = 0; v < adjacencias[raiz].size(); v++) {
		int vizinho = adjacencias[raiz][v];
		Node* noVizinho = nodes[vizinho];
		
		std::cout << "Vizinho: " << vizinho << std::endl;
		
		if(noVizinho->getScc() != id_scc){
				std::cout << "** Nao isolado**\n";
				return -1;
		}
	}
	
	return 0;
}


int main(){
    int N, P; // number of persons number of shares link
    
    //read N and read P;
    scanf("%d %d", &N, &P);

    //initialize the shared vector equal to number of person
    for(int i = 0; i < N+1 ; i++){
		nodes.push_back(new Node());
	}
	
    adjacencias = std::vector<std::vector<int> > (N+1);
	
   
    //for each share, read
    for(int i = 0 ; i < P ; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		
		std::cout << u << " " << v << std::endl;
		
		adjacencias[u].push_back(v);
	}
	
		
	for(std::vector<int>::size_type u = 1; u != nodes.size(); u++) {
		if (nodes[u]->getIndex() == UNDEFINED){
			strongconnect(u);
		}
	}
	
	std::cout << "--- Scc associado ---" << std::endl; 
	for(std::vector<int>::size_type u = 1; u != nodes.size(); u++) {
		std::cout << u << ": " << nodes[u]->getScc() << std::endl;
	}
	
	numberOfIsolatedSCC = numberOfSCC;
	
	for(std::vector<int>::size_type u = 0; u != raizes_scc_ambiguos.size(); u++) {
		if(verifica_scc_isolado(raizes_scc_ambiguos[u]) < 0){
			numberOfIsolatedSCC--;
		} 
	}
	
	
	
  printf("%d\n", numberOfSCC);
  printf("%d\n", sccMaxSize);
  printf("%d\n", numberOfIsolatedSCC);
  return 0;
} 
