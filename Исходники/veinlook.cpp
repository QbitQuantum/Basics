/*
address = absolute address of dump start
length = length in bytes
*/
void hexdump (DFHack::API& DF, uint32_t address, uint32_t length, int filenum)
{
    uint32_t reallength;
    uint32_t lines;
    lines = (length / 16) + 1;
    reallength = lines * 16;
    char *buf = new char[reallength];
    ofstream myfile;

    stringstream ss;
    ss << "hexdump" << filenum << ".txt";
    string name = ss.str();

    myfile.open (name.c_str());

    DF.ReadRaw(address, reallength, (uint8_t *) buf);
    for (int i = 0; i < lines; i++)
    {
        // leading offset
        myfile << "0x" << hex << setw(4) << i*16 << " ";
        // groups
        for(int j = 0; j < 4; j++)
        {
            // bytes
            for(int k = 0; k < 4; k++)
            {
                int idx = i * 16 + j * 4 + k;

                myfile << hex << setw(2) << int(static_cast<unsigned char>(buf[idx])) << " ";
            }
            myfile << " ";
        }
        myfile << endl;
    }
    delete buf;
    myfile.close();
}