TARGET_ADDRESS nub_allocate_stack_space
  (NUB nub,
   NUBTHREAD nubthread,
   NUBINT byte_count)
{
  LPDBGPROCESS                   process = (LPDBGPROCESS) nub;
  LPDBGTHREAD                    thread = (LPDBGTHREAD) nubthread;
  NUBINT                         code;
  DWORD                          count = (DWORD) byte_count;
  CONTEXT                        context;
  CONTEXT                        context_as_was;
  BOOL                           status_get_context, 
                                 status_set_context, 
                                 status_write,
                                 status_read;
  ALLOCATOR_INSTRUCTION_SEQUENCE instruction_sequence;
  ALLOCATOR_INSTRUCTION_SEQUENCE saved_stack_memory;
  DWORD                          SP;
  DWORD                          IP;
  DWORD                          instruction_position;
  DWORD                          bytes_written,
                                 bytes_read;
  DWORD                          expected_bp_address;
  BOOL                           spy_has_returned = FALSE;
  int                            second_chance_counter = 0;

  // Get the context for the thread.

  context.ContextFlags = CONTEXT_FULL;
  status_get_context =  get_thread_context(process, thread, &context);

  dylan_debugger_message("nub_allocate_stack_space: Thread Context before: %= : %=",
			 thread->ThreadHandle, status_get_context);
  dylan_debugger_message("Esp: %=  Eip: %=",
			 context.Esp,
			 context.Eip);

  context_as_was = context;

  if (thread->NeedsBreakpointReplacement)
    context.EFlags = context.EFlags & 0xFFFFFEFF;

  // Fill in the instruction sequence SUB ESP, <count>; INT 3

  instruction_sequence.Nop1 = 0x90;
  instruction_sequence.Nop2 = 0x90;
  instruction_sequence.SubInstruction = 0x81;
  instruction_sequence.SpecifyEsp = 0xEC;
  instruction_sequence.Immediate32 = count;
  instruction_sequence.BreakInstruction = 0xCC;

  SP = context.Esp;
  IP = context.Eip;

  // Write the instruction sequence onto the stack. The number of words we
  // are writing is small enough that this should work on both NT and
  // 95.

//context.Esp -= sizeof(ALLOCATOR_INSTRUCTION_SEQUENCE);
  instruction_position = context.Esp;
  context.Eip = instruction_position;

  // Save the data that was there originally. As a precaution, we will
  // re-write this back again if we have to abort the whole procedure.

  status_read =
     ReadProcessMemory
         (process->ProcessHandle,
          (LPCVOID) instruction_position,
          (LPVOID) &saved_stack_memory,
          sizeof(ALLOCATOR_INSTRUCTION_SEQUENCE),
          &bytes_read);

  // Out with the old, in with the new...

  status_write =
     ValidatedWriteProcessMemory 
         (process->ProcessHandle,
          (LPVOID) instruction_position,
          (LPVOID) &instruction_sequence,
          sizeof(ALLOCATOR_INSTRUCTION_SEQUENCE),
          &bytes_written);

  // Flush the instruction cache because we have written a segment of
  // code.

  FlushInstructionCache(process->ProcessHandle,
                        (LPCVOID) instruction_position,
                        sizeof(ALLOCATOR_INSTRUCTION_SEQUENCE));

  // Set the context of the thread so that it will execute the SUB instruction
  // and then return control to the debugger.

  status_set_context = SetThreadContext(thread->ThreadHandle, &context);

  if (!status_set_context) {
    status_write =
       ValidatedWriteProcessMemory 
           (process->ProcessHandle,
            (LPVOID) instruction_position,
            (LPVOID) &saved_stack_memory,
            sizeof(ALLOCATOR_INSTRUCTION_SEQUENCE),
            &bytes_written);
    SetThreadContext(thread->ThreadHandle, &context_as_was); // Just in case
    return(NULL);
  }

  // Remember the address at which we expect the breakpoint.

  expected_bp_address = instruction_position + 8;

  // Let the thread execute the fragment of code. Hopefully, that will give
  // us space on the stack that Windows 95 won't crap all over.

  suspend_all(process);
  process->ThreadRunningSpy = thread;
  thread->AddressOfSpyBreakpoint = expected_bp_address;

  // Explicitly continue all threads to release frozen threads;
  // they are all suspended at this point so won't be put back
  // into execution

  nub_threads_continue(nub);

  // Now do what it takes to put this Spy running Thread alone into execution

  execute_thread(thread);

  wait_for_stop_reason_internal
     (process, TRUE, 30000, &code, STOP_REASON_WAIT_SPY);

  if (code == SPY_RETURN_DBG_EVENT) {
    // Resume the suspended threads.
    resume_all_except(process, thread);

    // Write back the stack data that we crapped all over.
    status_write =
       ValidatedWriteProcessMemory 
           (process->ProcessHandle,
            (LPVOID) instruction_position,
            (LPVOID) &saved_stack_memory,
            sizeof(ALLOCATOR_INSTRUCTION_SEQUENCE),
            &bytes_written);

    // Get the context again. This should have ESP correctly set.
    status_get_context = GetThreadContext(thread->ThreadHandle, &context);

    dylan_debugger_message("nub_allocate_stack_space: Thread Context after: %= : %=",
			   thread->ThreadHandle, status_get_context);
    dylan_debugger_message("Esp: %=  Eip: %=",
			   context.Esp,
			   context.Eip);


    return((TARGET_ADDRESS) (context.Esp));
  }
  else {
    resume_all_except(process, thread);
    status_write =
       ValidatedWriteProcessMemory 
           (process->ProcessHandle,
            (LPVOID) instruction_position,
            (LPVOID) &saved_stack_memory,
            sizeof(ALLOCATOR_INSTRUCTION_SEQUENCE),
            &bytes_written);
    SetThreadContext(thread->ThreadHandle, &context_as_was);
    nub_debug_message("Error: Micro Spy call failed on Thread %=, code: %=",
		      (TARGET_ADDRESS)thread->ThreadHandle,
		      (TARGET_ADDRESS)code);
    return (NULL);
  }
  // Resume the suspended threads.
  resume_all_except(process, thread);

  // Write back the stack data that we crapped all over.

  status_write =
     ValidatedWriteProcessMemory 
         (process->ProcessHandle,
          (LPVOID) instruction_position,
          (LPVOID) &saved_stack_memory,
          sizeof(ALLOCATOR_INSTRUCTION_SEQUENCE),
          &bytes_written);

  // Get the context again. This should have ESP correctly set.
  status_get_context = GetThreadContext(thread->ThreadHandle, &context);

  return((TARGET_ADDRESS) (context.Esp));
}