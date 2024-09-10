void RemotePluginClient::setVSTChunk(std::vector<char> chunk)
{
    std::cerr << "RemotePluginClient::setChunk: writing vst chunk.." << std::endl;
    std::cerr << "RemotePluginClient::setChunk: read vst chunk, size=" << chunk.size() << std::endl;
    writeOpcode(m_controlRequestFd, RemotePluginSetVSTChunk);
    writeRaw(m_controlRequestFd, chunk);
}