


  const unsigned DstBlockID = Dst->getBlockID();
  
  // If we haven't analyzed the destination node, run the analysis now
  if (!analyzed[DstBlockID]) {
    mapReachability(Dst);
    analyzed[DstBlockID] = true;
  }
  
  // Return the cached result
  return reachable[DstBlockID][Src->getBlockID()];
}

// Maps reachability to a common node by walking the predecessors of the
// destination node.
void CFG::mapReachability(const CFGBlock *Dst) {
  SmallVector<const CFGBlock *, 11> worklist;
  llvm::BitVector visited(analyzed.size());
  
  ReachableSet &DstReachability = reachable[Dst->getBlockID()];
  DstReachability.resize(analyzed.size(), false);
  
  // Start searching from the destination node, since we commonly will perform
  // multiple queries relating to a destination node.
  worklist.push_back(Dst);
  bool firstRun = true;
  
  while (!worklist.empty()) {
    const Block *block = worklist.back();
    worklist.pop_back();
    
    if (visited[block->getBlockID()])
      continue;
    visited[block->getBlockID()] = true;
    
    // Update reachability information for this node -> Dst
    if (!firstRun) {
      // Don't insert Dst -> Dst unless it was a predecessor of itself
      DstReachability[block->getBlockID()] = true;
    }
    else
      firstRun = false;
    
    // Add the predecessors to the worklist.
    for (CFGBlock::const_pred_iterator i = block->pred_begin(),
         e = block->pred_end(); i != e; ++i) {
      worklist.push_back(*i);
    }
  }
}
