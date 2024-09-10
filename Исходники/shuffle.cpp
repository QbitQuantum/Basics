void TShuffle::parse(QDomElement metadata)
{
    QDomNodeList childs = metadata.childNodes();
    QDomElement  element;
    int          length = childs.length();
    for (int i = 0; i < length; i++)
    {
        element = childs.item(i).toElement();
        if (element.tagName() == "meta" && element.hasAttribute("name") && element.hasAttribute("content"))
        {
            if (element.attribute("name") == "adapi:pickingAlgorithm")
                pickingAlgorithm = element.attribute("content");
            else if (element.attribute("name") == "adapi:pickingBehavior")
                pickingBehavior = element.attribute("content");
            else if (element.attribute("name") == "adapi:pickNumber")
                pickNumber = element.attribute("content").toInt();
            internal_pick = pickNumber;
            randomizePlaylist();
        }
    }
    return;
}