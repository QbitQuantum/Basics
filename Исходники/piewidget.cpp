void PieWidget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    QRectF rectf(0,0,diameter,diameter);
    int allcount = 0;
    for(int i = 0; i < STATENUM; i++)
    {
        allcount+=statecounts[i];
    }
    int startangle = 0;
    int spanangle = 0;
    if(allcount != 0)
    {
        for(int i = 0; i < STATENUM; i++)
        {
            startangle = startangle + spanangle;
            spanangle = 360*16*statecounts[i]/float(allcount);
            painter.setBrush(QBrush(statecolors[i]));
            painter.drawPie(rectf,startangle,spanangle);
        }
        /*QPen pen;
        pen.setColor(Qt::blue);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawEllipse(1,1,diameter - 2,diameter - 2);*/

    }
    else
    {
        painter.setBrush(QBrush(Qt::Dense4Pattern));
        painter.drawEllipse(rectf);
        /*QPen pen;
        pen.setColor(Qt::blue);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawEllipse(1,1,diameter - 2,diameter - 2);*/
    }
    if(isparent)
    {
        int ystart = (diameter - STATENUM*STATEHINTHEIGHT - (STATENUM - 1)*STATEHINTVERSPACE)/2;
        for(int i = 0; i < STATENUM; i++)
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QBrush(statecolors[i]));
            painter.drawRect(diameter+HORIZONSPACE,ystart+(STATEHINTHEIGHT+STATEHINTVERSPACE)*i,STATEHINTHEIGHT,STATEHINTHEIGHT);
            painter.setBrush(Qt::NoBrush);
            painter.setPen(Qt::SolidLine);
            QRectF textrectf(diameter+HORIZONSPACE + STATEHINTHEIGHT + 10,ystart+(STATEHINTHEIGHT+STATEHINTVERSPACE)*i,100,STATEHINTHEIGHT);
            if(allcount != 0)
                painter.drawText(textrectf,Qt::AlignLeft|Qt::AlignVCenter,statename.at(i) + QString::number(statecounts[i]/float(allcount)*100,'f',1) + "%(" +QString::number(statecounts[i])+")");
            else
                painter.drawText(textrectf,Qt::AlignLeft|Qt::AlignVCenter,statename.at(i) + "0.0%(0)");
            painter.drawText(diameter+HORIZONSPACE + STATEHINTHEIGHT + 10,ystart+(STATEHINTHEIGHT+STATEHINTVERSPACE)*STATENUM,100,STATEHINTHEIGHT,Qt::AlignLeft|Qt::AlignLeft,name);
        }
    }
    else
    {
        int ystart = diameter + VERTICALSPACE;
        for(int i = 0; i < STATENUM; i++)
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QBrush(statecolors[i]));
            //painter.drawRect(diameter/4,ystart+(STATEHINTHEIGHT+STATEHINTVERSPACE)*i,STATEHINTHEIGHT,STATEHINTHEIGHT);
            painter.drawRect(0,ystart+(STATEHINTHEIGHT+STATEHINTVERSPACE)*i,STATEHINTHEIGHT,STATEHINTHEIGHT);
            painter.setBrush(Qt::NoBrush);
            painter.setPen(Qt::SolidLine);
           // QRectF textrectf(diameter/4 + STATEHINTHEIGHT + 10,ystart+(STATEHINTHEIGHT+STATEHINTVERSPACE)*i,100,STATEHINTHEIGHT);
            QRectF textrectf(0 + STATEHINTHEIGHT + 10,ystart+(STATEHINTHEIGHT+STATEHINTVERSPACE)*i,100,STATEHINTHEIGHT);
            if(allcount != 0)
                painter.drawText(textrectf,Qt::AlignLeft|Qt::AlignVCenter,/*statename.at(i) +*/QString::number(statecounts[i]/float(allcount)*100,'f',1) + "%(" +QString::number(statecounts[i])+")");
            else
                painter.drawText(textrectf,Qt::AlignLeft|Qt::AlignVCenter,/*statename.at(i) +*/"0.0%(0)");
        }
        /*namelabel->setFixedHeight(STATEHINTHEIGHT);
        namelabel->setAlignment(Qt::AlignCenter);
        namelabel->setText(name);
        namelabel->move(0,ystart+(STATEHINTHEIGHT+STATEHINTVERSPACE)*STATENUM);*/
        painter.drawText(0,ystart+(STATEHINTHEIGHT+STATEHINTVERSPACE)*STATENUM - STATEHINTVERSPACE ,diameter,STATEHINTHEIGHT,Qt::AlignCenter,name);

    }
}