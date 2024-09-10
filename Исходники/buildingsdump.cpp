void interleave_hex (DFHack::API& DF, vector < uint32_t > & addresses, uint32_t length)
{
    vector <char * > bufs;
    
    for(int counter = 0; counter < addresses.size(); counter ++)
    {
        char * buf = new char[length * 16];
        DF.ReadRaw(addresses[counter], length * 16, (uint8_t *) buf);
        bufs.push_back(buf);
    }
    cout << setfill('0');

    // output a header
    cout << "line offset ";
    for (int obj = 0; obj < addresses.size(); obj++)
    {
        cout << "0x" << hex << setw(9) << addresses[obj] << "  ";
    }
    cout << endl;
    
    for(int offs = 0 ; offs < length * 16; offs += 4)
    {
        if((!(offs % 16)) && offs != 0)
        {
            cout << endl;
        }
        cout << setfill(' ');
        cout << dec << setw(4) << offs/4 << " ";
        cout << setfill('0');
        cout << "0x" << hex << setw(4) << offs << " ";
        for (int object = 0; object < bufs.size(); object++)
        {
            // bytes
            for(int k = 0; k < 4; k++)
            {
                uint8_t data = bufs[object][offs + k];
                cout << hex << setw(2) << int(static_cast<unsigned char>(data)) << " ";
            }
            cout << " ";
        }
        cout << endl;
    }
    for(int counter = 0; counter < addresses.size(); counter ++)
    {
        delete bufs[counter];
    }
}