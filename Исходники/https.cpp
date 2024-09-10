int main(int argc, char *argv[])
{
    try
    {
        SocketHandler h;
        if (argc > 1 && !strcmp(argv[1], "-server"))
        {
            ListenSocket<tSocket> l(h);
            l.Bind(4443);
            h.Add(&l);
            while (h.GetCount())
            {
                h.Select(1, 0);
            }
        }
        else
        {
            std::string host = argc > 1 ? argv[1] : "www.alhem.net";
            tSocket sock(h, host);
            h.Add(&sock);
            while (h.GetCount())
            {
                h.Select(1, 0);
            }
        }
    }
    catch (const Exception& e)
    {
        printf("%s\n", e.ToString().c_str());
    }
}