bool CDlgSetMashen::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={
         m_cmbb_ap
        ,m_cmbb_speed
        ,m_btn_ok
        ,m_btn_cancel
    };
    int iTotalObj =  4;//11
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
            {
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
            {

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
            {
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