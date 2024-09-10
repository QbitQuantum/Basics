int main(int argc, char **argv) {
  Tserial* p;
  
  p = new Tserial();
  p->connect(UART_COMM_PORT, UART_BAUD_RATE, spNONE);
  
  ros::init(argc, argv, "yaw_publisher");
  
  ros::NodeHandle n;
  ros::Publisher yaw_pub = n.advertise<std_msgs::Float32>("yaw", 10);

  std_msgs::Float32 msg;

  while(ros::ok()) {
    char data_in[10];

    while(p->getChar() != '!');
    p->getArray(data_in, 8);
    
    msg.data = convertDataToVal2(data_in);
    yaw_pub.publish(msg);
  }
  
  p->disconnect();
  return 0;
}