void
ConstructLists (long my_id, time_info *local_time, long time_all)
{
   unsigned long start, finish;

   if (time_all)
      CLOCK(start);
   PartitionIterate(my_id, ConstructGridLists, TOP);
   BARRIER(G_Memory->synch, Number_Of_Processors);
   PartitionIterate(my_id, ConstructInteractionLists, BOTTOM);
   if (time_all)
      CLOCK(finish);

   if (time_all) {
      local_time[MY_TIME_STEP].list_time = finish - start;
   }
}