    virtual bool injectKeyEvents( const std::vector<KeyEventDesc> & intputlist)
    {
        if (!intputlist.size()) return false;


        INPUT * inputs = new INPUT[intputlist.size()];
        
        do
        {
            for (int pos=0; pos<intputlist.size(); ++pos)
            {
                inputs[pos].type = INPUT_KEYBOARD;
                inputs[pos].ki.wVk = intputlist[pos].keyval;
                
                if (intputlist[pos].type == KEY_EVENT_PRESSED) {
                
                    inputs[pos].ki.dwFlags =  0;
                } else {
                    inputs[pos].ki.dwFlags =  KEYEVENTF_KEYUP;
                }
                
                inputs[pos].ki.time = 0;
            }

            SendInput(intputlist.size(), inputs, sizeof(INPUT));

        }while(0);


        delete [] inputs;

        return true;
    }