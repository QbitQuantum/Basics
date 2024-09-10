void WiFiClient::stopAll()
{
    for (WiFiClient* it = _s_first; it; it = it->_next) {
        ClientContext* c = it->_client;
        if (c) {
            c->abort();
            c->unref();
            it->_client = 0;
        }
    }
}