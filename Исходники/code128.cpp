void renderCode128(OROPage * page, const QRectF & r, const QString & _str, int align)
{
    QVector<int> str;
    int i = 0;

    // create the list.. if the list is empty then just set a start code and move on
    if (_str.isEmpty())
        str.push_back(104);
    else {
        int rank_a = 0;
        int rank_b = 0;
        int rank_c = 0;

        QChar c;
        for (i = 0; i < _str.length(); ++i) {
            c = _str.at(i);
            rank_a += (code128Index(c, SETA) != -1 ? 1 : 0);
            rank_b += (code128Index(c, SETB) != -1 ? 1 : 0);
            rank_c += (c >= '0' && c <= '9' ? 1 : 0);
        }
        if (rank_c == _str.length() && ((rank_c % 2) == 0 || rank_c > 4)) {
            // every value in the is a digit so we are going to go with mode C
            // and we have an even number or we have more than 4 values
            i = 0;
            if ((rank_c % 2) == 1) {
                str.push_back(104); // START B
                c = _str.at(0);
                str.push_back(code128Index(c, SETB));
                str.push_back(99); // MODE C
                i = 1;
            } else
                str.push_back(105); // START C

            for (i = i; i < _str.length(); i += 2) {
                char a, b;
                c = _str.at(i);
                a = c.toLatin1();
                a -= 48;
                c = _str.at(i + 1);
                b = c.toLatin1();
                b -= 48;
                str.push_back(int((a * 10) + b));
            }
        } else {
            // start in the mode that had the higher number of hits and then
            // just shift into the opposite mode as needed
            int set = (rank_a > rank_b ? SETA : SETB);
            str.push_back((rank_a > rank_b ? 103 : 104));
            int v = -1;
            for (i = 0; i < _str.length(); ++i) {
                c = _str.at(i);
                v = code128Index(c, set);
                if (v == -1) {
                    v = code128Index(c, (set == SETA ? SETB : SETA));
                    if (v != -1) {
                        str.push_back(98); // SHIFT
                        str.push_back(v);
                    }
                } else
                    str.push_back(v);
            }
        }
    }

    // calculate and append the checksum value to the list
    int checksum = str.at(0);
    for (i = 1; i < str.size(); ++i)
        checksum += (str.at(i) * i);
    checksum = checksum % 103;
    str.push_back(checksum);

    // lets determine some core attributes about this barcode
    qreal bar_width = 1; // the width of the base unit bar 1/100 inch

    // this is are mandatory minimum quiet zone
    qreal quiet_zone = bar_width * 10;
    if (quiet_zone < 0.1)
        quiet_zone = 0.1;

    // what kind of area do we have to work with
    qreal draw_width = r.width();
    qreal draw_height = r.height();

    // how long is the value we need to encode?
    int val_length = str.size() - 2; // we include start and checksum in are list so
    // subtract them out for our calculations

    // L = (11C + 35)X
    // L length of barcode (excluding quite zone) in units same as X and I
    // C the number of characters in the value excluding the start/stop and checksum characters
    // X the width of a bar (pixels in our case)
    qreal L;

    qreal C = val_length;
    qreal X = bar_width;

    L = (((11.0 * C) + 35.0) * X);

    // now we have the actual width the barcode will be so can determine the actual
    // size of the quiet zone (we assume we center the barcode in the given area
    // what should we do if the area is too small????
    // At the moment the way the code is written is we will always start at the minimum
    // required quiet zone if we don't have enough space.... I guess we'll just have over-run
    // to the right
    //
    // calculate the starting position based on the alignment option
    // for left align we don't need to do anything as the values are already setup for it
    if (align == 1) { // center
        qreal nqz = (draw_width - L) / 2.0;
        if (nqz > quiet_zone)
            quiet_zone = nqz;
    } else if (align > 1) // right
        quiet_zone = draw_width - (L + quiet_zone);
    // else if(align < 1) {} // left : do nothing

    qreal pos = r.left() + quiet_zone;
    qreal top = r.top();

    QPen pen(Qt::NoPen);
    QBrush brush(QColor("black"));

    bool space = false;
    int idx = 0, b = 0;
    qreal w = 0.0;
    for (i = 0; i < str.size(); ++i) {
        // loop through each value and render the barcode
        idx = str.at(i);
        if (idx < 0 || idx > 105) {
            qDebug("Encountered a non-compliant element while rendering a 3of9 barcode -- skipping");
            continue;
        }
        space = false;
        for (b = 0; b < 6; ++b, space = !space) {
            w = _128codes[idx].values[b] * bar_width;
            if (!space) {
                ORORect * rect = new ORORect();
                rect->setPen(pen);
                rect->setBrush(brush);
                rect->setRect(QRectF(pos, top, w, draw_height));
                page->addPrimitive(rect);
            }
            pos += w;
        }
    }

    // we have to do the stop character separately like this because it has
    // 7 elements in it's bar sequence rather than 6 like the others
    int STOP_CHARACTER[] = { 2, 3, 3, 1, 1, 1, 2 };
    space = false;
    for (b = 0; b < 7; ++b, space = !space) {
        w = STOP_CHARACTER[b] * bar_width;
        if (!space) {
            ORORect * rect = new ORORect();
            rect->setPen(pen);
            rect->setBrush(brush);
            rect->setRect(QRectF(pos, top, w, draw_height));
            page->addPrimitive(rect);
        }
        pos += w;
    }
}