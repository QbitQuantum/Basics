//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void elMundo::pasteLIFE_add (QString line)
{
    int cN = 0;
    for (QString::const_iterator it  = line.constBegin();
            it != line.constEnd(); it++) {
        QChar c = *it;
        if (c.isDigit()) cN = 10*cN + c.digitValue();
        else {
            if (cN == 0) cN = 1;
            switch (c.unicode()) {
            case '.':
                cX += cN;
                cN = 0;
                break;
            case '*':
            case 'O':
                while (cN > 0) {
                    add(cX, cY, elcDefault);
                    cX++;
                    cN--;
                }
            }
        }
    }
    cX = cX0;
    cY++;
}