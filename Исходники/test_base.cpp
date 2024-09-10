void server_node::start()
{
    if (is_started())
        throw std::runtime_error("Server node \"" + m_path + "\" is already started");

    if (m_fork) {
        m_kill_sent = false;
        m_pid = fork();
        if (m_pid == -1) {
            m_pid = 0;
            int err = -errno;
            throw_error(err, "Failed to fork process");
        } else if (m_pid == 0) {
            char buffer[3][1024] = {
                " ",
                "-c"
            };
            std::string ios_path = ioserv_path();
            char * const args[] = {
                const_cast<char*>(ios_path.c_str()),
                buffer[1],
                const_cast<char*>(m_path.c_str()),
                NULL
            };
            auto ld_path = std::string("LD_LIBRARY_PATH=") + getenv("LD_LIBRARY_PATH");
            char * const env[] = {
                const_cast<char*>(ld_path.c_str()),
                NULL
            };
            if (execve(ios_path.data(), args, env) == -1) {
                int err = -errno;
                std::cerr << create_error(err, "Failed to start process \"%s\"", ios_path.c_str()).message() << std::endl;
                quick_exit(1);
            }
        }
    } else {
        m_node = dnet_parse_config(m_path.c_str(), 0);
    }

    if (!is_started())
        throw std::runtime_error("Can not start server with config file: \"" + m_path + "\"");
}