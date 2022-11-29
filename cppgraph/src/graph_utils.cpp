#include "graph_utils.h"

/* Creates vector of non-deterministic nodes in a graph */
std::vector<GenericIFTGraphNode*> getNondeterministicNodes(const GenericIFTCompactGraph& G) {
  std::vector<GenericIFTGraphNode*> output;
  for (uint64_t i = 0; i < G.num_nodes; ++i) {
    auto node = G.nodes[i];
    if ((node.flags & IFTGraphNodeFlags_Nondeterministic) > 0) {
      output.push_back(&node);
    }
  }
}


/* Creates a map with each node mapping to a vector of their children */
std::map<GenericIFTGraphNode *, std::vector<GenericIFTGraphNode *>> getGraphChildren(const GenericIFTCompactGraph& G) {
  std::map<GenericIFTGraphNode *, std::vector<GenericIFTGraphNode *>> output;
  for (uint64_t i = 0; i < G.num_edges; ++i) {
    auto edge = G.edges[i];
    output[edge.src].push_back(edge.dst);
  }
}