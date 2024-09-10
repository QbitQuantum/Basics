 bool do_step(Algorithm& algo, poss_type step_poss, EDoStepType type
   , poss_type assoc_step_poss)
 {
   if(called_) {
     algo.terminate(false);
     return false;
   }
   AlgorithmStepTesting::do_step(algo,step_poss,type,assoc_step_poss);
   algo.track().journal_out() << "\n* Do step \"Step_2_p1\" then Jump to \"Step_1\"\n";
   algo.get_assoc_step(2,POST_STEP,1)->do_step(algo,2,DO_POST_STEP,1);
   algo.do_step_next("Step_1");
   called_ = true;
   return false;
 }