  Object* ThreadState::state_as_object(STATE) {
    if(raise_reason_ == cNone && current_exception_.get()->nil_p()) return cNil;

    Exception* exc = Exception::create(state);
    exc->klass(state, G(exc_vm_internal));
    exc->set_ivar(state, state->symbol("reason"), Fixnum::from(raise_reason_));
    exc->set_ivar(state, state->symbol("destination"), destination_scope());
    exc->set_ivar(state, state->symbol("throw_dest"), throw_dest());

    exc->set_ivar(state, state->symbol("exception"),  current_exception());
    exc->set_ivar(state, state->symbol("value"),  raise_value());
    return exc;
  }