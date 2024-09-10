double Formulaeditor::factor(qint32& nPosition, QString& strCharacter)
{
    qreal f = 0.0;
    qint32 wI = 0, wL = 0, wBeginn = 0, wError = 0;

    if	(strCharacter == str_char(0)) return 0.0;
    // read digit and save as float in f
    if (((strCharacter >= "0") && (strCharacter <= "9")) || (strCharacter == "."))
    {
        wBeginn = nPosition;

        do
        {
            char_n(nPosition, strCharacter);
        }
        while ((((strCharacter >= "0") && (strCharacter <= "9")) || (strCharacter == ".")));

        if (strCharacter == ".")
        {
            do
            {
                char_n(nPosition, strCharacter);
            }
            while (!(((qint8)strCharacter.at(0).digitValue() >= 0) && ((qint8)strCharacter.at(0).digitValue() <=  9))  || (strCharacter.at(0) == '.'));
        }

        QString g_strF = m_strFunction.mid(wBeginn - 1, nPosition - wBeginn);
        f = g_strF.toFloat();
    }
    else
    {
        QString strCharacterUpper = strCharacter.toUpper();
        if (strCharacter == "(")
        {
            char_n(nPosition, strCharacter);
            f = expression(nPosition, strCharacter);
            if (strCharacter == ")")
                char_n(nPosition, strCharacter);
        }
        else if (strCharacterUpper == "X")
        {
            char_n(nPosition, strCharacter);
            f = m_dFktValue;
        }
        else
        {
            bool gefunden = false;
            qint32 AnzStdFunctions = m_strStandardFunction.length() - 1;
            for (wI = 1; wI <= AnzStdFunctions; wI++)
            {
                wL = m_strStandardFunction.at(wI).length();
                QString strFunktionUpper = m_strFunction.mid(nPosition - 1, wL);
                strFunktionUpper = strFunktionUpper.toUpper();
                QString strDummy(m_strStandardFunction.at(wI));
                strDummy = strDummy.toUpper();
                if (strFunktionUpper == strDummy)
                {
                    gefunden = true;
                    nPosition = nPosition + wL - 1;
                    char_n(nPosition, strCharacter);
                    // ! recursion !!!!!!!!!!!!!!!!!!!!!!
                    f = factor(nPosition, strCharacter);
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    if (strFunktionUpper == "ABS")
                        f = fabs(f);
                    else if (strFunktionUpper == "SQRT")
                        if (f >= 0)
                            f = sqrt(f);
                        else
                            wError = -1;
                    else if (strFunktionUpper == "SINH")
                        f = sinh(f);
                    else if (strFunktionUpper == "COSH")
                        f = cosh(f);
                    else if (strFunktionUpper == "TANH")
                        f = tanh(f);
                    else if (strFunktionUpper == "ARCTAN")
                        f = atan(f);
                    else if (strFunktionUpper == "LN")
                    {
                        if (f >= 0)
                            f = log(f);
                        else
                            wError = -1;
                    }
                    else if (strFunktionUpper == "LOG")
                    {
                        if (f >= 0)
                            f = log10(f);
                        else
                            wError = -1;
                    }
                    else if (strFunktionUpper == "EXP")
                    {
                        //if (f <= 41)
                            f = exp(f);
                        //else
                            //wError = -1;
                    }
                    else if (strFunktionUpper == "SIN")
                        f = sin(f);
                    else if (strFunktionUpper == "COS")
                        f = cos(f);
                    else if (strFunktionUpper == "COT")
                        f = cot(f);
                    else if (strFunktionUpper == "TAN")
                    {
                        if (cos(f) != 0)
                            f = tan(f);
                        else
                            wError = -1;
                    }
                    else if (strFunktionUpper == "ARCSIN")
                    {
                        if (fabs(f) < 1)
                            f = asin(f);
                        else
                            wError = -1;
                    }
                    else if (strFunktionUpper == "ARCCOS")
                    {
                        if (fabs(f) <= 1)
                            f = acos(f);
                        else
                            wError = -1;
                    }
                    else if (strFunktionUpper == "SIGN")
                        f = signl(f);                    
                    else if (strFunktionUpper == "RAD")
                        f = RAD(f);
                    else if (strFunktionUpper == "DEG")
                        f = DEG(f);
                    else if (strFunktionUpper == "ARSINH")
                        f = ArSinh(f);                   
                    else if (strFunktionUpper == "ARCOSH")
                    {
                        if (fabs(f) >= 1)
                            f = ArCosh(f);
                        else
                            wError = -1;
                    }
                    else if (strFunktionUpper == "ARTANH")
                    {
                        if (fabs(f) <= 1)
                            f = ArTanh(f);
                        else
                            wError = -1;
                    }
                    break;
                }
            }
            if (!gefunden)
            {
                char_n(nPosition, strCharacter);
                if (strCharacterUpper == "A")
                    f = m_dFunctionConstant[0];
                else if (strCharacterUpper == "B")
                    f = m_dFunctionConstant[1];
                else if (strCharacterUpper == "C")
                    f = m_dFunctionConstant[2];
                else if (strCharacterUpper == "D")
                    f = m_dFunctionConstant[3];
                else if (strCharacterUpper == "E")
                    f = m_dFunctionConstant[4];
                else if (strCharacterUpper == "F")
                    f = m_dFunctionConstant[5];
                else if (strCharacterUpper == "G")
                    f = m_dFunctionConstant[6];
                else if (strCharacterUpper == "H")
                    f = m_dFunctionConstant[7];
            }
        }
    }

    if (wError == -1)           errorText = QString("General Parser Error blocked!");

    return f;
}