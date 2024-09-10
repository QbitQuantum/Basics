 std::string createMessage(int i, Pool& pool) {
     std::string msg("Message ");
     msg.append(pool.itoa(i));
     return msg;
 }