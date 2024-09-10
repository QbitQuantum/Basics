float Nimbits::getValue(String pointName)
{
  EthernetClient client;

  if (client.connect(GOOGLE, PORT))
  {
    client.print(F("GET /service/value?"));
    writeAuthParamsToClient(client);
    client.print(F("&point="));
    client.print(pointName);
    writeHostToClient(client);

    return atof(&getResponse(client)[0]);
  }
  else
  {
    return -1;
  }

}