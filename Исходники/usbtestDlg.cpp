DWORD CUsbtestDlg::WaitWaveProc()
{
    while (true)
    {
        if (!run)
        {
            Sleep(1);
            continue;
        }        
        
        unsigned char* buffer = NULL;
        if (DEVCTRL_SUCCESS != WaitWavePacket(devID, &buffer, 30000))
        {
            Sleep(0);
            continue;
        }
        

        static int ifile = 0;

        if (ifile < 10)
        {
            char name[16];
            sprintf_s(name, 16, "wave_%d.log", ifile);

            FILE* pf = fopen(name, "w");
            for (int i = 0; i < waveSize*waveCount; i++)
            {
                fprintf_s(pf, "%d\n", buffer[i]);
            }
            fclose(pf);

            ifile++;
        }

        AddBuffer(devID, m_buffer, waveSize*waveCount);


        if (buffer)
        {
            m_buffer = buffer;
            curNo++;

            Invalidate();
            UpdateWindow();
        }
    }

    return 0;
}