/***********************************************************
2021 Spring - BLG 336E-Analysis of Algorithms II
Final Project
Question on Greedy Algorithms
Modified Dijkstra Algorithms for Maximum Capacity Path
Submitted: 15.06.2021 
**********************************************************/

/***********************************************************
STUDENT INFORMATION
Full Name : Göksu GÜZ
Student ID: 150180715
**********************************************************/

// Some of the libraries you may need have already been included.
// If you need additional libraries, feel free to add them
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

// Do not change this definition
#define INT_MAX 1000

using namespace std;

class Graph{
public:
	int node_count;
	int edge_count;
	int** adjacency_matrix;

	Graph(){};
	void read_file(char* filename);
	void print_adjacency_matrix(); // in case you need
	int weight(int i, int j){return this->adjacency_matrix[i][j];}
	~Graph();
};

Graph::~Graph(){
	for(int i = 0; i < node_count; i++){
		delete [] adjacency_matrix[i];
	}
}

void Graph::print_adjacency_matrix(){	
	// Prints the adjacency matrix
	for(int i = 0; i < this->node_count; i++){
		for(int j = 0; j < this->node_count; j++){
			cout<<this->adjacency_matrix[i][j]<<", ";
		}
		cout<<endl;
	}
}

void Graph::read_file(char* filename){
	
	/*********************************************/
	/****** CODE HERE TO READ THE TEXT FILE ******/
    string line;
	string first, second, third;
	ifstream myFile(filename);
    //Read the file
	if (!myFile.is_open()) {
		cerr << "FILE COULD NOT BE FOUND" << endl; 
		exit(1);
	}
	int i = 0;
	getline( myFile, line, '\n' );
	this->node_count = stoi(line);

	this->adjacency_matrix = new int*[this->node_count];
    for(int i = 0; i < this->node_count; i++){
        this->adjacency_matrix[i] = new int[this->node_count];
    }
	for (; !myFile.eof() ; i++) { 
		getline( myFile, first, '\t' );
		if(myFile.eof())
			break;
		getline( myFile, second, '\t' );
		getline( myFile, third, '\n' );
		// undirected graph
		this->adjacency_matrix[stoi(first)][stoi(second)] = stoi(third);
		this->adjacency_matrix[stoi(second)][stoi(first)] = stoi(third);
    }
	this->edge_count = i;
    myFile.close();

	/*********************************************/
}


void Modified_Dijkstra(Graph* graph){

	/*********************************************/
	/****** CODE HERE TO FOR THE ALGORITHM *******/

	// vectors according to the pseudo code
	vector<int> status;
	vector<int> wt;
	vector<int> dad;

	int startNode = 0;

	// first assigned values to these vectors
	for(int i = 0; i < graph->node_count ; i++){
		status.push_back(0);
		wt.push_back(-1);
		dad.push_back(-1);
	}

	status[startNode] = 2;
	wt[startNode] = INT_MAX;


	for(int j = 1; j < graph->node_count ; j++){
		if(graph->adjacency_matrix[startNode][j] != 0){
			status[j] = 1;
			wt[j] = graph->weight(startNode,j);
			dad[j] = startNode;
		}
	}

	while(true){
		int max_f = 0;
		int v_fringe;
		bool check = false;
		for(int i = 0; i < graph->node_count ; i++){
			if(status[i] == 1){
				check = true;
				if(wt[i] > max_f){
					max_f = wt[i];
					v_fringe = i;
				}
			}
		}
		if(check == false)
			break;
		status[v_fringe] = 2;
		for(int j = 0; j < graph->node_count; j++){
			if(graph->adjacency_matrix[v_fringe][j] != 0){
				if(status[j] == 0){
					status[j] = 1;
					wt[j] = min(wt[v_fringe], graph->weight(v_fringe,j));
					dad[j] = v_fringe;
				}
				else if(status[j] == 1 && wt[j] < min(wt[v_fringe], graph->weight(v_fringe, j))){
					wt[j] = min(wt[v_fringe], graph->weight(v_fringe,j));
					dad[j] = v_fringe;
				}
			}
		}
	}
	/*********************************************/
	
	
	/*********************************************/
	/***** DO NOT CHANGE THE FOLLOWING LINES *****/
	/**** THEY PRINT OUT THE EXPECTED RESULTS ****/
	/*********************************************/
	
	// The following line prints wt array (or vector).
	// Do not change anything in the following lines.
	cout<<"###########RESULTS###########"<<endl;
	cout<<endl;
	
	cout<<"1. WT ARRAY"<<endl;
	cout<<"------------------------"<<endl;
	cout<<"  ";
	for(int i = 0; i < graph->node_count - 1; i++){
		cout << wt[i] << ", ";
	}
	cout << wt[graph->node_count - 1] << endl;
	
	// The following lines print the final path.
	// Do not change anything in the following lines.
	int iterator = graph->node_count - 1;
	vector<int> path_info;
	path_info.push_back(iterator);
	while(iterator != 0){
		path_info.push_back(dad[iterator]);
		iterator = dad[iterator];
	}
	cout<<endl;
	cout<<"2. MAXIMUM CAPACITY PATH"<<endl;
	cout<<"------------------------"<<endl;
	cout<<"  ";
	vector<int>::iterator it;
    for (it = path_info.end() - 1; it > path_info.begin(); it--)
        cout << *it << " -> ";
    cout<<*path_info.begin()<<endl;
    
    cout<<endl;
    cout<<"3. MAXIMUM CAPACITY"<<endl;
    cout<<"------------------------"<<endl;
    cout<<"  ";
    cout<<wt[graph->node_count - 1]<<endl;
    cout<<"#############################"<<endl;
    
    return;
}

int main(int argc, char **argv){
	Graph* graph = new Graph();
	graph->read_file(argv[1]);
	graph->print_adjacency_matrix();
	Modified_Dijkstra(graph);
	return 0;	
}
