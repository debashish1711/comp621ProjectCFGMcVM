#include CFG.h
#include Syntax2CFG.h

#include <iostream>
namespace {
class DataflowWorklist {
  SmallVector<const CFGBlock *, 20> worklist;
  llvm::BitVector enqueuedBlocks;
public:
  DataflowWorklist(const CFG &cfg) : enqueuedBlocks(cfg.getNumBlockIDs()) {}
  
  void enqueueSuccessors(const CFGBlock *block);
  const CFGBlock *dequeue();
};
}


  DataflowSolver(DFValuesTy& d) : D(d), solso(d.getAnalysisData()) {}
   ~DataflowSolver() {}
   /// runOnCFG - Computes dataflow values for all blocks in a CFG
      void runOnCFG(CFG& cfg, bool recordStmtValues = false) {
     // Set initial dataflow values and boundary conditions.
     D.InitializeValues(cfg);
     // Solve the dataflow equations.  This will populate D.EdgeDataMap
     // with dataflow values.
     SolveDataflowEquations(cfg, recordStmtValues);
   }
 
   /// runOnBlock - Computes dataflow values for a given block.  This
   ///  should usually be invoked only after previously computing
   ///  dataflow values using runOnCFG, as runOnBlock is intended to
      ///  only be used for querying the dataflow values within a block
   ///  with and Observer object.
   void runOnBlock(const CFGBlock *B, bool recordStmtValues) {
     BlockDataMapTy& M = D.getBlockDataMap();
     typename BlockDataMapTy::iterator I = M.find(B);
 
     if (I != M.end()) {
      TF.getVal().copyValues(I->second);
       ProcessBlock(B, recordStmtValues, AnalysisDirTag());
     }   
   }

void DataflowWorklist::enqueueSuccessors(const ::CFGBlock *block) {
  unsigned OldWorklistSize = worklist.size();
  for (CFGBlock::const_succ_iterator I = block->succ_begin(),
       E = block->succ_end(); I != E; ++I) {
    const CFGBlock *Successor = *I;
    if (!Successor || enqueuedBlocks[Successor->getBlockID()])
      continue;
    worklist.push_back(Successor);
    enqueuedBlocks[Successor->getBlockID()] = true;
  }
  if (OldWorklistSize == 0 || OldWorklistSize == worklist.size())
    return;

  // Rotate the newly added blocks to the start of the worklist so that it forms
  // a proper queue when we pop off the end of the worklist.
  std::rotate(worklist.begin(), worklist.begin() + OldWorklistSize,
              worklist.end());
}

const CFGBlock *DataflowWorklist::dequeue() {
  if (worklist.empty())
    return 0;
  const CFGBlock *b = worklist.back();
  worklist.pop_back();
  enqueuedBlocks[b->getBlockID()] = false;
  return b;
}

InsertIntoWorklist(Block *B);

Block* RemoveFromWorklist();

void Merge(CFG &cfg, const Block *B);

void TransferFnBlock(const Block *B, Direction::forward);

void TransferFnBlock(const Block *B, Direction::backward);
