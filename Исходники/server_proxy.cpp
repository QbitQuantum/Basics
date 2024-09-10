bool HandleRead(const Message &msg, Connection &con) {
  bool succeeded = false;
  bool locked = false;
  ReadFileOp op;
  auto client = msg.sender();
  vector<string> slaves;
  try {
    msg.GetContent(op);
    cout << msg.sender() << " requested readop with arg: " << op.file_name
         << endl;
    if (!(locked = gFileMap.LockFile(op.file_name))) {
      cout << "Failed to lock entry. File was locked in the meantime." << endl;
      goto finish;
    }
    // get slaves associated with the file
    slaves = GetFileSlaves(op.file_name);
    if (slaves.empty()) {
      cout << "Read request failed. File does not exist." << endl;
    } else {
      slaves.resize(1);
      succeeded = PerformOp(con, client, op.file_name, slaves);
    }
  } catch (...) {
    cout << "Invalid read request from " << msg.sender() << endl;
  }
  if (locked) {
    gFileMap.UnlockFile(op.file_name);
  }
finish:
  Message res_msg(kFileOpResult, SAFE_MESS);
  ResultFileOp res{op.file_name, succeeded};
  res_msg.SetContent(res);
  if (!con.SendMessage(res_msg, client)) {
    cout << "Failed to inform client of op result." << endl;
  }
  return succeeded;
}