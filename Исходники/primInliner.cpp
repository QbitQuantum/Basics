 void check_send(InterpretedIC* ic) {
   GrowableArray<RScope*>* sub = rs->subScopes(bci());
   if (sub->length() == 1 && sub->first()->isUntakenScope()) {
     // this send was never taken
   } else {
     was_executed = true;			// this send was taken in recompilee
   }
 }