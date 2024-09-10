        void out(exlib::string& s)
        {
            exlib::wstring ws = utf8to16String(s);
            exlib::wchar *ptr = &ws[0];
            exlib::wchar *pend = ptr + ws.length();
            exlib::wchar *ptr2;
            DWORD dwWrite;

            while (ptr2 = (exlib::wchar *) qstrchr(ptr, L'\x1b'))
            {
                if (ptr2[1] == '[')
                {
                    WriteConsoleW(m_handle, ptr, (DWORD)(ptr2 - ptr), &dwWrite, NULL);

                    ptr2 += 2;

                    while (true)
                    {
                        if (ptr2[0] == 'm')
                        {
                            m_Now = m_wAttr;
                            m_wLight = m_wAttr & FOREGROUND_INTENSITY;
                            SetConsoleTextAttribute(m_handle, m_Now);
                            ptr2 ++;
                            break;
                        }

                        if (qisdigit(ptr2[0]))
                        {
                            if (ptr2[1] == 'm')
                            {
                                if (ptr2[0] == '0')
                                {
                                    m_Now = m_wAttr;
                                    m_wLight = m_wAttr & FOREGROUND_INTENSITY;
                                    SetConsoleTextAttribute(m_handle, m_Now);
                                }
                                ptr2 += 2;
                                break;
                            }

                            WORD mask, val;
                            WORD light = m_wLight;

                            if (ptr2[1] == ';')
                            {
                                if (ptr2[0] == '0')
                                    m_wLight = light = 0;
                                else if (ptr2[0] == '1')
                                    m_wLight = light = FOREGROUND_INTENSITY;
                                ptr2 += 2;
                            }

                            if (ptr2[0] == '3')
                            {
                                mask = 0xf0;
                                ptr2 ++;
                            }
                            else if (ptr2[0] == '4')
                            {
                                mask = 0x0f;
                                ptr2 ++;
                            }
                            else if (ptr2[0] == '9')
                            {
                                mask = 0xf0;
                                light |= FOREGROUND_INTENSITY;
                                ptr2 ++;
                            }
                            else if (ptr2[0] == '1' && ptr2[1] == '0')
                            {
                                mask = 0x0f;
                                light |= FOREGROUND_INTENSITY << 4;
                                ptr2 += 2;
                            }
                            else
                                break;

                            if (!qisdigit(ptr2[0]))
                                break;

                            val = ptr2[0] - '0';

                            if (val != 8)
                            {
                                if (val == 9)
                                {
                                    val = (m_wAttr & 0x0f) | (m_Now & 0xf0);

                                    m_Now = val | light;
                                    SetConsoleTextAttribute(m_handle, m_Now);
                                }
                                else
                                {
                                    val = (val & 2) | ((val & 1) ? 4 : 0)
                                          | ((val & 4) ? 1 : 0);

                                    if (mask == 0x0f)
                                        val <<= 4;

                                    m_Now = (m_Now & mask) | val | light;
                                    SetConsoleTextAttribute(m_handle, m_Now);
                                }
                            }

                            ptr2 ++;
                            if (ptr2[0] == 'm')
                            {
                                ptr2 ++;
                                break;
                            }
                        }
                    }
                }
                ptr = ptr2;
            }

            WriteConsoleW(m_handle, ptr, (DWORD)(pend - ptr), &dwWrite, NULL);
        }