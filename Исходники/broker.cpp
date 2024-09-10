 // Only called if we have credit. Return true if we sent a message.
 bool do_send(queue* q, proton::sender &s) {
     proton::message m;
     bool popped =  q->pop(m, has_messages_callback_);
     if (popped)
         s.send(m);
     /// if !popped the queue has saved the callback for later.
     return popped;
 }