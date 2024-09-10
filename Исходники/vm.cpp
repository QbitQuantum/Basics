  void VM::dequeue_thread(Thread* thread) {
    thread->queued(this, Qfalse);

    Tuple* scheduled = globals.scheduled_threads.get();

    /** @todo  Could it be in more than one somehow? --rue */
    List* list = try_as<List>(scheduled->at(this, thread->priority()->to_native()));
    (void) list->remove(this, thread);

    check_events();
  }