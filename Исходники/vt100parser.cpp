void VT100Parser::decodeOSC(uchar character)
{

    if (!parameters.size() &&
            character >= 0x30 && character <= 0x3f) {

        decodeParameters(character);
    }
    else
    {
        if (decodeOscState ==  None) {
            appendParameter();
            if (parameters.size() != 1) {
                tokenFinished();
                return;
            }
            oscData.clear();
            switch (parameters.at(0)) {
            case 0:
                decodeOscState = ChangeWindowAndIconName;
                break;
            case 1:
                decodeOscState = ChangeIconTitle;
                break;
            case 2:
                decodeOscState = ChangeWindowTitle;
                break;
            case 4:
                // TODO: set 256-color palette
                decodeOscState = Other;
                break;
            case 105:
                decodeOscState = ExTermBlock;
                break;
            default:
                qDebug() << parameters;

                decodeOscState = Other;
            }
            oscData.append(QChar(character));
        }
        else if (character == 0x07 || (decodeOscState == Other && character == 0x5c)) {
            if (decodeOscState == ChangeWindowAndIconName || decodeOscState == ChangeWindowTitle) {
                //m_screen->setTitle(title);
            }
            else if(decodeOscState == ExTermBlock) {
                int index = oscData.indexOf(QChar(';'));
                QStringRef type = oscData.leftRef(index);
                QStringRef data = oscData.midRef(index+1);
                if(type.compare("HTML") == 0) {
                    int argIndexes[2] = {0,};
                    int argN = 0;
                    for(int i = 0; i < data.length(); ++i) {
                        if(data.at(i) == QChar(';')) {
                            argIndexes[argN++] = i;
                        }
                        if(argN == 2)
                            break;
                    }
                    QStringRef objectId = oscData.midRef(index + 1, argIndexes[0]);
                    QStringRef numLines = oscData.midRef(index + 1 + argIndexes[0] + 1,  argIndexes[1] - argIndexes[0] - 1);
                    QStringRef actualData = oscData.midRef(index + 1 + argIndexes[1] + 1);
                    int lines = numLines.toString().toInt();
                    for(int i = 0; i < lines-1; ++i)
                        screen.lineFeed();
                    emit htmlBlock(objectId.toString(), lines, actualData.toString());
                }
                else if(type.compare("JS")) {

                }
            }
            tokenFinished();
        }
        else {
            oscData.append(QChar(character));
        }
    }
}