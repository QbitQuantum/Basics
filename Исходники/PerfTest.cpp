void
raw_sender(zmq::socket_t& s)
{
  for (size_t i = 0; i < ITERS; ++i)
  {
    zmq::message_t msg1(ARRAY_LEN(PART1)-1);
    memcpy(msg1.data(), PART1, msg1.size());
    s.send(msg1, ZMQ_SNDMORE);

    zmq::message_t msg2(ARRAY_LEN(PART2)-1);
    memcpy(msg2.data(), PART2, msg2.size());
    s.send(msg2, ZMQ_SNDMORE);

    zmq::message_t msg3(ARRAY_LEN(PART3)-1);
    memcpy(msg3.data(), PART3, msg3.size());
    s.send(msg3);

    zmq::message_t msg_res;
    s.recv(&msg_res, 0);

    if (i % 1000 == 0)
    {
      std::cout << ".";
      std::cout.flush();
    }
  }
}