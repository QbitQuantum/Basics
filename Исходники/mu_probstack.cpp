void state_probability_queue::QueueEmptyFault()
{
#if (DBG > 0)
  fprintf(stderr, "\nQueueEmptyFault(sfq): ");
#endif
#ifndef SPLITFILE
  size_t read =
      fread(&stateArray[head_begin], sizeof(state_and_probability_pair),
	    min(global_front, head_size),
	    paging_file_top);
#else
  //make sure we do not read garbage after the states
  size_t read = paging_file_top->read(&stateArray[head_begin],
				      sizeof(state_and_probability_pair),
				      min(global_front, head_size));
#endif

  if (read > 0) {		//ok, some states are swapped in

    num_elts_head = read;
    global_front -= read;
#if (DBG > 0)
    fprintf(stderr, " read %d states from bottom", read);
#endif

  } else if (global_rear > 0) {	//paging_file_top is empty, but paging_file_bottom is not

#ifndef SPLITFILE
    fclose(paging_file_top);

    paging_file_top = paging_file_bottom;
    fseek(paging_file_top, 0, SEEK_SET);	//move to the beginning of the queue
    global_front = global_rear;

    if ((paging_file_bottom = tmpfile()) == NULL) {
      Error.Notrace("Internal: Error creating bottom paging file.");
    }
    global_rear = 0;		//bottom file is empty

    size_t read = fread(&stateArray[head_begin], sizeof(state), head_size,
			paging_file_top);

    num_elts_head = read;
    global_front -= read;
#else
    splitFile *fswap;

    //swap files
#if (DBG > 0)
    fprintf(stderr, " swapping top with bottom");
#endif
    fswap = paging_file_top;
    paging_file_top = paging_file_bottom;

    paging_file_bottom = fswap;

    paging_file_top->seek(0, SEEK_SET);	//move to the beginning of the queue
    paging_file_bottom->seek(0, SEEK_SET);	//reset bottom queue

    global_front = global_rear;
    global_rear = 0;		//bottom file is empty

    //now bottom entries are top entries and bottom file is empty. Reload a block!
    size_t read = paging_file_top->read(&stateArray[head_begin],
					sizeof(state_and_probability_pair),
					min(global_front, head_size));
#if (DBG > 0)
    fprintf(stderr, " read %d states from disk", read);
#endif

    num_elts_head = read;
    global_front -= read;
#endif

  } else if (num_elts_tail > 0) {	//paging_file_top AND paging_file_bottom are empty

#if (DBG > 0)
    fprintf(stderr, " using memory tail...");
#endif

    /* the disk queue is ended. this means that the only states we have
       to explore are the ones in the current tail window */
    unsigned long swap = tail_begin;
    tail_begin = head_begin;
    head_begin = swap;

    swap = tail_size;
    tail_size = head_size;
    head_size = swap;

    num_elts_head = num_elts_tail;
    num_elts_tail = 0;
    rear = 0;
  } else {			//no more states in both swap files, and the memory is empty: why do we call again?
    Error.Notrace("Internal: Attempt to read an empty state queue.");
  }

  front = 0;
}