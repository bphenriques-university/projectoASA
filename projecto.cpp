#include <iostream>
#include <stdio.h>
#include <vector>


int main()
{
    int N; // number of persons
    int P; // number of shares
    
    std::vector<std::vector<int> > shares;
    
    std::cout << "[Number of Persons] [Number of shares]" << std::endl;
    //read N and read P;
    std::cin >> N >> P;
    
    //initialize the share vector equal to number of person
    shares = std::vector<std::vector<int> > (N);
    
    std::cout << "For each share: [Person a] [Person b]" << std::endl;
    //for each share, read
    for(int i = 0 ; i < P ; i++){
		//person u shares what it receives with person v
		int u, v;
		std::cin >> u >> v;
		shares[u-1].push_back(v);
	}
	
	//for each share, print
	for(std::vector<std::vector<int> >::size_type u = 0; u != shares.size(); u++) {
		for(std::vector<int>::size_type v = 0; v != shares[u].size(); v++) {
			std::cout << "Person " << u+1 << " shares what it receives with person " << shares[u][v] << std::endl;
		}
	}
	
	/* rest of the code */
	
    return 0;
} 
