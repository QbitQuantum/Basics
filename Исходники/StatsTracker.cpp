void StatsTracker::computeReachableUncovered() {
  KModule *km = executor.kmodule;
  Module *m = km->module;
  static bool init = true;
  const InstructionInfoTable &infos = *km->infos;
  StatisticManager &sm = *theStatisticManager;
  
  if (init) {
    init = false;

    // Compute call targets. It would be nice to use alias information
    // instead of assuming all indirect calls hit all escaping
    // functions, eh?
    for (Module::iterator fnIt = m->begin(), fn_ie = m->end(); 
         fnIt != fn_ie; ++fnIt) {
      for (Function::iterator bbIt = fnIt->begin(), bb_ie = fnIt->end(); 
           bbIt != bb_ie; ++bbIt) {
        for (BasicBlock::iterator it = bbIt->begin(), ie = bbIt->end(); 
             it != ie; ++it) {
          if (isa<CallInst>(it) || isa<InvokeInst>(it)) {
            CallSite cs(it);
            if (isa<InlineAsm>(cs.getCalledValue())) {
              // We can never call through here so assume no targets
              // (which should be correct anyhow).
              callTargets.insert(std::make_pair(it,
                                                std::vector<Function*>()));
            } else if (Function *target = getDirectCallTarget(cs)) {
              callTargets[it].push_back(target);
            } else {
              callTargets[it] = 
                std::vector<Function*>(km->escapingFunctions.begin(),
                                       km->escapingFunctions.end());
            }
          }
        }
      }
    }

    // Compute function callers as reflexion of callTargets.
    for (calltargets_ty::iterator it = callTargets.begin(), 
           ie = callTargets.end(); it != ie; ++it)
      for (std::vector<Function*>::iterator fit = it->second.begin(), 
             fie = it->second.end(); fit != fie; ++fit) 
        functionCallers[*fit].push_back(it->first);

    // Initialize minDistToReturn to shortest paths through
    // functions. 0 is unreachable.
    std::vector<Instruction *> instructions;
    for (Module::iterator fnIt = m->begin(), fn_ie = m->end(); 
         fnIt != fn_ie; ++fnIt) {
      if (fnIt->isDeclaration()) {
        if (fnIt->doesNotReturn()) {
          functionShortestPath[fnIt] = 0;
        } else {
          functionShortestPath[fnIt] = 1; // whatever
        }
      } else {
        functionShortestPath[fnIt] = 0;
      }

      // Not sure if I should bother to preorder here. XXX I should.
      for (Function::iterator bbIt = fnIt->begin(), bb_ie = fnIt->end(); 
           bbIt != bb_ie; ++bbIt) {
        for (BasicBlock::iterator it = bbIt->begin(), ie = bbIt->end(); 
             it != ie; ++it) {
          instructions.push_back(it);
          unsigned id = infos.getInfo(it).id;
          sm.setIndexedValue(stats::minDistToReturn, 
                             id, 
                             isa<ReturnInst>(it)
#if LLVM_VERSION_CODE < LLVM_VERSION(3, 1)
                             || isa<UnwindInst>(it)
#endif
                             );
        }
      }
    }
  
    std::reverse(instructions.begin(), instructions.end());
    
    // I'm so lazy it's not even worklisted.
    bool changed;
    do {
      changed = false;
      for (std::vector<Instruction*>::iterator it = instructions.begin(),
             ie = instructions.end(); it != ie; ++it) {
        Instruction *inst = *it;
        unsigned bestThrough = 0;

        if (isa<CallInst>(inst) || isa<InvokeInst>(inst)) {
          std::vector<Function*> &targets = callTargets[inst];
          for (std::vector<Function*>::iterator fnIt = targets.begin(),
                 ie = targets.end(); fnIt != ie; ++fnIt) {
            uint64_t dist = functionShortestPath[*fnIt];
            if (dist) {
              dist = 1+dist; // count instruction itself
              if (bestThrough==0 || dist<bestThrough)
                bestThrough = dist;
            }
          }
        } else {
          bestThrough = 1;
        }
       
        if (bestThrough) {
          unsigned id = infos.getInfo(*it).id;
          uint64_t best, cur = best = sm.getIndexedValue(stats::minDistToReturn, id);
          std::vector<Instruction*> succs = getSuccs(*it);
          for (std::vector<Instruction*>::iterator it2 = succs.begin(),
                 ie = succs.end(); it2 != ie; ++it2) {
            uint64_t dist = sm.getIndexedValue(stats::minDistToReturn,
                                               infos.getInfo(*it2).id);
            if (dist) {
              uint64_t val = bestThrough + dist;
              if (best==0 || val<best)
                best = val;
            }
          }
          // there's a corner case here when a function only includes a single
          // instruction (a ret). in that case, we MUST update
          // functionShortestPath, or it will remain 0 (erroneously indicating
          // that no return instructions are reachable)
          Function *f = inst->getParent()->getParent();
          if (best != cur
              || (inst == f->begin()->begin()
                  && functionShortestPath[f] != best)) {
            sm.setIndexedValue(stats::minDistToReturn, id, best);
            changed = true;

            // Update shortest path if this is the entry point.
            if (inst==f->begin()->begin())
              functionShortestPath[f] = best;
          }
        }
      }
    } while (changed);
  }

  // compute minDistToUncovered, 0 is unreachable
  std::vector<Instruction *> instructions;
  for (Module::iterator fnIt = m->begin(), fn_ie = m->end(); 
       fnIt != fn_ie; ++fnIt) {
    // Not sure if I should bother to preorder here.
    for (Function::iterator bbIt = fnIt->begin(), bb_ie = fnIt->end(); 
         bbIt != bb_ie; ++bbIt) {
      for (BasicBlock::iterator it = bbIt->begin(), ie = bbIt->end(); 
           it != ie; ++it) {
        unsigned id = infos.getInfo(it).id;
        instructions.push_back(&*it);
        sm.setIndexedValue(stats::minDistToUncovered, 
                           id, 
                           sm.getIndexedValue(stats::uncoveredInstructions, id));
      }
    }
  }
  
  std::reverse(instructions.begin(), instructions.end());
  
  // I'm so lazy it's not even worklisted.
  bool changed;
  do {
    changed = false;
    for (std::vector<Instruction*>::iterator it = instructions.begin(),
           ie = instructions.end(); it != ie; ++it) {
      Instruction *inst = *it;
      uint64_t best, cur = best = sm.getIndexedValue(stats::minDistToUncovered, 
                                                     infos.getInfo(inst).id);
      unsigned bestThrough = 0;
      
      if (isa<CallInst>(inst) || isa<InvokeInst>(inst)) {
        std::vector<Function*> &targets = callTargets[inst];
        for (std::vector<Function*>::iterator fnIt = targets.begin(),
               ie = targets.end(); fnIt != ie; ++fnIt) {
          uint64_t dist = functionShortestPath[*fnIt];
          if (dist) {
            dist = 1+dist; // count instruction itself
            if (bestThrough==0 || dist<bestThrough)
              bestThrough = dist;
          }

          if (!(*fnIt)->isDeclaration()) {
            uint64_t calleeDist = sm.getIndexedValue(stats::minDistToUncovered,
                                                     infos.getFunctionInfo(*fnIt).id);
            if (calleeDist) {
              calleeDist = 1+calleeDist; // count instruction itself
              if (best==0 || calleeDist<best)
                best = calleeDist;
            }
          }
        }
      } else {
        bestThrough = 1;
      }
      
      if (bestThrough) {
        std::vector<Instruction*> succs = getSuccs(inst);
        for (std::vector<Instruction*>::iterator it2 = succs.begin(),
               ie = succs.end(); it2 != ie; ++it2) {
          uint64_t dist = sm.getIndexedValue(stats::minDistToUncovered,
                                             infos.getInfo(*it2).id);
          if (dist) {
            uint64_t val = bestThrough + dist;
            if (best==0 || val<best)
              best = val;
          }
        }
      }

      if (best != cur) {
        sm.setIndexedValue(stats::minDistToUncovered, 
                           infos.getInfo(inst).id, 
                           best);
        changed = true;
      }
    }
  } while (changed);

  for (std::set<ExecutionState*>::iterator it = executor.states.begin(),
         ie = executor.states.end(); it != ie; ++it) {
    ExecutionState *es = *it;
    uint64_t currentFrameMinDist = 0;
    for (ExecutionState::stack_ty::iterator sfIt = es->stack.begin(),
           sf_ie = es->stack.end(); sfIt != sf_ie; ++sfIt) {
      ExecutionState::stack_ty::iterator next = sfIt + 1;
      KInstIterator kii;

      if (next==es->stack.end()) {
        kii = es->pc;
      } else {
        kii = next->caller;
        ++kii;
      }
      
      sfIt->minDistToUncoveredOnReturn = currentFrameMinDist;
      
      currentFrameMinDist = computeMinDistToUncovered(kii, currentFrameMinDist);
    }
  }
}