GrowableArray<MonitorInfo*>* compiledVFrame::monitors() const {
  // Natives has no scope
  if (scope() == NULL) {
    nmethod* nm = code();
    Method* method = nm->method();
    assert(method->is_native(), "");
    if (!method->is_synchronized()) {
      return new GrowableArray<MonitorInfo*>(0);
    }
    // This monitor is really only needed for UseBiasedLocking, but
    // return it in all cases for now as it might be useful for stack
    // traces and tools as well
    GrowableArray<MonitorInfo*> *monitors = new GrowableArray<MonitorInfo*>(1);
    // Casting away const
    frame& fr = (frame&) _fr;
    MonitorInfo* info = new MonitorInfo(
        fr.get_native_receiver(), fr.get_native_monitor(), false, false);
    monitors->push(info);
    return monitors;
  }
  GrowableArray<MonitorValue*>* monitors = scope()->monitors();
  if (monitors == NULL) {
    return new GrowableArray<MonitorInfo*>(0);
  }
  GrowableArray<MonitorInfo*>* result = new GrowableArray<MonitorInfo*>(monitors->length());
  for (int index = 0; index < monitors->length(); index++) {
    MonitorValue* mv = monitors->at(index);
    ScopeValue*   ov = mv->owner();
    StackValue *owner_sv = create_stack_value(ov); // it is an oop
    if (ov->is_object() && owner_sv->obj_is_scalar_replaced()) { // The owner object was scalar replaced
      assert(mv->eliminated(), "monitor should be eliminated for scalar replaced object");
      // Put klass for scalar replaced object.
      ScopeValue* kv = ((ObjectValue *)ov)->klass();
      assert(kv->is_constant_oop(), "klass should be oop constant for scalar replaced object");
      Handle k(((ConstantOopReadValue*)kv)->value()());
      assert(java_lang_Class::is_instance(k()), "must be");
      result->push(new MonitorInfo(k(), resolve_monitor_lock(mv->basic_lock()),
                                   mv->eliminated(), true));
    } else {
      result->push(new MonitorInfo(owner_sv->get_obj()(), resolve_monitor_lock(mv->basic_lock()),
                                   mv->eliminated(), false));
    }
  }
  return result;
}