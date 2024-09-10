void ApiServerSetColorTask::startParseSetColorTask(QByteArray buffer)
{
    API_DEBUG_OUT << QString(buffer) << "task thread:" << thread()->currentThreadId();
    bool isReadFail = false;

    // buffer can contains only something like this:
    // 1-34,9,125
    // 2-0,255,0;3-0,255,0;6-0,255,0;

    while (buffer.isEmpty() == false)
    {
        if (isReadFail == true)
        {
            qWarning() << "got it!";
        }

        // Check buffer length, minimum 7 - '2-0,0,0'
        if (buffer.length() < 7)
        {
            API_DEBUG_OUT << "error: buffer.length() < 7";
            isReadFail = true;
            goto end;
        }

        // Read led number
        int ledNumber = LightpackMath::getDigit(buffer[0]); // first char of ledNumber
        int ledNumber2 = LightpackMath::getDigit(buffer[1]); // second char of ledNumber
        if (ledNumber > 0)
        {
            if (buffer[1] == '-')
            {
                buffer.remove(0, 2); // remove "2-"
            }
            else if (ledNumber2 >= 0 && buffer[2] == '-')
            {
                ledNumber = ledNumber * 10 + ledNumber2; // 10,11,12..99
                buffer.remove(0, 3); // remove "10-"
            } else {
                API_DEBUG_OUT << "lednumber fail:" << QString(buffer);
                isReadFail = true;
                goto end;
            }
        } else {
            API_DEBUG_OUT << "isdigit fail:" << QString(buffer);
            isReadFail = true;
            goto end;
        }

        API_DEBUG_OUT << "lednumber-" << ledNumber << "buff-" << QString(buffer);

        if (ledNumber <= 0 || ledNumber > m_numberOfLeds)
        {
            API_DEBUG_OUT << "ledNumber is out of bounds:" << ledNumber;
            isReadFail = true;
            goto end;
        }

        // Convert for using in zero-based arrays
        ledNumber = ledNumber - 1;

        // Read led red, green and blue colors to buffer buffRgb[]
        int indexBuffer = 0;
        int indexRgb = 0;        
        memset(buffRgb, 0, sizeof(buffRgb));

        bool isDigitExpected = true;
        for (indexBuffer = 0; indexBuffer < buffer.length(); indexBuffer++)
        {
            int d = LightpackMath::getDigit(buffer[indexBuffer]);
            if (d < 0)
            {
                if (buffer[indexBuffer] == ';')
                {
                    break;
                }
                else if (buffer[indexBuffer] != ',')
                {
                    API_DEBUG_OUT << "expected comma, buffer:" << QString(buffer) << indexBuffer << buffer[indexBuffer];
                    isReadFail = true;
                    goto end;
                }
                else if (isDigitExpected)
                {
                    API_DEBUG_OUT << "expected digit, buffer:" << QString(buffer) << indexBuffer << buffer[indexBuffer];
                    isReadFail = true;
                    goto end;
                }
                isDigitExpected = true;
                indexRgb++;
            } else {
                buffRgb[indexRgb] *= 10;
                buffRgb[indexRgb] += d;

                isDigitExpected = false;

                if (buffRgb[indexRgb] > 255)
                {
                    API_DEBUG_OUT << "rgb value > 255";
                    isReadFail = true;
                    goto end;
                }
            }
        }

        // Remove read colors
        buffer.remove(0, indexBuffer);

        // Save colors
        m_colors[ledNumber] = qRgb(buffRgb[bRed], buffRgb[bGreen], buffRgb[bBlue]);

        API_DEBUG_OUT << "result color:" << buffRgb[bRed] << buffRgb[bGreen] << buffRgb[bBlue]
                      << "buffer:" << QString(buffer);

        if (buffer[0] == ';')
        {
            // Remove semicolon
            buffer.remove(0, 1);

            API_DEBUG_OUT << "buffer.isEmpty() == " << buffer.isEmpty();
        }
    }

end:
    if (isReadFail)
    {
        API_DEBUG_OUT << "errors while reading buffer";
        emit taskParseSetColorIsSuccess(false);
    } else {
        API_DEBUG_OUT << "read setcolor buffer - ok";
        emit taskParseSetColorDone(m_colors);
        emit taskParseSetColorIsSuccess(true);
    }
}