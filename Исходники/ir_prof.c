void 
__profile_call(ADDR caller, ADDR callee, char *caller_name, char *callee_name)
{
#ifdef _DEBUG
  return;
#else
  if (num_counts == 0)
    ir_prof_start();

  if (num_counts == sizeof_counts_array) {
    sizeof_counts_array *= 2;
    counts_array = (counts_entry *)REALLOC(
		    counts_array, sizeof_counts_array);
    PR_ASSERT(counts_array, "realloc of counts_array failed");
  }

  hash_entry(caller, callee, caller_name, callee_name);
#endif
}