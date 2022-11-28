# Group6_PBFT

This code is the implementation of the PBFT algorithm to simulate a blockchain.

This GitHub link has all the code necessary to run the code:
https://github.com/BryanPKS/Group6_PBFT

# ::RUN INSTRUCTIONS::

With g++ compile the code with this command:
g++ block.cpp PBFT.cpp

Now you can run the code with this command:
./a.exe

It will now show the adjacency matrix for the nodes in the blockchain created at run time.
Also, will then show all the stages running and then the blocks currently in the blockchain 
with the last in the list being the most recently added,

If you would like to add more to the blockchain simply type "y" and then choose any string that you would like to add.
Then you can introduce faults into the system that have the ability to randomly change nodes in the system to have fault set to true

# :: FUNCTIONALITY :: 

Each run will have a base f value of 33.
There are 3 * f + 1 nodes in the system and f faults are allowed in the system.

To change the amount of nodes in the system simply change the value of f on line 35 of the PBFT.cpp file.
The new amount of nodes will be 3*f+1

This program has a series of nodes that are attached to the blockchain and when a new block is added we will add in what is referred to as a "round"

# :: STEPS OF A ROUND ::

At the start of a round, all of the nodes are set to the state of "pre_prepared" and the fault is set to false.
A random node is chosen to be the proposer node that proposes the addition to the blockchain.

In the pre-prepare step, we will start with the proposer node set it to the prepared state, and search for connected nodes in the adjacency matrix 
with the corresponding index and recursively perform the same operation on the node at that index.
Faulty nodes will be skipped and not be selected in subsequent rounds.
If there are no valid nodes connected to the current node then we will run an iterative search to find the next reliable candidate.
Each time a node is called in this function its index is added to a valid nodes vector. This will allow us to more easily select them for the remaining steps.
Once we have at least 2*f+1 nodes that are in the correct state will continue on to the next step in the round.

In the prepare step, we set 2*f+1 of the nodes to the committed state confirming their validity.

In the commit stage, we will set all nodes currently in the commit state to final_commit and then add the new block to the blockchain.
