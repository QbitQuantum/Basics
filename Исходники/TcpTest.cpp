int main(int argc, char* argv[])
{
    Socket skt(Socket::TCP);
    skt.bind("0.0.0.0", 0);
    skt.listen();
    while (true) {
        Socket c = skt.accept();
        cout << "Accept New Client" << endl;
        char buf[1024];
        int len = c.recv(buf, sizeof(buf));
        buf[len] = '\0';
        cout << "Request:" << buf << endl;
        c.send(buf, len);
    }
    return 0;
}