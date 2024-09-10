bool recvFile(tcp::socket &socket, std::string filepath) {
    std::fstream file;
    file.open(filepath, std::ios::out | std::ios::binary);
    if(!file.is_open()) return false;
    size_t file_size = 0;
    boost::asio::read(socket, boost::asio::buffer(&file_size, sizeof(file_size)));
    size_t file_count = 0;
    while(file_count < file_size) {
        
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        boost::system::error_code ecode;
        size_t buffer_size = socket.read_some(boost::asio::buffer(buffer, 1024), ecode);
        if(ecode == boost::asio::error::eof)
            break;
        else if(ecode) throw boost::system::system_error(ecode);
        
        file.write(buffer,buffer_size);
        file_count += buffer_size;
        std::cout << ".";
        
        /*
        boost::array<char, 128> ar;
        boost::system::error_code ecode;
        size_t len = socket.read_some(boost::asio::buffer(ar), ecode);
        if(ecode == boost::asio::error::eof) break;
        else if(ecode) throw boost::system::system_error(ecode);
        file.write(ar.data(), len);
        */
    }
    file.close();
    return true;
}