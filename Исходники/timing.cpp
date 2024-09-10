 static void compareSnapshot(const Snapshot &from, const Snapshot &to, Entry *entry) {
   entry->time = diffTime(from.time, to.time);
   entry->memoryDiff = to.memory_curr - from.memory_curr;
   entry->allocTotal = to.memory_total - from.memory_total;
   for (int i = 0; i < 32; i++) {
     entry->delta_blk_cnt_curr[i] = to.blk_cnt_curr[i] - from.blk_cnt_curr[i];
     entry->delta_blk_cnt_total[i] = to.blk_cnt_total[i] - from.blk_cnt_total[i];
   }
 }