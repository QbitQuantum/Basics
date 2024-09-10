int			main()
{
  char			*vars = getenv("QUERY_STRING");
  ANetwork::t_frameMonit	*frame = (ANetwork::t_frameMonit*) malloc(sizeof(ANetwork::t_frame));
  Network		net;

  std::cout << // "Content-type: application/json"
    "Access-Control-Allow-Origin: *" << std::endl << std::endl;
  if (!vars || sscanf(vars, "id=%d&data=%s", &(frame->idRequest), &(frame->data)) != 2) {
    std::cout << "{\"result\":\"Invalid parameters !\"}" << std::endl;
    return (-1);
  }
  try {
    net.init(9999, ANetwork::TCP_MODE);
    net.connect("127.0.0.1");
    net.getSocket()->write((void*) frame, sizeof(ANetwork::t_frameMonit));
    frame = (ANetwork::t_frameMonit*) net.read(sizeof(ANetwork::t_frameMonit));
    net.close();
    std::cout << "{\"result\":" << frame->data << "}" << std::endl;
  } catch (const std::exception &e) {
    std::cout << "{\"error\":\"" << e.what() << "\"}" << std::endl;
  }
};