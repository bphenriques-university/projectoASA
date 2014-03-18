/* Grupo 47 - Analise e Sintese de Algoritmos 2013/2014
 * Frederico Sabino 73239
 * Bruno Henriques 72913
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>

#define UNDEFINED -1

/* ---------- GLOBAL ID ---------- */
int global_index = 0;

/* ---------- CLASS NODE --------- */
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
		inline int getIndex() const { return _index; }
		inline int getLowIndex() const { return _lowIndex; }
		inline int getScc() const { return _scc_id; }
		inline void setLowIndex(int index) { _lowIndex = index ; }
		inline void setInStack(bool b) { _inStack = b;}
		inline void setScc(int scc) { _scc_id = scc;}
		inline bool isInStack() const { return _inStack;}	
};

/* ---------- GLOBAL VARIABLES --------- */

int numberOfSCC = 0;
int sccMaxSize = 0;
int numberOfIsolatedSCC = 0;

std::stack<int> nodeStack;
std::vector<Node*> nodes;
std::vector<std::vector<int> > adjacencias;

/* ---------- STRONG CONNECT ---------- */
/* Applies tarjan algorithm and paints each node with the associated SCC
 * input: a node id to start a DFS
 * output: none
*/

void strongConnect(int u) {
	Node* raiz = nodes[u];

	raiz->setup();
	nodeStack.push(u);
	raiz->setInStack(true);

	for(size_t v = 0; v < adjacencias[u].size(); v++) {
		int vizinho = adjacencias[u][v];
		Node* noVizinho = nodes[vizinho];

		if(noVizinho->getIndex() == UNDEFINED){
			strongConnect(vizinho);
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
		node->setScc(numberOfSCC);
		
		sccMaxSize = std::max(sccMaxSize, currentSCCSize);
	}
}

/* ---------- COUNTISOLATEDSCC ---------- */
/* For each SCC, count which ones have got a node that has a link to another SCC
 * input: void
 * output: number of SCC that don't have any link from within to another SCC
*/

int countIsolatedSCC() {
	std::vector<bool> scc_checked (numberOfSCC, false);
	int count_isolated = numberOfSCC;
	
	for(size_t u = 1; u < adjacencias.size(); u++) {
		int orig_scc = nodes[u]->getScc();
		
		if(scc_checked[orig_scc] == true){
			continue;
		}
		
		for(size_t v = 0; v < adjacencias[u].size() ; v++) {
			int adjacente = adjacencias[u][v];
			int dest_scc = nodes[adjacente]->getScc();
			
			#ifdef DEBUG
			std::cout << "orig: " << u << " dest: " << adjacente << std::endl;
			#endif
			
			if(orig_scc != dest_scc){
				#ifdef DEBUG
				std::cout << "Not isolated!" << std::endl;
				#endif
				
				scc_checked[orig_scc] = true;
				count_isolated--;
				break;
			}
		}
	}
	
	
	return count_isolated;	
}

/* ------------ MAIN FUNCTION -------------- */
int main() {
	int N, P; 
	std::vector<bool> scc_checked (numberOfSCC, false);
  
	int scanRes = scanf("%d %d", &N, &P);
	if(scanRes != 2 && scanRes != EOF) {
		printf("%s\n", "Error reading from standard input.");
	}

	//initialization
	for(int i = 0; i < N+1 ; i++) {
		nodes.push_back(new Node());
	}
	
	adjacencias = std::vector<std::vector<int> > (N+1);
   
	for(int i = 0 ; i < P ; i++) {
		int u, v;
		scanRes = scanf("%d %d", &u, &v);
		if(scanRes != 2 && scanRes != EOF) {
			printf("%s\n", "Error reading from standard input.");
		}
		
		adjacencias[u].push_back(v);
	}
	
	//for every node, apply Tarjan algorithm
	for(size_t u = 1; u != nodes.size(); u++) {
		if (nodes[u]->getIndex() == UNDEFINED){
			strongConnect(u);
		}
	}
	
	//for every SCC, count the number of isolated ones
	numberOfIsolatedSCC = countIsolatedSCC();
	
	#ifdef DEBUG
	std::cout << "--- Scc associado ---" << std::endl; 
	for(size_t u = 1; u != nodes.size(); u++) {
		std::cout << u << ": " << nodes[u]->getScc() << std::endl;
	}
	#endif
	
	printf("%d\n", numberOfSCC);
	printf("%d\n", sccMaxSize);
	printf("%d\n", numberOfIsolatedSCC);
  
  return 0;
}