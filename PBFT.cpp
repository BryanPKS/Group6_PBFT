#include <iostream>
#include <vector>
#define pre_prepared 0
#define prepared 1
#define committed 2
#define final_committed 3

int main() {
  std::cout << "Hello World!\n";
}

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


const int f = 2;
const int node_size = 3*f + 1;
// matrix empty for now until general code is running
int connection_matrix[node_size][node_size] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
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

bool validate_state(int STATE) {
  int validated = 0;
  //for loop iterates through each node in the array, nodeList
  for(int i = 0; i < sizeof(nodelist); i++) {
    if(STATE = nodelist->get_state()) {
        validated++;
    }
    if(validated >= 2 * sizeof(nodelist) + 1) {
      return true;
    }
  }
  return false;
}



void pre_prepare_state(int index) { 
  int one = 1;
  int *oneptr = &one; //ignore this for some reason the if statement on line 89 only works with pointers...

  valid_nodes.push_back(index); // add to valid nodes vector so we don't have to preform search again

  nodelist[index].set_state(prepared);
  std::vector<int> connected_nodes;
  if (validate_state(prepared))              // check if 2f+1 nodes are in prepared state
    prepare_state(index);      // then go to next stage
  

  for(int i = 0; i < sizeof(nodelist); i++) {      // check for immediate connections
    if(connection_matrix[i,index] == oneptr) {
      connected_nodes.push_back(i); // add to vector of nodes that are connected for fallback node search
      if(nodelist->get_state() != prepared && nodelist->get_fault() == false)
        pre_prepare_state(index);              // go to next connected node not in current state recursively
    }
  }

  // no nodes that were connected were in the correct state or unfaulty
  for(int j = 0; j < connected_nodes.size(); j++) { // preform same check but for connected
    for(int i = 0; i < sizeof(nodelist); i++) {
      if(connection_matrix[i,j] == oneptr) {
        if(nodelist->get_state() != prepared && nodelist->get_fault() == false)
          pre_prepare_state(i);              // go to next connected node not in current state recursively
      }
    }
  }
}

void prepare_state(int index) { // enter committed state
  nodelist[index].set_state(committed);
  if (validate_state(committed))
    committed_state(index);

  // go to next node in varified vector recursively
   for(int i = 0; i < sizeof(nodelist); i++) {
      if(nodelist[valid_nodes[i]].get_state() != committed) {
        prepare_state(valid_nodes[i]);
      }
   }
}

void committed_state(int index) { // insert into block chain then change state to final committed
  

  if (validate_state(final_committed)) {
    //insert into blockchain
    //NOTE: this might not be where we add to the block chain
    return; // end loop; round succesfully finished
  }
  nodelist[index].set_state(final_committed);

  // go to next node in varified vector recursively
  for(int i = 0; i < sizeof(nodelist); i++) {
      if(nodelist[valid_nodes[i]].get_state() != final_committed) {
        committed_state(valid_nodes[i]);
      }
   }
}

void start_round() {
  for(int i = 0; i < node_size; i++) {
    nodelist[i].set_state(pre_prepared);
  }
  //Randomly generate a node index to be the preposer
  pre_prepare_state(preposer_index);
}
int main() {
  start_round();
  return 0;
}

