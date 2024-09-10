void vfo::mousePressEvent(QMouseEvent *event)
{
    bool isVFOa = false;
    int digit, cnt;
    QString myStr = "";
    long long freq;

    if (event->button() == Qt::RightButton) {

//qDebug()<<Q_FUNC_INFO<<": event x/y = "<<event->x()<<"/"<<event->y();

        //Check to see if we have right clicked on the band button group
        if ((event->x() > 414) && (event->x() < 573) &&
            (event->y() > 6) && (event->y() < 111)) {
//            storeVFO(); //make the selected button flash yellow & call store routine
            timer.start(500,this);
            ui->btnGrpBand->checkedButton()->setStyleSheet("background-color: yellow");
            emit rightBandClick();  //connected to Band:quickMemStore via UI:quickMemStore

        }   // Check to see if we have right clicked the RIT slider
        else if ((event->x() > 189) && (event->x() < 403) &&
                 (event->y() > 89) && (event->y() < 111)) {
                ui->hSlider->setValue(0);
        }
        // We have clicked either on the display or somewhere else on the widget

        else {  // Check to see if we have clicked outside the vfo display area
            digit = getDigit(event->x(), event->y());
//qDebug()<<Q_FUNC_INFO<<": The value of digit is ..."<<digit;
            if (digit != 9) {       // getDigit returns 9 if click was outside display area.
                if (digit < 9) {    // getDigit returns 0 ... 8 if we clicked on vfoA
                    freq = readA();
                    isVFOa = true;
                    myStr = ui->lbl_Amhz->text() + ui->lbl_Akhz->text() + ui->lbl_Ahz->text();
                }
                else {                  // getDigit returns 10 ... 18 if we clicked on vfoB
                    digit = digit - 10; // so convert to 1 ... 8.
                    freq = readB();
                    myStr = ui->lbl_Bmhz->text() + ui->lbl_Bkhz->text() + ui->lbl_Bhz->text();
                }
                for (cnt = myStr.length(); cnt < 9; cnt++) {
                    myStr = "0" + myStr;
                }
                for (cnt = digit; cnt < 9; cnt++) {
                    myStr[cnt] = QChar('0');
                    ui->hSlider->setValue(0);
                }
                freq = freq - myStr.toLongLong();
                if (isVFOa) {   //We right clicked on vfoA
                    if(selectedVFO == 'A' || selectedVFO == 'S') {
                        emit frequencyMoved(freq, 1);
//qDebug()<<Q_FUNC_INFO<<": vfoA, emit frequencyChanged(myStr.toLongLong()) = "<<freq;
                    }
                    else {
                        writeA(myStr.toLongLong());
//qDebug()<<Q_FUNC_INFO<<": vfoA, writeA(myStr.toInt()) = "<<freq;
                    }
                }
//                else if(ui->pBtnSubRx->isChecked()) { //We right clicked on vfoB
//qDebug()<<Q_FUNC_INFO<<": vfoB and subRx mode";
//                }
                else if(selectedVFO == 'B') {
                        emit frequencyMoved(freq, 1);
//qDebug()<<Q_FUNC_INFO<<": Line 187 ... vfoB, emit frequencyMoved(freq, 1) = "<<freq;
                }
                else {
                        writeB(myStr.toLongLong());
//qDebug()<<Q_FUNC_INFO<<": vfoB, writeA(myStr.toInt()) = "<<freq;
                }
            }
        }
    }   //If event not right button or getDigit = 9, fall thru to here with no processing.
}