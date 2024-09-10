//------------------------------------------------------------------------------
PyObject* pybm_mid_req_update_fields(PyObject *self, PyObject *args)
{    
    if (g_ipcClient)
    {
        // C0 06 FF 20 00 B3 00
        std::vector<unsigned char> data(4);
        data[0] = 0x20;
        data[1] = 0x00;
        data[2] = 0xB3;
        data[3] = 0x00;
        IPCClient::IBusMessage msg(0xC0, 0xFF, data);

        g_ipcClient->send(msg);
    }

#if 0
    // C0 06 FF 20 02 8E 00 xx
    // C0 06 FF 20 01 B0 00 xx
    if (g_ipcClient)
    {
        std::vector<unsigned char> data(4);
        data[0] = 0x20;
        data[1] = 0x02;
        data[2] = 0x8E;
        data[3] = 0x00;
        IPCClient::IBusMessage msg(0xC0, 0xFF, data);

        g_ipcClient->send(msg);
    }
    my_sleep(100);
    
    if (g_ipcClient)
    {
        std::vector<unsigned char> data(4);
        data[0] = 0x20;
        data[1] = 0x01;
        data[2] = 0xB0;
        data[3] = 0x00;
        IPCClient::IBusMessage msg(0xC0, 0xFF, data);

        g_ipcClient->send(msg);
    }
#endif
    // return void
    Py_INCREF(Py_None);
    return Py_None;
}