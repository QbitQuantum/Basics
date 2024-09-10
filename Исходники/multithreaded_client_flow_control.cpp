 // work_queue work items is are automatically dequeued and called by proton
 // This function is called because it was queued by send()
 void do_send(const proton::message& m) {
     sender_.send(m);
     std::lock_guard<std::mutex> l(lock_);
     --queued_;                    // work item was consumed from the work_queue
     credit_ = sender_.credit();   // update credit
     sender_ready_.notify_all();       // Notify senders we have space on queue
 }