void TR::CompilationController::shutdown()
   {
   tlsFree(OMR::compilation);
   if (!_useController)
      return;

   // would like to free all entries in the pool of compilation plans
   int32_t remainingPlans = TR_OptimizationPlan::freeEntirePool();

   // print some stats
   if (verbose() >= LEVEL1)
      {
      fprintf(stderr, "Remaining optimizations plans in the system: %d\n", remainingPlans);
      }
   _compilationStrategy->shutdown();
   }