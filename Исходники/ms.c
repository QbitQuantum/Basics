void run_child() {
  int s_pid;
  int m_pid;
  
  s_pid = fork();
  
  if(ISCHILD(s_pid)) {
    execl("./s", "sum", NULL);
    exit(1);
  } else if(s_pid < 0) {
    exit(1);
  }
  
  m_pid = fork(); 
  
  if(ISCHILD(m_pid)){
    execl("./m", "mul", NULL); 
    exit(1);
  } else if(m_pid < 0) {
    exit(1);
  }
  
  return;
}