void GraphMultiColorPainter::paint()
{

    //checkColors
    checkColors();


    QColor m_back = QColor(0,180,0,0);

    //Create a new painter
    QPainter qpN(m_widget);
    //Draw gird and BG
    drawBackground(qpN);
    drawGrid(qpN);
    //Compute size of the data and step size
    int size = m_cache.size();
    qpN.setBrush(m_back);
    qpN.drawRoundedRect(0 ,0,m_width -2 ,m_height-1,
                     3,3,Qt::AbsoluteSize);

    bool legendOnOff = (MIN_LEGEND_WIDTH * size) <= m_width;


    for(int i = 0 ; i < (size);i++)
    {
       //lets use our utils to draw the graph
       m_back = m_colors[size-i-1];
       m_back.setAlpha(80);
       painterUtils:: drawRectangleGraph(qpN,0,
                                         m_width,m_height,m_cache[size-i-1],
                                         m_colors[size-i-1],m_back);

       //paint legend
       if (legendOnOff )
       {
                QString text = QString("#") + QString::number(size-i-1);
                qpN.drawText(MIN_LEGEND_WIDTH *(size-i-1) +5,15,text);



       }
    }


}