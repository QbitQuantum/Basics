void attendClient(int sock)
{
  MESSAGE msg;

  while(-1 != waitMessage(sock, &msg))
  {
    switch(msg.type)
    {
      case GCD: sendAnswer(sock,gcd(msg.param1,msg.param2));
                break;
      case LCM: sendAnswer(sock,lcm(msg.param1,msg.param2));
                break;
    }
  }
  close(sock);
}