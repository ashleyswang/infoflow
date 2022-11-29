// #include "graph_utils.h"
// #include "ift.h"

// #include <map>

// #include "GraphBLAS.h"
// #include "LAGraph.h"
// #include "LAGraphX.h"

// #define NUM_NODES 100

// void propagate_graphblas(GenericIFTCompactGraph& G) {
//   // make mapping of pointers to ints
//   std::map<GenericIFTGraphNode*, int> node_map;
//   for (int i = 0; i < G.num_nodes; ++i) {
//     auto* node = &G.nodes[i];
//     node_map[node] = i;
//   }

//   // make adjacency matrix
//   GrB_Matrix matrix;
//   GrB_Matrix_new(&matrix, GrB_BOOL, NUM_NODES, NUM_NODES);
//   for (int i = 0; i < G.num_edges; ++i) {
//     auto edge = G.edges[i];
//     GrB_Matrix_setElement_BOOL(matrix, true, node_map.at(edge.src), node_map.at(edge.dst));
//   }
  
//   // make graph
//   char* error;
//   LAGraph_Graph graph;
//   LAGraph_New(&graph, &matrix, LAGraph_ADJACENCY_DIRECTED, error);

//   // do BFS and output all visited nodes
//   GrB_Vector vector;
//   // gotta do this for all the non deterministic nodes, idk seems kinda like a lot of work but i suppose you could multithread each bfs call, but then is it really worth it to use graphblas? idk sober ashley
//   // you figure it out <3 -high ashley
//   // wait but also to check for the actual node, you can just check the index in the output vector
//   // i think it'll have a -1 or null if it is never reached
//   LAGr_BreadthFirstSearch(nullptr, &vector, graph, index, msg);

//   // then you get the indices and then you iterate through the node list
//   // get the node pointer from the index and then make it non deterministic if it is not already nondeterministic
// }

// #undef NUM_NODES