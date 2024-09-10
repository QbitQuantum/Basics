int ATCommandsInterface::tryReadLine()
{
  static bool lineDetected = false;

  //Block on serial read or incoming command
  DBG("Trying to read a new line from stream");
  int ret = m_pStream->waitAvailable(); //This can be aborted
  size_t readLen = 0;
  if(ret == OK)
  {
    ret = m_pStream->read((uint8_t*)m_inputBuf + m_inputPos, &readLen, AT_INPUT_BUF_SIZE - 1 - m_inputPos, 0); //Do NOT wait at this point
  }
  if(ret == OK)
  {
    m_inputPos+=readLen;
    m_inputBuf[m_inputPos] = '\0'; //Add null terminating character to ease the use of str* functions
    DBG("In buffer: [%s]", m_inputBuf);
  }

  if( ret == NET_INTERRUPTED ) //It is worth checking readLen as data might have been read even though the read was interrupted
  {
    DBG("Read was interrupted");
    return NET_INTERRUPTED; //0 chars were read
  }
  else if(readLen == 0)
  {
    DBG("Nothing read");
    return OK; //0 chars were read
  }

  DBG("Trying to process incoming line");
  bool lineProcessed = false;

  do
  {
    lineProcessed = false; //Reset flag

    DBG("New iteration");

    //Look for a new line
    if(!lineDetected)
    {
      DBG("No line detected yet");
      //Try to look for a starting CRLF
      char* crPtr = strchr(m_inputBuf, CR);
      /*
      Different cases at this point:
      - CRLF%c sequence: this is the start of a line
      - CRLFCR(LF) sequence: this is the end of a line (followed by the beginning of the next one)
      - LF: this is the trailing LF char of the previous line, discard
      - CR / CRLF incomplete sequence: more data is needed to determine which action to take
      - %c ... CR sequence: this should be the echo of the previous sequence
      - %c sequence: This might be the echo of the previous command; more data is needed to determine which action to take

      In every case, move mem at the beginning
      */
      if(crPtr != NULL)
      {
        DBG("CR char found");

#if 0
        //Discard all preceding characters (can do nothing if m_inputBuf == crPtr)
        memmove(m_inputBuf, crPtr, (m_inputPos + 1) - (crPtr-m_inputBuf)); //Move null-terminating char as well
        m_inputPos = m_inputPos - (crPtr-m_inputBuf); //Adjust m_inputPos
#endif

        //If the line starts with CR, this should be a result code
        if( crPtr == m_inputBuf )
        {
          //To determine the sequence we need at least 3 chars
          if(m_inputPos >= 3)
          {
            //Look for a LF char next to the CR char
            if(m_inputBuf[1] == LF)
            {
              //At this point we can check whether this is the end of a preceding line or the beginning of a new one
              if(m_inputBuf[2] != CR)
              {
                DBG("Beginning of new line found");
                //Beginning of a line
                lineDetected = true; //Move to next state-machine step
              }
              else
              {
                //End of an unprocessed line
                WARN("End of unprocessed line");
              }
              //In both cases discard CRLF
              DBG("Discarding CRLF");
              memmove(m_inputBuf, m_inputBuf + 2, (m_inputPos + 1) - 2); //Move null-terminating char as well
              m_inputPos = m_inputPos - 2; //Adjust m_inputPos
            }
            else
            {
              //This is completely unexpected, discard the CR char to try to recover good state
              WARN("Unexpected %c char (%02d code) found after CR char", m_inputBuf[1]);
              memmove(m_inputBuf, m_inputBuf + 1, (m_inputPos + 1) - 1); //Move null-terminating char as well
              m_inputPos = m_inputPos - 1; //Adjust m_inputPos
            }
          }
        }
        //if the line does NOT begin with CR, this can be an echo of the previous command, process it
        else
        {
          int crPos = crPtr - m_inputBuf;
          int lfOff = 0; //Offset for LF if present
          DBG("New line found (possible echo of command)");
          //This is the end of line
          //Replace m_inputBuf[crPos] with null-terminating char
          m_inputBuf[crPos] = '\0';
          //Check if there is a LF char afterwards
          if(m_inputPos - crPos >= 1)
          {
            if(m_inputBuf[crPos+1] == LF)
            {
              lfOff++; //We will discard LF char as well
            }
          }
          //Process line
          int ret = processReadLine();
          if(ret)
          {
            m_inputPos = 0;
            m_inputBuf[0] = '\0'; //Always have a null-terminating char at start of buffer
            lineDetected = false;
            return ret;
          }

          //If sendData has been called, all incoming data has been discarded
          if(m_inputPos > 0)
          {
            memmove(m_inputBuf, m_inputBuf + crPos + lfOff + 1, (m_inputPos + 1) - (crPos + lfOff + 1)); //Move null-terminating char as well
            m_inputPos = m_inputPos - (crPos + lfOff + 1); //Adjust m_inputPos
          }
          DBG("One line was successfully processed");
          lineProcessed = true; //Line was processed with success
          lineDetected = false; //Search now for a new line
        }
      }
      else if(m_inputBuf[0] == LF) //If there is a remaining LF char from the previous line, discard it
      {
        DBG("Discarding single LF char");
        memmove(m_inputBuf, m_inputBuf + 1, (m_inputPos + 1) - 1); //Move null-terminating char as well
        m_inputPos = m_inputPos - 1; //Adjust m_inputPos
      }
    }

    //Look for the end of line
    if(lineDetected)
    {
      DBG("Looking for end of line");
      //Try to look for a terminating CRLF
      char* crPtr = strchr(m_inputBuf, CR);
      /*
      Different cases at this point:
      - CRLF sequence: this is the end of the line
      - CR%c sequence : unexpected
      - CR incomplete sequence: more data is needed to determine which action to take
      */

      //Try to look for a '>' (greater than character) that marks an entry prompt
      char* greaterThanPtr = strchr(m_inputBuf, GD);
      /*
      This character must be detected as there is no CRLF sequence at the end of an entry prompt
       */

      if(crPtr != NULL)
      {
        DBG("CR char found");
        int crPos = crPtr - m_inputBuf;
        //To determine the sequence we need at least 2 chars
        if(m_inputPos - crPos >= 2)
        {
          //Look for a LF char next to the CR char
          if(m_inputBuf[crPos + 1] == LF)
          {
            DBG("End of new line found");
            //This is the end of line
            //Replace m_inputBuf[crPos] with null-terminating char
            m_inputBuf[crPos] = '\0';
            //Process line
            int ret = processReadLine();
            if(ret)
            {
              m_inputPos = 0;
              m_inputBuf[0] = '\0'; //Always have a null-terminating char at start of buffer
              lineDetected = false;
              return ret;
            }

            //If sendData has been called, all incoming data has been discarded
            if(m_inputPos > 0)
            {
              //Shift remaining data to beginning of buffer
              memmove(m_inputBuf, m_inputBuf + crPos + 2, (m_inputPos + 1) - (crPos + 2)); //Move null-terminating char as well
              m_inputPos = m_inputPos - (crPos + 2); //Adjust m_inputPos
            }

            DBG("One line was successfully processed");
            lineProcessed = true; //Line was processed with success
          }
          else
          {
            //This is completely unexpected, discard all chars till the CR char to try to recover good state
            WARN("Unexpected %c char (%02d code) found in incoming line", m_inputBuf[crPos + 1]);
            memmove(m_inputBuf, m_inputBuf + crPos + 1, (m_inputPos + 1) - (crPos + 1)); //Move null-terminating char as well
            m_inputPos = m_inputPos - (crPos + 1); //Adjust m_inputPos
          }
          lineDetected = false; //In both case search now for a new line
        }
      }
      else if(greaterThanPtr != NULL)
      {
        DBG("> char found");
        int gdPos = greaterThanPtr - m_inputBuf;
        //To determine the sequence we need at least 2 chars
        if(m_inputPos - gdPos >= 2)
        {
          //Look for a space char next to the GD char
          if(m_inputBuf[gdPos + 1] == ' ')
          {
            //This is an entry prompt
            //Replace m_inputBuf[gdPos] with null-terminating char
            m_inputBuf[gdPos] = '\0';

            //Shift remaining data to beginning of buffer
            memmove(m_inputBuf, m_inputBuf + gdPos + 1, (m_inputPos + 1) - (gdPos + 1)); //Move null-terminating char as well
            m_inputPos = m_inputPos - (gdPos + 1); //Adjust m_inputPos

            //Process prompt
            ret = processEntryPrompt();
            if(ret)
            {
              m_inputPos = 0;
              m_inputBuf[0] = '\0'; //Always have a null-terminating char at start of buffer
              lineDetected = false;
              return ret;
            }

            DBG("One line was successfully processed");
            lineProcessed = true; //Line was processed with success
          }
          else
          {
            //This is completely unexpected, discard all chars till the GD char to try to recover good state
            WARN("Unexpected %c char (%02d code) found in incoming line", m_inputBuf[gdPos + 1]);
            memmove(m_inputBuf, m_inputBuf + gdPos + 1, (m_inputPos + 1) - (gdPos + 1)); //Move null-terminating char as well
            m_inputPos = m_inputPos - (gdPos + 1); //Adjust m_inputPos
          }
          lineDetected = false; //In both case search now for a new line
        }
      }
    }
  } while(lineProcessed); //If one complete line was processed there might be other incoming lines that can also be processed without reading the buffer again

  //If the line could not be processed AND buffer is full, it means that we won't ever be able to process it (buffer too short)
  if(m_inputPos == AT_INPUT_BUF_SIZE - 1)
  {
    //Discard everything
    m_inputPos = 0;
    m_inputBuf[0] = '\0'; //Always have a null-terminating char at start of buffer
    WARN("Incoming buffer is too short to process incoming line");
    //Look for a new line
    lineDetected = false;
  }

  DBG("Processed every full incoming lines");

  return OK;
}