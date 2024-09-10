/* receiveBinary.
 *
*/
int receiveBinary(char **data)
{
    free(*data);
    *data=NULL;

    char localBuffer[BUFFER_LENGTH];
    int index = 0;
    int received = 0;
    int end = FALSE;
    int find = FALSE;

    if (connectEnd)
        end = TRUE;

    while (end == FALSE)
    {
        // copy all the received data in localBuffer and test if the end of data char is received
        while ((bufferEnd > bufferStart) && (!find))
        {
            if (clientBuffer[bufferStart] == '\n')
                find = TRUE; // end of data char received
            else
                localBuffer[index++] = clientBuffer[bufferStart++]; // copy data to localBuffer
        }

        /* end of data char find ? */
        if (find)
        {
            localBuffer[index++] = '\n';
            localBuffer[index] = '\0';
            bufferStart++;
            end = TRUE;
            printf("%s\n", localBuffer);

#ifdef WIN32
            *data = _strdup(localBuffer);
#else
            *data = strdup(localBuffer);
#endif
            return index*sizeof(char); // == data size
        }
        else // all data no yet 'received'
        {
            bufferStart = 0;
            received = recv(mainSocket, clientBuffer, BUFFER_LENGTH, 0);

            if (received < 0)
            {
                perror("receiveBinary error.");
                end = TRUE;
            }
            else if (!received) // that's all
            {
                connectEnd = TRUE;

                if (index > 0) // is there data in localBuffer ?
                {
                    localBuffer[index++] = '\n';
                    localBuffer[index] = '\0';
#ifdef WIN32
                    *data = _strdup(localBuffer);
#else
                    *data = strdup(localBuffer);
#endif
                    return index * sizeof(char); // == data size
                }
                else
                {
                    // nothing received
                    return ERROR_EMPTY_BUFF;
                }
            }
            else
            {
                // 'received' octets more received
                bufferEnd = received;
            }
        }
    }
    return ERROR_RECEIVING;
}