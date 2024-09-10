  ThreadState* VMThreadState::state_as_object(STATE) {
    if(raise_reason_ == cNone && current_exception_.get()->nil_p()) return nil<ThreadState>();

    ThreadState* thread_state = ThreadState::create(state);
    thread_state->raise_reason(state, Fixnum::from(raise_reason_));
    thread_state->destination_scope(state, destination_scope());
    thread_state->throw_dest(state, throw_dest());
    thread_state->current_exception(state, current_exception());
    thread_state->raise_value(state, raise_value());
    return thread_state;
  }