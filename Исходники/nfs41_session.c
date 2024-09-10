/* session slot mechanism */
static void init_slot_table(nfs41_slot_table *table) 
{
    uint32_t i;
    EnterCriticalSection(&table->lock);
    table->max_slots = NFS41_MAX_NUM_SLOTS;
    for (i = 0; i < NFS41_MAX_NUM_SLOTS; i++) {
        table->seq_nums[i] = 1;
        table->used_slots[i] = 0;
    }
    table->highest_used = table->num_used = 0;
    table->target_delay = 0;

    /* wake any threads waiting on a slot */
    if (slot_table_avail(table))
        WakeAllConditionVariable(&table->cond);
    LeaveCriticalSection(&table->lock);
}