void EditEventValues::paintEvent(QPaintEvent *)
{
    mPainter = new QPainter(this);
    mPen = new QPen(Qt::black);
    mBrush = new QBrush(Qt::lightGray, Qt::SolidPattern);
    mFont.setPointSize(6);
    mPainter->setPen(*mPen);
    mPainter->setBrush(*mBrush);
    mPainter->setFont(mFont);

    //this is perhaps the background?

    long tick;

    unsigned char d0,d1;

    int event_x;
    int event_height;

    bool selected;

    int start_tick = 0 ;
    int end_tick = (width() * m_zoom);

    mPainter->drawRect(0,
                       0,
                       width() - 1,
                       height() - 1);

    m_seq->reset_draw_marker();
    while ( m_seq->get_next_event( m_status,
                                   m_cc,
                                   &tick, &d0, &d1,
                                   &selected ) == true )
    {

        if ( tick >= start_tick && tick <= end_tick )
        {

            /* turn into screen corrids */

            event_x = tick / m_zoom + c_keyboard_padding_x;

            /* generate the value */
            event_height = d1;

            if ( m_status == EVENT_PROGRAM_CHANGE ||
                 m_status == EVENT_CHANNEL_PRESSURE  ){

                event_height = d0;
            }

            /* draw vert lines */
            mPen->setWidth(2);
            mPainter->setPen(*mPen);
            mPainter->drawLine(event_x + 1,
                               height() - event_height,
                               event_x + 1,
                               height());

            //draw numbers
            QString val = QString::number(d1);

            mPen->setColor(Qt::black);
            mPen->setWidth(1);
            mPainter->setPen(*mPen);
            if (val.length() >= 1)
                mPainter->drawText(event_x + 3,
                                   c_dataarea_y - 25,
                                   val.at(0));
            if (val.length() >= 2)
                mPainter->drawText(event_x + 3,
                                   c_dataarea_y - 25 + 8,\
                                   val.at(1));
            if (val.length() >= 3)
                mPainter->drawText(event_x + 3,
                                   c_dataarea_y - 25 + 16,
                                   val.at(2));
        }
    }

    //draw edit line

    if (mLineAdjust)
    {
        int x,y,w,h;
        mPen->setColor(Qt::black);
        mPen->setStyle(Qt::DashLine);
        mPainter->setPen(*mPen);

        xy_to_rect ( mDropX,
                     mDropY,
                     mCurrentX,
                     mCurrentY,
                     &x, &y,
                     &w, &h );

        mOld->setX(x);
        mOld->setY(y);
        mOld->setWidth(w);
        mOld->setHeight(h);

        mPainter->drawLine(mCurrentX + c_keyboard_padding_x,
                           mCurrentY,
                           mDropX + c_keyboard_padding_x,
                           mDropY );
    }

    delete mPainter;
    delete mBrush;
    delete mPen;
}