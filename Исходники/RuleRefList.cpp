void RuleRefList::fromXml(const QDomElement& ele) throw(XmlParseException)
{
    QDomNodeList list  = ele.childNodes();
    int len = list.length();
    QDomElement node;
    
    
    for(int i = 0; i < len; i++)
    {
        node = list.item(i).toElement();
        if(!node.isNull())
        {
            if(node.nodeName() == "rule_ref")
            {
                UnresolvedReference ref(node);
                m_unresolvedRules.append(ref);
            }
            else
                throw XmlParseException("invalid rule ref list node", node);
        }
    }
}