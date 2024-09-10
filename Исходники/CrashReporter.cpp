static void run_program(QString program, QString arg1, QString arg2, QString arg3, QString arg4, bool wait_until_finished){

#if defined(FOR_WINDOWS)

  char *p = strdup(program.toAscii());
  char *a1 = strdup(arg1.toAscii());
  char *a2 = strdup(arg2.toAscii());
  char *a3 = strdup(arg3.toAscii());
  char *a4 = strdup(arg4.toAscii());

  if(_spawnl(wait_until_finished ? _P_WAIT :  _P_DETACH, p, p, a1, a2, a3, a4, NULL)==-1){
    fprintf(stderr,"Couldn't launch crashreporter: \"%s\" \"%s\"\n",p,a1);
    SYSTEM_show_message(strdup(talloc_format("Couldn't launch crashreporter: \"%s\" \"%s\"\n",p,a1)));
    Sleep(3000);
  }

#elif defined(FOR_LINUX) || defined(FOR_MACOSX)
      
  //if(system(QString(QCoreApplication::applicationDirPath() + "/crashreporter " + key + " " + QString::number(getpid()) + "&").toAscii())==-1) { // how to fix utf-8 here ?
  QString a = "LD_LIBRARY_PATH=" + QString(getenv("LD_LIBRARY_PATH"));
  QString full_command = a + " " + program + " " + arg1 + " " + arg2 + " " + arg3 + " " + arg4;

  if (wait_until_finished==false)
    full_command += "&";

  fprintf(stderr, "Executing -%s-\n",full_command.toUtf8().constData());
  
  if(system(strdup(full_command.toUtf8().constData()))==-1) {
    SYSTEM_show_message(strdup(talloc_format("Couldn't start crashreporter. command: -%s-\n",full_command.toUtf8().constData())));
  }

#else
  #error "unknown system"
#endif

}