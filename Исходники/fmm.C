void
PartitionGrid (long my_id, time_info *local_time, long time_all)
{
   unsigned long start = 0, finish;

   if (time_all)
      CLOCK(start);
   if (Partition_Flag == COST_ZONES)
      CostZones(my_id);
   if (time_all) {
      CLOCK(finish);
      local_time[MY_TIME_STEP].partition_time = finish - start;
   }
}