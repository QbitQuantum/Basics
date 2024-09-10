void KeyBoardPreview::paintEvent(QPaintEvent* event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.setBrush(QColor(0xd6, 0xd6, 0xd6));
    p.drawRect(rect());

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(0x58, 0x58, 0x58));
    p.setPen(pen);

    p.setBrush(QColor(0x58, 0x58, 0x58));

    p.setBackgroundMode(Qt::TransparentMode);
    p.translate(0.5, 0.5);

    int rx = 3;
    int x=6;
    int y=6;
    int first_key_w = 0;
    int remaining_x[] = {0,0,0,0};
    int remaining_widths[] = {0,0,0,0};

    for (int i = 0; i < 4; i++) {
        if (first_key_w > 0) {
            first_key_w = first_key_w*1.375;

            if (kb == &kbList[KB_105] && i == 3)
                first_key_w = key_w * 1.275;

            p.drawRoundedRect(QRectF(6, y, first_key_w, key_w), rx, rx);
            x = 6 + first_key_w + space;
        }
        else {
            first_key_w = key_w;
        }



        bool last_end = (i==1 && ! kb->kb_extended_return);
        int rw=usable_width-x;
        int ii=0;

        for (int k : kb->keys.at(i)) {
            QRectF rect = QRectF(x, y, key_w, key_w);

            if (ii == kb->keys.at(i).size()-1 && last_end)
                rect.setWidth(rw);

            p.drawRoundedRect(rect, rx, rx);

            rect.adjust(5, 1, 0, 0);

            p.setPen(QColor(0x9e, 0xde, 0x00));
            p.setFont(upperFont);
            p.drawText(rect, Qt::AlignLeft | Qt::AlignTop, shift_text(k));

            rect.setBottom(rect.bottom() - 2.5);

            p.setPen(QColor(0xff, 0xff, 0xff));
            p.setFont(lowerFont);
            p.drawText(rect, Qt::AlignLeft | Qt::AlignBottom, regular_text(k));

            rw = rw - space - key_w;
            x = x + space + key_w;
            ii = ii+1;

            p.setPen(pen);
        }



        remaining_x[i] = x;
        remaining_widths[i] = rw;

        if (i != 1 && i != 2)
            p.drawRoundedRect(QRectF(x, y, rw, key_w), rx, rx);

        y = y + space + key_w;
    }


    if (kb->kb_extended_return) {
        rx=rx*2;
        int x1 = remaining_x[1];
        int y1 = 6 + key_w*1 + space*1;
        int w1 = remaining_widths[1];
        int x2 = remaining_x[2];
        int y2 = 6 + key_w*2 + space*2;

        // this is some serious crap... but it has to be so
        // maybe one day keyboards won't look like this...
        // one can only hope
        QPainterPath pp;
        pp.moveTo(x1, y1+rx);
        pp.arcTo(x1, y1, rx, rx, 180, -90);
        pp.lineTo(x1+w1-rx, y1);
        pp.arcTo(x1+w1-rx, y1, rx, rx, 90, -90);
        pp.lineTo(x1+w1, y2+key_w-rx);
        pp.arcTo(x1+w1-rx, y2+key_w-rx, rx, rx, 0, -90);
        pp.lineTo(x2+rx, y2+key_w);
        pp.arcTo(x2, y2+key_w-rx, rx, rx, -90, -90);
        pp.lineTo(x2, y1+key_w);
        pp.lineTo(x1+rx, y1+key_w);
        pp.arcTo(x1, y1+key_w-rx, rx, rx, -90, -90);
        pp.closeSubpath();

        p.drawPath(pp);
    }
    else {
        x= remaining_x[2];
        y = 6 + key_w*2 + space*2;
        p.drawRoundedRect(QRectF(x, y, remaining_widths[2], key_w), rx, rx);
    }


    QWidget::paintEvent(event);
}