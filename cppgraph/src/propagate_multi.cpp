#include "graph_utils.h"
#include "ift.h"

#include <pthread.h>

namespace {

struct Args {
  Args(pthread_mutex_t& mutex, 
       std::vector<GenericIFTGraphNode *>& nondeterministic_nodes, 
       std::map<GenericIFTGraphNode *, std::vector<GenericIFTGraphNode *>>& child_map) : 
    mutex(mutex), 
    nondeterministic_nodes(nondeterministic_nodes), 
    child_map(child_map) {}
    
  pthread_mutex_t& mutex;
  std::vector<GenericIFTGraphNode *>& nondeterministic_nodes;
  std::map<GenericIFTGraphNode *, std::vector<GenericIFTGraphNode *>>& child_map;
  int num_threads = 0;
};

void* update_flag(void *param) {
  Args* args = static_cast<Args*> (param);
  pthread_mutex_lock(&args->mutex);
  int id = args->num_threads++;
  pthread_mutex_unlock(&args->mutex);

  while (!args->nondeterministic_nodes.empty()) {
    pthread_mutex_lock(&args->mutex);
    GenericIFTGraphNode* node = args->nondeterministic_nodes.front();
    args->nondeterministic_nodes.erase(args->nondeterministic_nodes.begin());
    pthread_mutex_lock(&args->mutex);

    auto children = args->child_map[node];
    for (auto child : children) {
      if ((child->flags & IFTGraphNodeFlags_Nondeterministic) == 0) {
        child->flags = child->flags | IFTGraphNodeFlags_Nondeterministic;
        pthread_mutex_lock(&args->mutex);
        args->nondeterministic_nodes.push_back(child);
        pthread_mutex_unlock(&args->mutex);
      }
    }
    // printf("pid %d: writing to node %d\n", args->id, node->id);
    
  }
}

}

#define NUM_THREADS 10

void propagate_multi(GenericIFTCompactGraph& G) {
  pthread_mutex_t mutex;
  auto nd_nodes = getNondeterministicNodes(G);
  auto child_map = getGraphChildren(G);
  Args args = {mutex, nd_nodes, child_map};

  pthread_t threads[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], 0, &update_flag, (void*)&args);
  }

  for (auto thread : threads) pthread_join(thread, 0);
}

#undef NUM_THREADS