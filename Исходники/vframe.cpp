void javaVFrame::print() {
  ResourceMark rm;
  vframe::print();
  tty->print("\t");
  method()->print_value();
  tty->cr();
  tty->print_cr("\tbci:    %d", bci());

  print_stack_values("locals",      locals());
  print_stack_values("expressions", expressions());

  GrowableArray<MonitorInfo*>* list = monitors();
  if (list->is_empty()) return;
  tty->print_cr("\tmonitor list:");
  for (int index = (list->length()-1); index >= 0; index--) {
    MonitorInfo* monitor = list->at(index);
    tty->print("\t  obj\t");
    if (monitor->owner_is_scalar_replaced()) {
      Klass* k = java_lang_Class::as_Klass(monitor->owner_klass());
      tty->print("( is scalar replaced %s)", k->external_name());
    } else if (monitor->owner() == NULL) {
      tty->print("( null )");
    } else {
      monitor->owner()->print_value();
      tty->print("(" INTPTR_FORMAT ")", (address)monitor->owner());
    }
    if (monitor->eliminated() && is_compiled_frame())
      tty->print(" ( lock is eliminated )");
    tty->cr();
    tty->print("\t  ");
    monitor->lock()->print_on(tty);
    tty->cr();
  }
}