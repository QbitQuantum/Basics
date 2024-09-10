bool ProcessMessage(Message& msg, Socket& socket){
    bool isFinish = true;
    std::vector<std::string> argv = msg.GetCmdArgs();
    int argc = argv.size();

    Header hdr(MT_COMMAND, g_kdesk_port, 0, 0, CMD_ACK_OK);
    Message res_msg = Message(hdr, NULL);
    std::string job_id, exe_path;
    std::stringstream ss;
    std::vector<std::string> recv_files;
    switch(msg.GetHeader()->GetCommand()){
      case CMD_SUBMITJOB:
        std::cout << "CMD_SUBMITJOB <job id><exe file>";
        if(argc >= 2){
          job_id = argv[0];
          exe_path = argv[1];
          std::cout << "send response init job sucess, wait to receive folder: " << g_home_job_dir << "/" << job_id << std::endl;
          // Send response
          if(socket.Send(res_msg)){
            if(socket.RecvFolder(g_home_job_dir, recv_files)){
              std::cout << "receieve folder success\n";
              ProcessSubmitJob(socket, job_id, exe_path, recv_files);
            } else {
              std::cout << "receieve folder success\n";
              hdr.SetCommand(CMD_ACK_ERR);
              res_msg.SetHeader(hdr);
              socket.Send(res_msg);
            }

            // Clear job folderx
            if(g_home_job_dir.size() > 0){
              std::string cmd = std::string("rm -r ") + g_home_job_dir +  std::string("/") + job_id ;
              std::cout << "cmd: " << cmd << std::endl;
              std::string stdout = "ingore remove just test";// = SystemCommandUtils::Exec(cmd.c_str());
              std::cout << "stdout: " << stdout << std::endl;
            }
          } else {
            std::cout << "send response int job fail\n";
          }
        } else {
          std::cout << "command argument is missing.\n ";
        }
        break;
      case CMD_GET_TIME_RESOURCE:
        std::cout << "CMD_GET_TIME_RESOURCE <kdesk acc> \n";
        if(argc >= 1){;
          if(RunKAccountJ(socket, argv[0])){
            std::cout << "success\n";
          } else{
            std::cout << "[ERR] run command fail\n";
          }
        } else {
          std::cout << "[ERR] command required arg is missing.\n";
        }
        break;
      case CMD_REMOVETUNNEL:
        std::cout << "CMD_REMOVETUNNEL\nExit now!!\n";
        exit(0);
        break;
      default:
        std::cout << "[ERR] Unknown message: " << msg.GetHeader()->GetCommand() << std::endl;
        break;
    }
    return isFinish;
}