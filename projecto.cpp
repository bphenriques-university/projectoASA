#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>

std::stack<int> nodeStack;

typedef struct node {
	int index;
	int lowIndex;
	int value;
} Node;

void tarjanAlgorithm() {
	nodeStack.push(5);
	std::cout << "" << nodeStack.top() << std::endl;
}


int main()
{
    int N; // number of persons
    int P; // number of shares
    
    std::vector<std::vector<Node> > shares;
    
    std::cout << "[Number of Persons] [Number of shares]" << std::endl;
    //read N and read P;
    std::cin >> N >> P;
    
    //initialize the share vector equal to number of person
    shares = std::vector<std::vector<Node> > (N);

    std::cout << "For each share: [Person a] [Person b]" << std::endl;
    //for each share, read
    for(int i = 0 ; i < P ; i++){
		//person u shares what it receives with person v
		int u, v;
		std::cin >> u >> v;
		Node node;
		node.index = -1;
		node.lowIndex = -1;
		node.value = v;
		shares[u-1].push_back(node);
	}
	
	//for each share, print
	for(std::vector<std::vector<Node> >::size_type u = 0; u != shares.size(); u++) {
		for(std::vector<Node>::size_type v = 0; v != shares[u].size(); v++) {
			std::cout << "Person " << u+1 << " shares what it receives with person " << shares[u][v].value << std::endl;
		}
	}
	
	/* rest of the code */
	tarjanAlgorithm();
    return 0;
} 
