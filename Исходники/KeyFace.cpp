KeyFace::KeyFace(VAC * vac, XmlStreamReader & xml) :
    Cell(vac, xml),
    KeyCell(vac, xml),
    FaceCell(vac, xml)
{
    // Cycles
    QString str;
    QStringRef d = xml.attributes().value("cycles");
    bool opened = false;
    for(int i=0; i<d.length(); ++i)
    {
        QChar c = d.at(i);
        if(c == '[')
            opened = true;
        if(opened)
            str += c;
        if(c==']')
        {
            cycles_ << Cycle();
            cycles_.last().fromString(str);
            opened = false;
            str.clear();
        }
    }
}