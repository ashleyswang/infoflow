#pragma once

#include "ift.h"

#include <map>
#include <vector>

std::vector<GenericIFTGraphNode*> getNondeterministicNodes(const GenericIFTCompactGraph& G);
std::map<GenericIFTGraphNode *, std::vector<GenericIFTGraphNode *>> getGraphChildren(const GenericIFTCompactGraph &G);
