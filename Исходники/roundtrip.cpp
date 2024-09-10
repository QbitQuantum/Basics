void serverMessageCallback(const TcpConnectionPtr& conn, Buffer* buffer, kimgbo::Timestamp receiveTime)
{
	int64_t message[2];
  while (buffer->readableBytes() >= frameLen)
  {
    memcpy(message, buffer->peek(), frameLen);
    buffer->retrieve(frameLen);
    message[1] = receiveTime.microSecondsSinceEpoch();
    conn->send(message, sizeof message);
  }
}