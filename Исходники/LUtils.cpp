inline QStringList ProcessRun(QString cmd, QStringList args){
  //Assemble outputs
  QStringList out; out << "1" << ""; //error code, string output
  QProcess proc;
  QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
  env.insert("LANG", "C");
  env.insert("LC_MESSAGES", "C");
  proc.setProcessEnvironment(env);
  proc.setProcessChannelMode(QProcess::MergedChannels);
  if(args.isEmpty()){
    proc.start(cmd, QIODevice::ReadOnly);
  }else{
    proc.start(cmd,args ,QIODevice::ReadOnly);	  
  }
  QString info;
  while(!proc.waitForFinished(1000)){
    if(proc.state() == QProcess::NotRunning){ break; } //somehow missed the finished signal
    QString tmp = proc.readAllStandardOutput();
    if(tmp.isEmpty()){ proc.terminate(); }
    else{ info.append(tmp); }
  }
  out[0] = QString::number(proc.exitCode());
  out[1] = info+QString(proc.readAllStandardOutput());
  return out;	
}