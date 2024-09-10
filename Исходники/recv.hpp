inline aid_t recv(Recver& recver, message& msg, match& mach)
{
  bool add_exit = check_exit(mach.match_list_);
  if (add_exit)
  {
    mach.match_list_.push_back(exit);
  }

  aid_t sender = recver.recv(msg, mach);
  if (add_exit && msg.get_type() == exit)
  {
    exit_code_t exc;
    std::string errmsg;
    msg >> exc >> errmsg;
    throw std::runtime_error(errmsg);
  }