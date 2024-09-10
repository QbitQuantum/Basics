void TMedia::setBaseParameters()
{
    cache_control = filename = log_content_id = "";
    if (root_element.hasChildNodes())
    {
        QDomNodeList childs = root_element.childNodes();
        QDomElement param;
        for (int i = 0; i < childs.length(); i++)
        {
            param = childs.item(i).toElement();
            if (param.tagName() == "param")
            {
                if (param.hasAttribute("cacheControl") && param.hasAttribute("value"))
                    cache_control = param.attribute("value");
                else if (param.hasAttribute("filename") && param.hasAttribute("value"))
                    filename = param.attribute("value");
                else if (param.hasAttribute("logContentId") && param.hasAttribute("value"))
                    log_content_id = param.attribute("value");
            }
        }

    }
}