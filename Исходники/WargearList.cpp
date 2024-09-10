void WargearList::fromXml(const QDomElement& ele) throw(XmlParseException)
{
    QDomNodeList list = ele.childNodes();
    int len = list.length();
    QDomElement current;
    
    for(int i = 0; i < len; i++)
    {
        current = list.item(i).toElement();
        if(!current.isNull())
        {
            if(current.nodeName() == "wargear")
            {
                Wargear wg(current, race());
                m_wargears.insert(wg.id(), wg);
            }
            else
                throw XmlParseException("invalid wargear list node", current);
        }
    }
}