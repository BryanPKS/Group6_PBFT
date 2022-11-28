#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "block.h"
#include "blockChain.h"

#define pre_prepared 0
#define prepared 1
#define committed 2
#define final_committed 3

void pre_prepare_state(int index);
void prepare_state(int index);
void committed_state(int index);
void start_round(blockChain bc, block b);
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


const int f = 33;                   // This is the amount of faulty nodes allowed in the system; If you would like to change the amount of nodes, change this value and the nodes size will change to 3*f+1
const int node_size = 3*f + 1;      // Amount of nodes in the system.
blockChain* BLOCKCHAIN;
block* BLOCK;
// matrix empty for now until general code is running 
int connection_matrix[node_size][node_size];
int preposer_index = 0;
std::string fault_amount;
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

void printStats()
{
  BLOCKCHAIN->printStats();
}
 
void matrix_generator() {                 // This function generates the values of the adjacency matrix at runtime.
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

bool validate_state(int STATE) { // This funtion allows us to check the state of every node until we have found atleast 2*f+1 nodes in the system that are of the desired state. If we don't then return false
  int validated = 0;
  for(int i = 0; i < node_size; i++) {
    if(STATE == nodelist[i].get_state()) {
      validated++;
    }
    if(validated == 2 * f + 1) {
      return true;
    }
  }
  return false;
}



void pre_prepare_state(int index) { 
  valid_nodes.push_back(index); // add to valid nodes vector so we don't have to preform search again
  nodelist[index].set_state(prepared);  

  if (validate_state(prepared)) {             // check if 2f+1 nodes are in prepared state
      std::cout << "prepared validated!"<< std::endl; 
      prepare_state(index);                   // then go to next stage
  }

  for(int i = 0; i < node_size; i++) {      // check for immediate connections
    if(connection_matrix[i][index] == 1) {

      if(nodelist[i].get_state() != prepared && nodelist[i].get_fault() == false) {
        pre_prepare_state(i);   // go to next connected node not in current state recursively 
      }
    }
  }
  for (int i = 0; i < node_size; i++) {     // if there are no immediate connections that have valid nodes then iteratively find the next valid node
    if(nodelist[i].get_state() != prepared && nodelist[i].get_fault() == false)
      pre_prepare_state(i);
  }
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
    std::string decision;
    std::cout << "Final validated!"<< std::endl; 
    //insert into blockchain
    BLOCKCHAIN->addBlock(BLOCKCHAIN->getLatestBlock().getHash(), BLOCK->getData()); // add a new block
    printStats();                                                                   // print the new block
    std::cout << "Go for another round? (y/n): ";
    getline(std::cin, decision);
    if(decision == "y" || decision == "Y")
    {
      for(int i = 0; i < node_size; i++) {  // set all the nodes to fault for next runs
        nodelist[i].set_fault(false);
      }

      std::string blockInfo;
      std::cout << "Enter string data for block: ";
      getline(std::cin, blockInfo);
      block bb(BLOCKCHAIN->getLatestBlock().getHash(), blockInfo); // prepare next string to add to blockchain

      std::cout << "Enter amount of faults you'd like to add to the system" << std::endl;
      std::cout << "The amount of faults can be 1 to " << f << ": ";
      getline(std::cin , fault_amount);
      for(int i = 0; i < stoi(fault_amount); i++) {         // after input it takes the amount of faults that are to be added and adds them to the nodes list
        int rand_index = (rand() % node_size);
        if(nodelist[rand_index].get_fault() == false) {
          nodelist[rand_index].set_fault(true);
        }
        else {
          while (nodelist[rand_index].get_fault()) {
            rand_index = (rand() % node_size);
          }
          nodelist[rand_index].set_fault(true);
        }
      }
      start_round(*BLOCKCHAIN, bb);
    }
    exit(0); // end program; all rounds are succesfully finished
    return; 
  }
  

  // go to next node in varified vector recursively
  for(int i = 0; i < node_size; i++) {
      if(nodelist[valid_nodes[i]].get_state() != final_committed) {
        committed_state(valid_nodes[i]);
      }
   }
   
}

void start_round(blockChain bc, block b) {
  BLOCKCHAIN = &bc;
  BLOCK = &b;
  valid_nodes.clear();
  preposer_index = (rand() % node_size); // chooses a random node in the nodes list to be the preposer
  std::cout << preposer_index << " :PreposerIndex\n";
  pre_prepare_state(preposer_index);
}

int main() {
  blockChain bc1;
  block b1(bc1.getLatestBlock().getHash(), "info stuff"); // setup the first block for the first round
  srand((unsigned) time(NULL));
  
  matrix_generator(); // generate matrix for system
  start_round(bc1, b1); // start first round
  return 0;
}

