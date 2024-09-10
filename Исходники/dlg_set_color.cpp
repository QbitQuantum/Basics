bool CDlgSetColor::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
        m_cmbb_beat_rate
        ,m_cmbb_spo2
        ,m_cmbb_spire_rate
        ,m_cmbb_temp
        ,m_cmbb_nibp
        ,m_cmbb_mashen
        ,m_cmbb_ibp1
        ,m_cmbb_ibp2
        ,m_cmbb_co2
        ,m_cmbb_wav_eeg
        ,m_cmbb_wav_ecg1
        ,m_cmbb_wav_ecg2
        ,m_cmbb_wav_ecg3
        ,m_cmbb_wav_ecg4
        ,m_cmbb_wav_ecg5
        ,m_cmbb_wav_ecg6
        ,m_cmbb_wav_ecg7
        ,m_cmbb_wav_pulse
        ,m_cmbb_wav_spr
        ,m_cmbb_wav_ibp1
        ,m_cmbb_wav_ibp2
        ,m_cmbb_wav_co2
        ,m_cmbb_wav_mashen
        ,m_btn_ok
        ,m_btn_cancel
    };
    int iTotalObj =  25;//
    int iOkPos = iTotalObj -2;
    int iCancelPos = iTotalObj -1;
    if(e->type() == QEvent::KeyPress)
    {

        QKeyEvent *event=(QKeyEvent *)e;
        switch (event->key()) {
        case Qt::Key_Up:
        case Qt::Key_Left:
            if(bCursorSta == false)
            {
                if(iCursor == 0)
                {
                    iCursor = iTotalObj-1;
                }
                else
                {
                    iCursor -=1;
                }
                if((iCursor>=0) &&(iCursor<iOkPos))
                {
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->setFocus();
                }
                else
                {
                    QPushButton *p = (QPushButton *)obj[iCursor];
                    p->setFocus();
                }

            }
            else
            {/*

                if((iCursor >= 7)&&(iCursor <=10))
                {
                    QSpinBox *p = (QSpinBox *)obj[iCursor];
                    if(p->value()!= p->minimum())
                    {
                        p->setValue(p->value()-1);
                    }
                    else
                    {
                        p->setValue(p->maximum());
                    }

                }*/
            }

            return true;
            break;
        case Qt::Key_Down:
        case Qt::Key_Right:
            if(bCursorSta == false)
            {
                if(iCursor == iTotalObj-1)
                {
                    iCursor = 0;
                }
                else
                {
                    iCursor +=1;
                }
                if((iCursor>=0) &&(iCursor<iOkPos))
                {
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->setFocus();
                }

                else
                {
                    QPushButton *p = (QPushButton *)obj[iCursor];
                    p->setFocus();
                }

            }
            else
            {/*
                if((iCursor >= 7)&&(iCursor <=10))
                {
                    QSpinBox *p = (QSpinBox *)obj[iCursor];
                    if(p->value()!= p->maximum())
                    {
                        p->setValue(p->value()+1);
                    }
                    else
                    {
                        p->setValue(p->minimum());
                    }

                }*/

            }
            return true;
            break;
        case Qt::Key_Return:
            if(bCursorSta == false)
            {
                if(iCursor == iOkPos)
                {
                    do_ok_clicked();
                }
                else if(iCursor == iCancelPos)
                {
                    do_cancel_clicked();
                }
                else if((iCursor>=0) &&(iCursor<iOkPos))
                {
                    //btn[iCursor]->showPopup();

                    bCursorSta = false;
                    QComboBox *p = (QComboBox *)obj[iCursor];
                    p->showPopup();
                    //p->setStyleSheet("background-color: rgb(35, 53, 234,255);");
                }


            }
            else
            {/*
                bCursorSta = false;
                if((iCursor >= 7)&&(iCursor <=10))
                {

                    QSpinBox *p = (QSpinBox *)obj[iCursor];
                    //p->setStyleSheet("background-color: rgb(255, 255, 255);");;
                }
                //obj[iCursor]->setStyleSheet("background-color: rgb(255, 255, 255);");
*/
            }
            return true;
            break;
        default:
            CMainForm *p = (CMainForm *)pMainForm;
            p->f_process_key(event->key());
            return true;
            break;

        }
    }
    else
    {
        return false;
    }
}