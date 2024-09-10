void rsg::RsgCommHandler::setSrcData(const int64_t addr, const std::string& buff) {
    s4u::Comm *comm = (s4u::Comm*) addr;
    std::string *payload = new std::string(buff.data(), buff.length());
    comm->setSrcData((void*)payload, sizeof(void*));
}