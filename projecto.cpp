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
	bool _outside_current_scc;
		
	/* enquanto estou a fazer dfs marco todos os nós como fora do scc actual */
	/* se depois de fazer um novo scc ainda haver nós fora do scc actual entao o scc anterior tem arcos para fora */
	/* faço reset da flag e o ciclo recomeça */
	
	/* i.e. para cada nó visitado meto _outside_current_scc a true;
	 * quando faço pop na pilha meto a false
	 * se ainda houver nós a true temos um scc que nao esta isolado
	 */
	
	public:
		Node(){
			_index = UNDEFINED;
			_lowIndex = UNDEFINED;
			_scc_id = UNDEFINED;
			_inStack = false;
		}
		bool checkedIsolation = false;
		
		inline void setup() { _index = global_index; _lowIndex = _index; global_index++; }
		inline int getIndex() { return _index; }
		inline int getLowIndex() { return _lowIndex; }
		inline int getScc() { return _scc_id; }
		inline void setLowIndex(int index) { _lowIndex = index ; }
		inline void setInStack(bool b) { _inStack = b;}
		inline void setScc(int scc) { _scc_id = scc;}
		inline bool isInStack() { return _inStack;}
};

int last_rootNode_popped = 0;
bool poppedNodes = false;
bool phantomSCC = false; // a phantom scc is an scc that is processed but in which all of its nodes aren't in the stack

int numberOfSCC = 0;
int sccMaxSize = 0;
int numberOfIsolatedSCC = 0;

std::stack<int> nodeStack;
std::vector<Node*> nodes;
std::vector<std::vector<int> > adjacencias;


bool find(int u, int v){
	for (unsigned long i = 0; i < adjacencias[u].size(); i++){
		if(adjacencias[u][i] == v){
			return true;
		}
	}
	return false;
}


void strongConnect(int u, int father) {
	int fatherNode = father;
	Node* raiz = nodes[u];
	int lastConnectorNode = -1; //se o id ao fazer pop da pilha nunca chegar a este id entao o scc e' isolado

	raiz->setup();
	if(!nodeStack.empty()) {
		lastConnectorNode = nodeStack.top();
	}
	nodeStack.push(u);
	raiz->setInStack(true);
	

	for(unsigned long v = 0; v < adjacencias[u].size(); v++) {

		int vizinho = adjacencias[u][v];
		Node* noVizinho = nodes[vizinho];

		if(noVizinho->getIndex() == UNDEFINED) {
			strongConnect(vizinho, u);
			raiz->setLowIndex(std::min(raiz->getLowIndex(), noVizinho->getLowIndex()));
		}
		else if (noVizinho->isInStack()){
			raiz->setLowIndex(std::min(raiz->getLowIndex(), noVizinho->getIndex()));
		}
	}
  
  
	if(raiz->getLowIndex() == raiz->getIndex()) {
		numberOfSCC++;
		int currentSCCSize = 0;
		int poppedNodeIndex = 0;
		Node* node = NULL;
		
		#ifdef DEBUG
		std::cout << "--- popping ---" << std::endl;
		#endif

		do {
			poppedNodeIndex = nodeStack.top();
			#ifdef DEBUG
			std::cout << "popped: " << poppedNodeIndex << std::endl;
			#endif

			nodeStack.pop();
			
			nodes[poppedNodeIndex]->setInStack(false);
			node = nodes[poppedNodeIndex];
			currentSCCSize++;
			node->setScc(numberOfSCC);
		} while(raiz->getIndex() != node->getIndex());

		//aqui dizemos que o no' pai (se ainda estiver na stack) nao e' isolado
		if((nodeStack.size() >= 1 && nodes[fatherNode]->checkedIsolation == false) || (phantomSCC && nodeStack.empty())) {
			std::cout << "SCC with node " << fatherNode <<" is not isolated!" << std::endl;
			nodes[fatherNode]->checkedIsolation = true;
			numberOfIsolatedSCC--;
		}

		if(nodeStack.empty()) {
			phantomSCC = true;
		}

		node->setScc(numberOfSCC);
		sccMaxSize = std::max(sccMaxSize, currentSCCSize);
	}
}



int main() {
	int N, P; // number of persons number of shares link
	int scanRes = 0;
  //read N and read P;
  scanRes = scanf("%d %d", &N, &P);
  if(scanRes <= 0 && scanRes != EOF) {
			std::cout << "Error reading from standard input." << std::endl;
		}

  //initialize the shared vector equal to number of person
	for(int i = 0; i < N+1 ; i++) {
		nodes.push_back(new Node());
	}
	
  adjacencias = std::vector<std::vector<int> > (N+1);
	
   
  //for each share, read
  for(int i = 0 ; i < P ; i++) {
  	int u, v;
		scanRes = scanf("%d %d", &u, &v);
		if(scanRes <= 0 && scanRes != EOF) {
			std::cout << "Error reading from standard input." << std::endl;
		}

		adjacencias[u].push_back(v);
	}
	
		
	for(unsigned long u = 1; u != nodes.size(); u++) {
		if (nodes[u]->getIndex() == UNDEFINED){
			strongConnect(u, -1);
			phantomSCC = false;
		}
	}
	
	#ifdef DEBUG
	std::cout << "--- Scc associado ---" << std::endl; 
	for(unsigned long u = 1; u != nodes.size(); u++) {
		std::cout << u << ": " << nodes[u]->getScc() << std::endl;
	}
	#endif
	
  printf("%d\n", numberOfSCC);
  printf("%d\n", sccMaxSize);
  printf("%d\n", numberOfSCC + numberOfIsolatedSCC);
  return 0;
} 
