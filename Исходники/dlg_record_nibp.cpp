bool CDlgRecordNIBP::eventFilter(QObject *o,QEvent *e)
{
    QObject *obj[]={

        m_btn_back_end,
        m_btn_back_fast,
        m_btn_back,
        m_btn_forwd,
        m_btn_forwd_fast,
        m_btn_forwd_end,
        m_btn_return
    };
    int iTotalObj =  7;//11
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
                if((iCursor>=0) &&(iCursor<iTotalObj))
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
                if((iCursor>=0) &&(iCursor<iTotalObj))
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
                if((iCursor>=0) &&(iCursor<iTotalObj ))
                {
                    switch(iCursor)
                    {
                    case 0:
                        slot_back_end();
                        break;
                    case 1:
                        slot_back_fast();
                        break;

                    case 2:
                        slot_back();
                        break;
                    case 3:
                        slot_forwd();
                        break;
                    case 4:
                        slot_forwd_fast();
                        break;
                    case 5:
                        slot_forwd_end();
                        break;
                    case 6:
                        slot_return();
                        break;
                    default:
                        break;
                    }
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