 static void echo(actor<stackful>& self)
 {
   try
   {
     while (true)
     {
       message msg;
       aid_t sender = self.recv(msg);
       match_t type = msg.get_type();
       if (type == atom("echo"))
       {
         self.send(sender, msg);
       }
       else
       {
         break;
       }
     }
   }
   catch (std::exception& ex)
   {
     std::cerr << "echo except: " << ex.what() << std::endl;
   }
 }