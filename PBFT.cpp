#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

#define pre_prepared 0
#define prepared 1
#define committed 2
#define final_committed 3

void pre_prepare_state(int index);
void prepare_state(int index);
void committed_state(int index);
// pseudo:

// classes 
// print matrix
// rand function to randomly select starting node, before pre-prepared

//2/3 function check, takes state of node. if 2f + 1 


// 7 nodes in system, max 2 faulty nodes
// variable f, 3f + 1 amount of nodes in system, f = faulty nodes
// minimum nodes in the system, 2f + 1, more than 2/3 of total nodes have to be non-faulty

// connection matrix = matrix of all connections, 
// nodelist = array of structs for each node


const int f = 33;
const int node_size = 3*f + 1;
bool matrix_made = false;
// matrix empty for now until general code is running 
int connection_matrix[node_size][node_size];
int preposer_index = 0;
std::vector<int> valid_nodes; // this is a vector of indexes of nodes that we will fill with all valid nodes that are going to be used
                              // this will help iterating through them in the other methods after pre_prepare_state
class node {
  private:
    int state = pre_prepared;
    bool fault = false;
  public:
    void set_state(int new_state) {
      state = new_state;
    }
    int get_state() {
      return state;
    }
    void set_fault(int new_fault) {
      fault = new_fault;
    }
    bool get_fault() {
      return fault;
    }
};

node nodelist[node_size];
 
void matrix_generator() {
  for (int i = 0; i < node_size; i++) {
    for (int j = 0; j < node_size; j++) {
      if (i == j)
        connection_matrix[i][j] = 0;
      else if (i < j) {
        connection_matrix[i][j] = rand()%2;
        connection_matrix[j][i] = connection_matrix[i][j];
      }

      std::cout << connection_matrix[i][j] << ", ";   
    }
    std::cout << std::endl;
  }
}

bool validate_state(int STATE) {
  int validated = 0;
  //for loop iterates through each node in the array, nodeList
  for(int i = 0; i < node_size; i++) {
    if(STATE == nodelist[i].get_state()) {
      std::cout << "loop " << i << std::endl;
      std::cout << STATE << " Equals: " << nodelist[i].get_state() << std::endl;
      validated++;
    }
    if(validated == 2 * f + 1) {
      std::cout << "\n";
      return true;
    }
  }
  std::cout << "\n";
  return false;
}



void pre_prepare_state(int index) { 
  valid_nodes.push_back(index); // add to valid nodes vector so we don't have to preform search again
  std::vector<int> connected_nodes;
  nodelist[index].set_state(prepared);  

  if (validate_state(prepared)) {             // check if 2f+1 nodes are in prepared state
      std::cout << "prepared validated!"<< std::endl; 
      prepare_state(index);                   // then go to next stage
  }

  for(int i = 0; i < node_size; i++) {      // check for immediate connections
    std::cout << connection_matrix[i][index] << ", ";
    if(connection_matrix[i][index] == 1) {
      connected_nodes.push_back(i); // add to vector of nodes that are connected for fallback node search

      if(nodelist[i].get_state() != prepared && nodelist[i].get_fault() == false) {
        connected_nodes.clear();
        std::cout << "\n";
        pre_prepare_state(i);   // go to next connected node not in current state recursively 
      }
    }
  }
  std::cout << "\n##################\n";
  for (int i = 0; i < node_size; i++) {
    if(nodelist[i].get_state() != prepared && nodelist[i].get_fault() == false)
      pre_prepare_state(i);
  }

  /*
  // no nodes that were connected were in the correct state or unfaulty
  for(int j = 0; j < connected_nodes.size(); j++) { // preform same check but for connected
    for(int i = 0; i < node_size; i++) {
      if(connection_matrix[i][j] == 1) {
        if(nodelist[i].get_state() != prepared && nodelist[i].get_fault() == false)
          pre_prepare_state(i);              // go to next connected node not in current state recursively

      }
    }
  }
  */
}

void prepare_state(int index) { // enter committed state
  nodelist[index].set_state(committed);
  if (validate_state(committed)) {
    std::cout << "commit validated!"<< std::endl; 
    committed_state(index);
  }
    

  // go to next node in varified vector recursively
   for(int i = 0; i < node_size; i++) {
      if(nodelist[valid_nodes[i]].get_state() != committed) {
        prepare_state(valid_nodes[i]);
      }
   }
}

void committed_state(int index) { // insert into block chain then change state to final committed
  nodelist[index].set_state(final_committed);
  if (validate_state(final_committed)) {
    std::cout << "Final validated!"<< std::endl; 
    //insert into blockchain
    //NOTE: this might not be where we add to the block chain
    exit(0);
    return; // end loop; round succesfully finished
  }
  

  // go to next node in varified vector recursively
  for(int i = 0; i < node_size; i++) {
      if(nodelist[valid_nodes[i]].get_state() != final_committed) {
        committed_state(valid_nodes[i]);
      }
   }
   
}



void start_round() {
  valid_nodes.clear();
  preposer_index = (rand() % node_size);
  std::cout << preposer_index << " :PreposerIndex\n";
  pre_prepare_state(preposer_index);
}
int main() {
  srand((unsigned) time(NULL));
  nodelist[3].set_fault(true);
  nodelist[1].set_fault(true);
  nodelist[5].set_fault(true);
  matrix_generator();
  start_round();
  return 0;
}

