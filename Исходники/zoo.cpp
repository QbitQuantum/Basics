void Zoo::FinishTrain() {
  for (auto i = 0; i < num_servers_; i++) {
    int dst_rank = server_id_to_rank(i);
    MessagePtr msg(new Message());
    msg->set_src(rank());
    msg->set_dst(dst_rank);
    msg->set_type(MsgType::Server_Finish_Train);
    SendTo(actor::kCommunicator, msg);
  }
}