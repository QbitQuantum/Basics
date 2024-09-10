 void on_sendable(proton::sender &sender) override {
     while (sender.credit() && sent_ < total_) {
         id_value_ = sent_ + 1;
         message_.correlation_id(id_value_);
         message_.creation_time(proton::timestamp::now());
         sender.send(message_);
         sent_++;
     }
 }