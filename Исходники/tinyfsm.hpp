 void transit(void) {
   // DBG("*** Fsm::transit<S>() *** " << __PRETTY_FUNCTION__);
   current_state->exit();
   current_state = state_ptr<S>();
   current_state->entry();
 }