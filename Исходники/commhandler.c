void CommHandler(void) //UART4 Interrupt handler implementation
{
    int c = GetChar();

    if (c >= 0)
    {
        //ConfigMode = 1;
        LEDon();
        //print("got char %02X\r\n", c);

        switch (c)
        {
            case 'b':
                print("rebooting into boot loader ...\r\n");
                Delay_ms(1000);
                bootloader();
                break;

            case 'c':
                debugCnt ^= 1;
                print("counter messages %s\r\n", debugCnt ? "on" : "off");
                break;

            case 'd':
                debugPrint ^= 1;
                print("debug messages %s\r\n", debugPrint ? "on" : "off");
                break;

            case 'g':
                Delay_ms(100);
                PutChar('x');

                for (int i = 0; i < CONFIGDATASIZE; i++)
                {
                    uint8_t data = configData[i];
                    PutChar(data);
                }

                break;

            case 'G':
                printConfig();
                break;

#if 0

            case 'H':
                if (CharAvailable() >= CONFIGDATASIZE)
                {
                    for (int i = 0; i < CONFIGDATASIZE; i++)
                    {
                        uint8_t data = GetChar();

                        if (data <= LARGEST_CONFIGDATA)
                        {
                            configData[i] = data;
                        }
                    }

                    configSave();
                }
                else
                {
                    UnGetChar(c); // try again in next loop
                }

                break;
#endif

            case 'h':
                for (int i = 0; i < CONFIGDATASIZE; i++)
                {
                    int data;

                    while ((data = GetChar()) < 0)
                        ;

                    if (data <= LARGEST_CONFIGDATA)
                    {
                        configData[i] = data;
                    }
                }

                configSave();
                break;

            case 'i':
                ConfigMode = 1;
                break;

            case 'j':
                ConfigMode = 0;
                break;

            case 'o':
                debugOrient ^= 1;
                print("Orientation messages %s\r\n", debugOrient ? "on" : "off");
                break;

            case 'p':
                debugPerf ^= 1;
                print("performance messages %s\r\n", debugPerf ? "on" : "off");
                break;

            case 'r':
                debugRC ^= 1;
                print("RC messages %s\r\n", debugRC ? "on" : "off");
                break;

            case 'R':
                print("rebooting...\r\n");
                Delay_ms(1000);
                reboot();
                break;

            case 's':
                debugSense ^= 1;
                print("Sensor messages %s\r\n", debugSense ? "on" : "off");
                break;

            case 'u':
            {
                extern int bDeviceState;
                printUSART("\r\nYY bDeviceState %3d  VCPConnectMode %d\r\n", bDeviceState, GetVCPConnectMode());
                break;
            }

            case '+':
                testPhase += 0.1;
                print("test phase output %5.1f\r\n", testPhase);
                break;

            case '-':
                testPhase -= 0.1;
                print("test phase output %5.1f\r\n", testPhase);
                break;

            default:
                // TODO
                break;
        }
    }
}