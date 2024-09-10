void Win32_Raytrace_Work_Queue::add_entry(Raytrace_Work_Entry entry) {
  u32 new_next_entry_to_add =
      (this->next_entry_to_add + 1) % COUNT_OF(this->entries);
  assert(new_next_entry_to_add != this->next_entry_to_do);
  Raytrace_Work_Entry *entry_to_add = this->entries + this->next_entry_to_add;
  *entry_to_add = entry;
  _WriteBarrier();
  this->next_entry_to_add = new_next_entry_to_add;
  ReleaseSemaphore(this->semaphore, 1, 0);
}