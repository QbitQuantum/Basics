void win_ctrl_z(HANDLE ctrlz)
{
    int i;
    int *p;
    DWORD rc;
    DWORD size;
    INPUT_RECORD input[EVENTSIZE];

    rc = WaitForSingleObject(ctrlz, 0);

    if (rc == WAIT_FAILED)
    {
        fprintf(stderr, "WaitForSingleObject failed: %d\n", GetLastError());
    }
    else if (rc == WAIT_OBJECT_0)
    {
        if (!ReadConsoleInput(ctrlz, input, EVENTSIZE, &size))
        {
            fprintf(stderr, "ReadConsoleInput failed: %d\n", GetLastError());
        }
        else
        {
            for (i = 0; i < size; ++i)
            {
                if (input[i].EventType == KEY_EVENT)
                {
                    if (input[i].Event.KeyEvent.bKeyDown &&
                            (input[i].Event.KeyEvent.uChar.AsciiChar == 0x1A  ||
                             input[i].Event.KeyEvent.uChar.AsciiChar == 0x01))
                    {
                        switch (ctrlzbind)
                        {
                        case BIND_DPORT:
                            p = &dst_port;
                            break;
                        case BIND_TTL:
                            p = &src_ttl;
                            break;
                        default:
                            printf("[winctrl_z]: error binding port or ttl, disabling ctrl-a "
                                   "and ctrl-z\n");
                            ctrlzbind = BIND_NONE;
                            return;
                        }

                        if (input[i].Event.KeyEvent.uChar.AsciiChar == 0x01)
                        {
                            if (*p > 0)
                                (*p)--;
                        }
                        else
                            (*p)++;

                        printf("\b\b\b\b\b\b\b\b\b");
                        printf("%d: ", *p);
                        fflush(stdout);
                        break;
                    }
                }
            }
        }
    }
    FlushConsoleInputBuffer(ctrlz);
    ResetEvent(ctrlz);
}