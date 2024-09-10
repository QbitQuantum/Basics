void QuickAddCapacitorDialog::slotAttemptAutoComplete()
{
    QString text = ui->capacitanceValueLineEdit->text().trimmed();
    //We accept 3 digit value codes with an optional tolerance code
    if(text.length()==3 || text.length()==4){
        QString multiplicandStr = text.left(2);
        QChar multiplierChar = text.at(2);
        bool multiplicandOk;
        int multiplicand = multiplicandStr.toInt(&multiplicandOk);        
        if(multiplicandOk && multiplierChar.isDigit()){
            double capacitance = multiplicand * pow10(-12);
            int multiplierIdx = to_char(multiplierChar) - '0';
            if(multiplierIdx >= 0 && multiplierIdx <= 9){
                capacitance = capacitance * MULTIPLIERS[multiplierIdx];
            }
            QString capacitanceStr = UnitFormatter::format(capacitance, _capacitanceParam.unitSymbol());
            ui->capacitanceValueLineEdit->setText(capacitanceStr);
        }
        if(text.length()==4){
            QChar toleranceChar = text.at(3);
            if(toleranceChar.isLetter()){
                QString tolerance = lookupTolerance(to_char(toleranceChar));
                if(!tolerance.isEmpty()){
                    ui->toleranceLineEdit->setText(tolerance);
                }
            }
        }
    }

}