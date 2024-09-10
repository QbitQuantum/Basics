BOOLEAN
NTAPI
VgaInterpretCmdStream(IN PUSHORT CmdStream)
{
    PUCHAR Base = (PUCHAR)VgaRegisterBase;
    USHORT Cmd;
    UCHAR Major, Minor;
    USHORT Count;
    UCHAR Index;
    PUSHORT Buffer;
    PUSHORT ShortPort;
    PUCHAR Port;
    UCHAR Value;
    USHORT ShortValue;

    /* First make sure that we have a Command Stream */
    if (!CmdStream) return TRUE;

    /* Loop as long as we have commands */
    while (*CmdStream)
    {
        /* Get the Major and Minor Function */
        Cmd = *CmdStream;
        Major = Cmd & 0xF0;
        Minor = Cmd & 0x0F;

        /* Move to the next command */
        CmdStream++;

        /* Check which major function this was */
        if (Major == 0x10)
        {
            /* Now let's see the minor function */
            if (Minor & CMD_STREAM_READ)
            {
                /* Now check the sub-type */
                if (Minor & CMD_STREAM_USHORT)
                {
                    /* The port is what is in the stream right now */
                    ShortPort = UlongToPtr((ULONG)*CmdStream);

                    /* Move to the next command */
                    CmdStream++;

                    /* Read USHORT from the port */
                    READ_PORT_USHORT(PtrToUlong(Base) + ShortPort);
                }
                else
                {
                    /* The port is what is in the stream right now */
                    Port = UlongToPtr((ULONG)*CmdStream);

                    /* Move to the next command */
                    CmdStream++;

                    /* Read UCHAR from the port */
                    READ_PORT_UCHAR(PtrToUlong(Base) + Port);
                }
            }
            else if (Minor & CMD_STREAM_WRITE_ARRAY)
            {
                /* Now check the sub-type */
                if (Minor & CMD_STREAM_USHORT)
                {
                    /* The port is what is in the stream right now */
                    ShortPort = UlongToPtr(Cmd);

                    /* Move to the next command and get the count */
                    Count = *(CmdStream++);

                    /* The buffer is what's next in the command stream */
                    Buffer = CmdStream++;

                    /* Write USHORT to the port */
                    WRITE_PORT_BUFFER_USHORT(PtrToUshort(Base) + ShortPort, Buffer, Count);

                    /* Move past the buffer in the command stream */
                    CmdStream += Count;
                }
                else
                {
                    /* The port is what is in the stream right now */
                    Port = UlongToPtr(Cmd);

                    /* Move to the next command and get the count */
                    Count = *(CmdStream++);

                    /* Add the base to the port */
                    Port = PtrToUlong(Port) + Base;

                    /* Move to next command */
                    CmdStream++;

                    /* Loop the cmd array */
                    for (; Count; Count--, CmdStream++)
                    {
                        /* Get the byte we're writing */
                        Value = (UCHAR)*CmdStream;

                        /* Write UCHAR to the port */
                        WRITE_PORT_UCHAR(Port, Value);
                    }
                }
            }
            else if (Minor & CMD_STREAM_USHORT)
            {
                /* Get the ushort we're writing and advance in the stream */
                ShortValue = *CmdStream;
                CmdStream++;

                /* Write USHORT to the port (which is in cmd) */
                WRITE_PORT_USHORT((PUSHORT)Base + Cmd, ShortValue);
            }
            else
            {
                /* The port is what is in the stream right now */
                Port = UlongToPtr((ULONG)*CmdStream);

                /* Get the uchar we're writing */
                Value = (UCHAR)*++CmdStream;

                /* Move to the next command */
                CmdStream++;

                /* Write UCHAR to the port (which is in cmd) */
                WRITE_PORT_UCHAR(PtrToUlong(Base) + Port, Value);
            }
        }
        else if (Major == 0x20)
        {
            /* Check the minor function. Note these are not flags anymore. */
            switch (Minor)
            {
                case 0:
                    /* The port is what is in the stream right now */
                    ShortPort = UlongToPtr(*CmdStream);

                    /* Move to the next command and get the count */
                    Count = *(CmdStream++);

                    /* Move to the next command and get the value to write */
                    ShortValue = *(CmdStream++);

                    /* Add the base to the port */
                    ShortPort = PtrToUlong(ShortPort) + (PUSHORT)Base;

                    /* Move to next command */
                    CmdStream++;

                    /* Make sure we have data */
                    if (!ShortValue) continue;

                    /* Loop the cmd array */
                    for (; Count; Count--, CmdStream++)
                    {
                        /* Get the byte we're writing */
                        ShortValue += (*CmdStream) << 8;

                        /* Write USHORT to the port */
                        WRITE_PORT_USHORT(ShortPort, ShortValue);
                    }
                    break;
                case 1:
                    /* The port is what is in the stream right now. Add the base too */
                    Port = *CmdStream + Base;

                    /* Move to the next command and get the count */
                    Count = *++CmdStream;

                    /* Move to the next command and get the index to write */
                    Index = (UCHAR)*++CmdStream;

                    /* Move to next command */
                    CmdStream++;

                    /* Loop the cmd array */
                    for (; Count; Count--, Index++)
                    {
                        /* Write the index */
                        WRITE_PORT_UCHAR(Port, Index);

                        /* Get the byte we're writing */
                        Value = (UCHAR)*CmdStream;

                        /* Move to next command */
                        CmdStream++;

                        /* Write UCHAR value to the port */
                        WRITE_PORT_UCHAR(Port, Value);
                    }
                    break;
                case 2:
                    /* The port is what is in the stream right now. Add the base too */
                    Port = *CmdStream + Base;

                    /* Read the current value and add the stream data */
                    Value = READ_PORT_UCHAR(Port);
                    Value &= *CmdStream++;
                    Value ^= *CmdStream++;

                    /* Write the value */
                    WRITE_PORT_UCHAR(Port, Value);
                    break;
                default:
                    /* Unknown command, fail */
                    return FALSE;
            }
        }
        else if (Major != 0xF0)
        {
            /* Unknown major function, fail */
            return FALSE;
        }

        /* Get the next command */
        Cmd = *CmdStream;
    }

    /* If we got here, return success */
    return TRUE;
}