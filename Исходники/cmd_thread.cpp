void CmdThread::onClient(DebuggerClient &client) {
  if (DebuggerCommand::displayedHelp(client)) return;
  if (client.argCount() > 1) {
    help(client);
    return;
  }

  if (client.argCount() == 0) {
    m_body = "info";
    auto res = client.xend<CmdThread>(this);
    client.print(res->m_out);
  } else if (client.arg(1, "list")) {
    processList(client);
  } else if (client.arg(1, "normal")) {
    m_body = "normal";
    client.sendToServer(this);
    client.info("Thread is running in normal mode now. Other threads will "
                 "interleave when they hit breakpoints as well.");
  } else if (client.arg(1, "sticky")) {
    m_body = "sticky";
    client.sendToServer(this);
    client.info("Thread is running in sticky mode now. All other threads "
                 "will wait until this thread finishes, when they hit "
                 "breakpoints.");
  } else if (client.arg(1, "exclusive")) {
    m_body = "exclusive";
    client.sendToServer(this);
    client.info("Thread is running in exclusive mode now. All other threads "
                 "will not break, even when they hit breakpoints.");
  } else {
    std::string snum = client.argValue(1);
    if (!DebuggerClient::IsValidNumber(snum)) {
      client.error("'[t]hread {index}' needs a numeric argument.");
      client.tutorial(
        "You will have to run '[t]hread [l]ist' first to see a list of valid "
        "numbers or indices to specify. Thread 1 is always your current "
        "thread. If that's the only thread on the list, you do not have "
        "another thread at break to switch to."
      );
      return;
    }

    int num = atoi(snum.c_str());
    DThreadInfoPtr thread = client.getThread(num);
    if (!thread) {
      processList(client, false);
      thread = client.getThread(num);
      if (!thread) {
        client.error("\"%s\" is not a valid thread index. Choose one from "
                      "this list:", snum.c_str());
        processList(client);
        return;
      }
    }

    if (thread->m_id == client.getCurrentThreadId()) {
      client.info("This is your current thread already.");
      return;
    }

    m_body = "switch";
    m_threads.push_back(thread);
    client.sendToServer(this);
    throw DebuggerConsoleExitException();
  }
}