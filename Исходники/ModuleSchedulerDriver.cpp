   void ModuloSchedulerDriverPass::duplicateValuesWithMultipleUses(BasicBlock* bb, Instruction* ind) {

       // While we keep duplicating nodes (and create more possible work), keep going
       bool keep_going = false; 
       do {
           keep_going = false; 
           // For each instruction in this BB
           for (BasicBlock::iterator it = bb->begin(); it!= bb->end(); ++it) {
               // if it is not the induction variable and it has more than one use
               if ((!dyn_cast<PHINode>(it)) &&  // Do not clone PHINodes
                       (ind != it) &&  // Do not clone induction pointer
                       // Only clone when you have more than one #uses
                       (instructionPriority::getLocalUses(it,bb) >1)) {

                   Instruction* cloned = it->clone(); // duplicate it
                    it->getParent()->getInstList().insert(it, cloned);
                    //Can also do: cloned->insertBefore(it); // on newer LLVMS
                    cloned->setName("cloned");
                    instructionPriority::replaceFirstUseOfWith(it, cloned);
                    // we may have created potential candidates for duplication. 
                    // you have to keep going
                   keep_going = true; 
               }
           } // foe rach inst
       } while (keep_going);
   }