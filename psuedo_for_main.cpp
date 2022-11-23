#include <iostream>
#define pre_prepared 0
#define prepared 1
#define commited 2
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
// minimum nodes in the system, 2f + 1, more than 2/3 of total nodes

// connection matrix = matrix of all connections, 
// nodelist = array of structs for each node

//

// 4 stages, all states for nodes, structs for each stage
// For each stage,  
// Pre-Prepared, waits until 2f + 1 
// prepared, 
// committed, 
// final committed,

/*
bool validate_state(int STATE) {
  int validated = 0;
  for loop iterates through each node in the array, nodeList
  for(int i = 0; i<nodelist.size; i++) {
    if(STATE = nodelist.state) {
        validated++
    }
    if(validated >= 2 * nodelist.size + 1) {
      return TRUE
    }
  }
  return False
}

round() {
  set all nodes to the preprepared state
  Randomly generate a node index to be the preposer
  pre_prepare(nodelist[preposer_index])
}

void pre_prepare_state(int preposer_index) { 
  if (validate_state(prepared))              // check if 2f+1 nodes are in prepared state
    prepare_state(int preposer_index)        // then go to next stage

  nodelist[preposer_index].state = prepared  // set current node to prepared state

  for(i = 0; size of nodelist) {
    if(node is connected to current node)
      if(state != prepared)
        pre_prepare_state[i]                 // go to next connected node not in current state recursively
  }
}

void prepare_state(int preposer_index) { // enter committed state
  if (validate_state(committed))
    committed_state(int preposer_index)

  nodelist[preposer_index].state = committed

  for(i = 0; size of nodelist) {
    if(node is connected to current node)
      if(state == prepared)
        prepare_state(i)
  }
}

void committed_state(int preposer_index) { // insert into block chain then change state to final committed
  insert into blockchain

  if (validate_state(final_committed))
    return

  nodelist[preposer_index].state = final_committed

  for(i = 0; size of nodelist) {
    if(node is connected to current node)
      if(state == committed)
        committed_state(i)
  }
}



*/
