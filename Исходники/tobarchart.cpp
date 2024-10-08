void toBarChart::paintChart(QPainter *p, QRect &rect)
{
    QFontMetrics fm = p->fontMetrics();

    if (!Zooming)
    {
        if (MinAuto)
        {
            bool first = true;
            std::list<std::list<double> >::reverse_iterator i = Values.rbegin();
            if (i != Values.rend())
            {
                for (std::list<double>::iterator j = (*i).begin(); j != (*i).end(); j++)
                {
                    if (first)
                    {
                        first = false;
                        zMinValue = *j;
                    }
                    else if (zMinValue > *j)
                        zMinValue = *j;
                }
            }
        }
        if (MaxAuto)
        {
            bool first = true;
            std::list<double> total;
            std::list<bool>::iterator e = Enabled.begin();
            {
                for (std::list<std::list<double> >::iterator i = Values.begin(); i != Values.end(); i++)
                {
                    std::list<double>::iterator k = total.begin();
                    if (e == Enabled.end() || *e)
                    {
                        for (std::list<double>::iterator j = (*i).begin(); j != (*i).end(); j++)
                        {
                            if (k == total.end())
                            {
                                total.insert(total.end(), *j);
                                k = total.end();
                            }
                            else
                            {
                                *k += *j;
                                k++;
                            }
                        }
                    }
                    if (e != Enabled.end())
                        e++;
                }
            }
            for (std::list<double>::iterator i = total.begin(); i != total.end(); i++)
            {
                if (first)
                {
                    first = false;
                    zMaxValue = *i;
                }
                else if (zMaxValue < *i)
                    zMaxValue = *i;
            }
        }
        if (!MinAuto)
            zMinValue = MinValue;
        else
        {
            zMinValue = round(zMinValue, false);
            MinValue = zMinValue;
        }
        if (!MaxAuto)
            zMaxValue = MaxValue;
        else
        {
            zMaxValue = round(zMaxValue, true);
            MaxValue = zMaxValue;
        }
    }

    paintTitle(p, rect);
    paintLegend(p, rect);
    paintAxis(p, rect);

    std::list<QPolygon> Points;
    int cp = 0;
    int samples = countSamples();
    int zeroy = int(rect.height() - 2 - ( -zMinValue / (zMaxValue - zMinValue) * (rect.height() - 4)));
    if (samples > 1)
    {
        const QMatrix &mtx = p->worldMatrix();
        p->setClipRect(int(mtx.dx() + 2), int(mtx.dy() + 2), rect.width() - 3, rect.height() - 3);
        if (Zooming)
            p->drawText(2, 2, rect.width() - 4, rect.height() - 4,
                        Qt::AlignLeft | Qt::AlignTop, tr("Zoom"));
        std::list<bool>::reverse_iterator e = Enabled.rbegin();
        for (std::list<std::list<double> >::reverse_iterator i = Values.rbegin(); i != Values.rend(); i++)
        {
            if (e == Enabled.rend() || *e)
            {
                std::list<double> &val = *i;
                int count = 0;
                int skip = SkipSamples;
                QPolygon a(samples + 10);
                int x = rect.width() - 2;
                for (std::list<double>::reverse_iterator j = val.rbegin(); j != val.rend() && x >=
                        2;
                        j++)
                {
                    if (skip > 0)
                        skip--;
                    else
                    {
                        int val = int(rect.height() - 2 - ((*j - zMinValue) / (zMaxValue - zMinValue) * (rect.height() - 4)));
                        x = rect.width() - 2 - count * (rect.width() - 4) / (samples - 1);
                        a.setPoint(count, x, val);
                        count++;
                        if (count >= samples)
                            break;
                    }
                }
                a.resize(count * 2);
                Points.insert(Points.end(), a);
            }
            cp++;
            if (e != Enabled.rend())
                e++;
        }
    }

    std::map<int, int> Bottom;
    std::list<bool>::reverse_iterator e = Enabled.rbegin();
    for (std::list<QPolygon>::iterator i = Points.begin(); i != Points.end();)
    {
        while (e != Enabled.rend() && !*e)
        {
            cp--;
            e++;
        }
        if (e != Enabled.rend())
            e++;
        cp--;

        QPolygon a = *i;
        int lx = 0;
        int lb = 0;
        for (int j = 0; j < a.size() / 2; j++)
        {
            int x, y;
            a.point(j, &x, &y);
            if (Bottom.find(x) == Bottom.end())
                Bottom[x] = 0;
            if (lx != x)
                lb = Bottom[x];
            a.setPoint(a.size() - 1 - j, x, zeroy - lb);
            y -= lb;
            a.setPoint(j, x, y);
            Bottom[x] = zeroy - y;
            lx = x;
        }

        p->save();
        QBrush brush(Utils::toChartBrush(cp));
        p->setBrush(brush.color());
        p->drawPolygon(a);
        if (brush.style() != Qt::SolidPattern)
        {
            p->setBrush(QBrush(Qt::white, brush.style()));
            p->drawPolygon(a);
        }
        p->restore();
        i++;
    }
}