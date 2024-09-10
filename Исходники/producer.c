void main(int argc, char ** argv)
{
  Circular_Buffer * cir_buffer;
  uint32 h_mem;
  sem_t s_procs_completed;

  char hello_world[STRING_LENGTH] = "Hello world";
  int ct = 0;

  if (argc != 3) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore>\n"); 
    Exit();
  }

  // Convert the command-line strings into integers for use as handles
  h_mem = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  s_procs_completed = dstrtol(argv[2], NULL, 10);

  // Map shared memory page into this process's memory space
  if ((cir_buffer = (Circular_Buffer *)shmat(h_mem)) == NULL) {
    Printf("Could not map the virtual address to the memory in "); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }


  while(ct < STRING_LENGTH){
    // Get the lock
    if(lock_acquire(cir_buffer->buffer_lock) != SYNC_SUCCESS){
      Printf("Get the lock failed !!!!!!!!!!!!!!!!!!\n");
      Exit();
    }

    /* Printf("Producer %d holds the lock %d, head = %d, tail = %d\n", getpid(), cir_buffer->buffer_lock, cir_buffer->head, cir_buffer->tail); */

    // Producer an item to the buffer
    if((cir_buffer->head + 1) % BUFFERSIZE == cir_buffer->tail){
      // The buffer is full, do nothing
    }
    else{
      // Insert the character
      cir_buffer->space[cir_buffer->head] = hello_world[ct];

      /* Printf("buffer lock: %d\n", cir_buffer->buffer_lock); */
      Printf("Producer %d inserted: %c\n", getpid(), hello_world[ct]);

      // Update head and ct
      ct++;
      cir_buffer->head = (cir_buffer->head + 1) % BUFFERSIZE;
    }

    // Release the lock
    if(lock_release(cir_buffer->buffer_lock) != SYNC_SUCCESS){
      Printf("Producer %d release the lock %d failed !!!!!!!!!!!!!!!!!!\n", getpid(), cir_buffer->buffer_lock);
      Exit();
    }
  }



  // Signal the semaphore to tell the original process that we're done
  Printf("Producer: PID %d is complete.\n", getpid());
  

  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }

  return;
}