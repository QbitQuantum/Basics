void LineGraphWidget::paintEvent(QPaintEvent *)
{
    qDebug() << "akb";
    int i;
    int a,b,c,d;
    Counter = 0;
    QPixmap pix(widgetX,widgetY);

    QPainter painter(&pix);
    pix.fill(Qt::white);

    QPen pen;
    pen.setBrush(Qt::black);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);

    QPen pen1;
    pen1.setBrush(Qt::black);

    painter.setRenderHint(QPainter::Antialiasing);

    for(i = 0;i < sumUnitX+1; ++i)
    {
        a = basePoint.x + i*singleUnitX;
        b = basePoint.y;
        c = a;
        d = yAxisEndPoint.y;
        painter.drawLine(a,b,c,d);
    }

    for(i = 0; i < sumUnitY+1; ++i)
    {
        a = basePoint.x;
        b = basePoint.y - singleUnitY*i;
        c = xAxisEndPoint.x;
        d = b;
        painter.drawLine(a,b,c,d);
    }

    painter.setPen(pen1);

    for (i = 0;i <sumUnitY+1; i++)
    {
        QRectF rectF(5,basePoint.y - singleUnitY*i-10,singleUnitX+5,singleUnitY);//长宽与位数的关系 2015/06/05
        double temp = (sumUnitY > 0) ? ((static_cast<double>(rangeMax-rangeMin))/static_cast<double>(sumUnitY))*static_cast<double>(i) : 0;
        painter.drawText(rectF,Qt::AlignLeft,QString::number(static_cast<int>(temp)));
    }

    for (i = 0;i < sumUnitX+1;++i)
    {
        QRectF rectF(singleUnitX*i+35,basePoint.y+10,singleUnitX,singleUnitY);
        painter.drawText(rectF,Qt::AlignLeft,QString::number((i+this->second)%60));
    }


    for(int i = 0; i<yList.size()-1;i++)
    {
        painter.drawLine(basePoint.x+i*singleUnitX,
                         yList.at(i),
                         basePoint.x + (i + 1)*singleUnitX,
                         yList.at(i+1)
                         );
    }

    if(yList.size() > sumUnitX)
    {
        yList.removeFirst();
    }
    int temp = basePoint.y - qrand() % 150;
    yList.append(temp);

    painter.end();
    painter.begin(this);
    painter.drawPixmap(0,0,pix);
    painter.end();
    Counter = 0;

    if(this->second%60==0 && this->second > 60 )
    {
        this->second = 1;
    }
    else
    {
        this->second +=1;
    }

}