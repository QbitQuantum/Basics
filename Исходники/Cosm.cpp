void CosmClient::sendData(uint32_t feedId, char datastreamId[], double dataToSend)
{
    if (_client.connect("api.cosm.com", 80)) {
        Serial.println("Connecting to Cosm...");

        _client.print("PUT /v2/feeds/");
        _client.print(feedId);
        _client.print("/datastreams/");
        _client.print(datastreamId);
        _client.print(".csv HTTP/1.1\n");
        _client.print("Host: api.cosm.com\n");

        _client.print("X-ApiKey: ");
        _client.print(_api);
        _client.print("\n");
        _client.print("Content-Length: ");

        int lengthOfData = getLength(dataToSend);
        _client.println(lengthOfData, DEC);

        _client.print("Content-Type: text/csv\n");
        _client.println("Connection: close\n");

        _client.print(dataToSend, DEC);
    }
}