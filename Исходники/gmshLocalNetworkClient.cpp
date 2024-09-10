bool gmshLocalNetworkClient::kill()
{
  // FIXME: we should kill all the clients in the list
  if(getPid() > 0) {
    if(KillProcess(getPid())){
      Msg::Info("Killed '%s' (pid %d)", _name.c_str(), getPid());
#if defined(HAVE_FLTK)
      if(FlGui::available())
        FlGui::instance()->setProgress("Killed", 0, 0, 0);
#endif
      setPid(-1);
      return true;
    }
  }
  setPid(-1);
  return false;
}