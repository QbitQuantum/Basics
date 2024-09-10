void FwLinePrimitive::setLine(const QLine& line)
{
    if(line != this->line())
    {
        prepareGeometryChanged();
        setPos(line.p1());

        m_p2 = line.p2() - line.p1();

        if(line.y1() == line.y2())
        {
            m_orientation = Fw::O_Horizontal;
            m_lenght = m_p2.x() - pos().x();

        }
        else if(line.x1() == line.x2())
        {
            m_orientation = Fw::O_Vertical;
            m_lenght = m_p2.y() - pos().y();
        }
        else
        {
            m_orientation = Fw::O_Diagonal;
            m_lenght = qRound(QLineF(line).length());
        }
        update();
    }
}