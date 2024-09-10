void RemoteSyslogChannel::log(const Message& msg)
{
    Poco::FastMutex::ScopedLock lock(_mutex);

    if (!_open) open();

    std::string m;
    m.reserve(1024);
    m += '<';
    Poco::NumberFormatter::append(m, getPrio(msg) + _facility);
    m += '>';
    if (_bsdFormat)
    {
        Poco::DateTimeFormatter::append(m, msg.getTime(), BSD_TIMEFORMAT);
        m += ' ';
        m += _host;
    }
    else
    {
        m += "1 "; // version
        Poco::DateTimeFormatter::append(m, msg.getTime(), SYSLOG_TIMEFORMAT);
        m += ' ';
        m += _host;
        m += ' ';
        m += _name;
        m += ' ';
        Poco::NumberFormatter::append(m, msg.getPid());
        m += ' ';
        m += msg.getSource();
    }
    m += ' ';
    m += msg.getText();

    _socket.sendTo(m.data(), static_cast<int>(m.size()), _socketAddress);
}