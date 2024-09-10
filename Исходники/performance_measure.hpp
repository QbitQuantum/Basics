double performance_measure(F f)
{
   unsigned count = 1;
   double time, result;
#ifdef _WIN32
   int old_priority = GetThreadPriority(GetCurrentThread());
   SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
#endif
   //
   // Begin by figuring out how many times to repeat
   // the function call in order to get a measureable time:
   //
   do
   {
      boost::timer t;
      for(unsigned i = 0; i < count; ++i)
         f();
      time = t.elapsed();
      count *= 2;
      t.restart();
   }while(time < 0.5);

   count /= 2;
   result = time;
   //
   // Now repeat the measurement over and over
   // and take the shortest measured time as the
   // result, generally speaking this gives us
   // consistent results:
   //
   for(unsigned i = 0; i < 20u;++i)
   {
      boost::timer t;
      for(unsigned i = 0; i < count; ++i)
         f();
      time = t.elapsed();
      if(time < result)
         result = time;
      t.restart();
   }
#ifdef _WIN32
   SetThreadPriority(GetCurrentThread(), old_priority);
#endif
   return result / count;
}