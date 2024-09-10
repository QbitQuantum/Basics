ResultCodes WaitJobNotification(Socket& kd_sock, Socket& kp_sock, const std::string& job_id){
  std::cout << "WaitJobNotification\n";
  ResultCodes rlt = OK;

  std::stringstream ss;
  ss << g_home_job_dir << job_id ;
  std::string job_path = ss.str();
  std::cout <<"job dir use to save file: " << job_path << std::endl;

  Message notify_msg_begin, notify_msg_end, change_state_msg(Header(MT_COMMAND, 0, 9999, 0, CMD_JOB_STATE), NULL),
      send_msg(Header(MT_COMMAND, 0, 9999, 0, CMD_JOB_STATE), NULL);
  std::vector<std::string> argv;
  std::string pjm_jobid, status, start_date, duration_time;

  // wait new status start running
  if(kd_sock.Recv(notify_msg_begin)){
    if(notify_msg_begin.GetHeader()->GetCommand() == CMD_JOB_STATE){
      argv = notify_msg_begin.GetCmdArgs();
      if(argv.size() > 4){
        pjm_jobid = argv[1];
        status = argv[2];
        start_date = argv[3];
        duration_time = argv[4];
        std::cout << pjm_jobid << " " << status << " " <<  start_date << " " << duration_time << std::endl;
        change_state_msg.AddArgv(job_id);
        change_state_msg.AddArgv(pjm_jobid);
        change_state_msg.AddArgv(status);
        change_state_msg.AddArgv(start_date);
        change_state_msg.AddArgv(duration_time);
      }
      std::cout << "submit job success\n";
    } else {
      rlt = SLAVEDAEMON_SUBMITJOB_ERR;
      std::cout << "wait notification job\n";
      return rlt;
    }
  }
  if(kp_sock.Send(change_state_msg)){
    std::cout << " send event change status to kp_server sucesss\n";
  } else {
    std::cout << " send event change status response to kp_server fail\n";
    rlt = SLAVEDAEMON_SUBMITJOB_ERR;
    return rlt;
  }

  // wait file
  while(true){
    int status = kd_sock.RecvListFile(job_path);
    std::cout << "status = " << status << std::endl;
    if(status > 0){
      std::cout << "Receieve new files success;\n";
      //Message req(Header(MT_COMMAND, 0, 0, 0, CMD_INITJOB), NULL), res;
//      /notify_msg.AddArgv(job_id);
      break;
    }
    sleep(3);
  }

  // wait last notify
  if(kd_sock.Recv(notify_msg_end)){
    if(notify_msg_end.GetHeader()->GetCommand() == CMD_JOB_STATE){
      argv = notify_msg_end.GetCmdArgs();
      if(argv.size() > 3){
        pjm_jobid = argv[1];
        status = argv[2];
        start_date = argv[3];
        duration_time = argv[4];
        std::cout << pjm_jobid << " " << status << " " <<  start_date << " " << duration_time << std::endl;
        send_msg.AddArgv(job_id);
        send_msg.AddArgv(pjm_jobid);
        send_msg.AddArgv(status);
        send_msg.AddArgv(start_date);
        send_msg.AddArgv(duration_time);
      }
      std::cout << "submit job success\n";
    } else {
      rlt = SLAVEDAEMON_SUBMITJOB_ERR;
      std::cout << "wait notification job\n";
    }
  }
  if(kp_sock.Send(send_msg)){
    std::cout << " send response to kp_server sucesss\n";
  } else {
    std::cout << " send response to kp_server fail\n";
    rlt = SLAVEDAEMON_SUBMITJOB_ERR;
  }
  return rlt;
}