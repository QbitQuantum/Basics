void MTScaleFlo::draw(QPainter& p, const QRect& r)
{
    int x = r.x();
    int w = r.width();

    x -= 20;
    w += 40;    // wg. Text

    //---------------------------------------------------
    //    draw Marker
    //---------------------------------------------------

    int y = 12;
    p.setPen(MusEGlobal::config.rulerFg);
    p.setFont(MusEGlobal::config.fonts[5]);
    p.drawLine(r.x(), y+1, r.x() + r.width(), y+1);
    QRect tr(r);
    tr.setHeight(12);
    MusECore::MarkerList* marker = MusEGlobal::song->marker();
    for (MusECore::iMarker m = marker->begin(); m != marker->end(); ++m) {

        int xp = parent->tick_to_x(m->second.tick()) + xoffset - xpos;
        if (xp > x+w)
            break;
        int xe = r.x() + r.width();
        MusECore::iMarker mm = m;
        ++mm;
        if (mm != marker->end())
            xe = parent->tick_to_x(mm->first) + xoffset - xpos;

        QRect tr(xp, 0, xe-xp, 13);

        QRect wr = r.intersected(tr);
        if(!wr.isEmpty())
        {
            if (m->second.current())
                p.fillRect(wr, MusEGlobal::config.rulerCurrent);

            int x2;
            if (mm != marker->end())
                x2 = parent->tick_to_x(mm->first) + xoffset - xpos;
            else
                x2 = xp+200;

            if(xp >= -32)
                p.drawPixmap(xp, 0, *flagIconS);

            if(xp >= -1023)
            {
                QRect r = QRect(xp+10, 0, x2-xp, 12);
                p.setPen(MusEGlobal::config.rulerFg);
                p.drawText(r, Qt::AlignLeft|Qt::AlignVCenter, m->second.name());
            }

            if(xp >= 0)
            {
                p.setPen(Qt::green);
                p.drawLine(xp, y, xp, height());
            }
        }
    }

    //---------------------------------------------------
    //    draw location marker
    //---------------------------------------------------

    int h = height()-12;

    for (int i = 0; i < 3; ++i) {
        int xp = parent->tick_to_x(pos[i]) + xoffset - xpos;
        if (xp >= x && xp < x+w) {
            QPixmap* pm = markIcon[i];
            p.drawPixmap(xp - pm->width()/2, y-1, *pm);
        }
    }


    //---------------------------------------------------
    //    draw beats
    //---------------------------------------------------


    p.setPen(MusEGlobal::config.rulerFg);

    unsigned ctick;
    int bar1, bar2, beat;
    unsigned tick;

    ctick = parent->x_to_tick(x - xoffset + xpos);
    AL::sigmap.tickValues(ctick, &bar1, &beat, &tick);
    AL::sigmap.tickValues(parent->x_to_tick(x+w - xoffset + xpos), &bar2, &beat, &tick);


    int stick = AL::sigmap.bar2tick(bar1, 0, 0);
    int ntick;
    for (int bar = bar1; bar <= bar2; bar++, stick = ntick) {
        ntick     = AL::sigmap.bar2tick(bar+1, 0, 0);
        int tpix = parent->delta_tick_to_delta_x(ntick - stick);
        if (tpix < 64) {
            // donï¿½t show beats if measure is this small
            int n = 1;
            if (tpix < 32)
                n = 2;
            if (tpix <= 16)
                n = 4;
            if (tpix < 8)
                n = 8;
            if (tpix <= 4)
                n = 16;
            if (tpix <= 2)
                n = 32;
            if (bar % n)
                continue;
            p.setFont(MusEGlobal::config.fonts[3]);
            int x = parent->tick_to_x(stick) + xoffset - xpos;
            QString s;
            s.setNum(bar + 1);
            p.drawLine(x, y+1, x, y+1+h);
//                  QRect r = QRect(x+2, y, 0, h);
            QRect r = QRect(x+2, y, 1000, h);
            p.drawText(r, Qt::AlignLeft|Qt::AlignVCenter|Qt::TextDontClip, s);
        }
        else {
            int z, n;
            AL::sigmap.timesig(stick, z, n);
            for (int beat = 0; beat < z; beat++) {
                int xp = parent->tick_to_x(AL::sigmap.bar2tick(bar, beat, 0)) + xoffset - xpos;
                QString s;
                QRect r(xp+2, y, 1000, h);
                int y1;
                int num;
                if (beat == 0) {
                    num = bar + 1;
                    y1  = y + 1;
                    p.setFont(MusEGlobal::config.fonts[3]);
                }
                else {
                    num = beat + 1;
                    y1  = y + 7;
                    p.setFont(MusEGlobal::config.fonts[4]);
                    r.setY(y+3);
                }
                s.setNum(num);
                p.drawLine(xp, y1, xp, y+1+h);
                p.drawText(r, Qt::AlignLeft|Qt::AlignVCenter|Qt::TextDontClip, s);
            }
        }
    }
}