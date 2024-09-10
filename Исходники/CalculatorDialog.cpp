void CalculatorDialog::expressionChanged(bool validExpression, bool validPointer, int_t value)
{
    if(!validExpression)
    {
        ui->txtBin->setText("");
        ui->txtSignedDec->setText("");
        ui->txtUnsignedDec->setText("");
        ui->txtHex->setText("");
        ui->txtOct->setText("");
        ui->txtAscii->setText("");
        ui->txtUnicode->setText("");
        ui->txtExpression->setStyleSheet("border: 2px solid red");
        emit validAddress(false);
    }
    else
    {
        ui->txtExpression->setStyleSheet("");
        ui->txtHex->setText(inFormat(value, N_HEX));
        ui->txtSignedDec->setText(inFormat(value, N_SDEC));
        ui->txtUnsignedDec->setText(inFormat(value, N_UDEC));
        int cursorpos = ui->txtBin->cursorPosition();
        ui->txtBin->setText(inFormat(value, N_BIN));
        ui->txtBin->setCursorPosition(cursorpos);
        ui->txtOct->setText(inFormat(value, N_OCT));
        if((value == (value & 0xFF)))
        {
            QChar c = QChar::fromLatin1((char)value);
            if(c.isPrint())
                ui->txtAscii->setText("'" + QString(c) + "'");
            else
                ui->txtAscii->setText("???");
        }
        else
            ui->txtAscii->setText("???");
        ui->txtAscii->setCursorPosition(1);
        if((value == (value & 0xFFF)))  //UNICODE?
        {
            QChar c = QChar::fromLatin1((wchar_t)value);
            if(c.isPrint())
                ui->txtUnicode->setText("L'" + QString(c) + "'");
            else
                ui->txtUnicode->setText("????");
        }
        else
        {
            ui->txtUnicode->setText("????");
        }
        ui->txtUnicode->setCursorPosition(2);
        emit validAddress(validPointer);
    }
}