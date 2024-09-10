double ReadIR(Tserial& serial)
{
    int nbytes = serial.getNbrOfBytes();
    std::stringstream ss; 
    for(int i = 0; i < nbytes; i++)
    {
        ss << serial.getChar();
    }
    double distance;
    while(ss.good())
    {
        std::string str;
        std::getline(ss,str);
        if(!str.empty())
        {
            std::stringstream test(str);
            test >> distance;
        }
    }