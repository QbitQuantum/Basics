 static void my_child(stackful_actor self)
 {
   aid_t aid = self->recv();
   self->reply(aid);
 }