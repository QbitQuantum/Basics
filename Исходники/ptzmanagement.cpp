Nodes *PtzManagement::getNodes()
{
    Nodes *nodes = NULL;
    Message *msg = newMessage();
    QDomElement getNodes = newElement("wsdl:GetNodes");
    msg->appendToBody(getNodes);
    MessageParser *result = sendMessage(msg);
    if(result != NULL){
        nodes = new Nodes();
        QXmlQuery *query = result->query();
        QXmlResultItems items;
        QXmlItem item;
        QDomDocument doc;
        QDomNodeList itemNodeList;
        QDomNode node;
        QString value,xml;
        query->setQuery(result->nameSpace()+"doc($inputDocument)//tptz:PTZNode");
        query->evaluateTo(&items);
        item = items.next();
        while(!item.isNull()){
            query->setFocus(item);
            query->setQuery(result->nameSpace()+".");
            query->evaluateTo(&xml);
            doc.setContent(xml);
            itemNodeList = doc.elementsByTagName("tptz:PTZNode");
            for(int i=0; i<itemNodeList.size();i++)
            {
                node = itemNodeList.at(i);
                value = node.toElement().attribute("token");
                nodes->setPtzNodeToken(value.trimmed());
            }
            query->setQuery(result->nameSpace()+"./tt:Name/string()");
            query->evaluateTo(&value);
            nodes->setName(value.trimmed());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:AbsolutePanTiltPositionSpace/tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setAppsUri(value.trimmed());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:AbsolutePanTiltPositionSpace/tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setAppsXRangeMin(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:AbsolutePanTiltPositionSpace/tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setAppsXRangeMax(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:AbsolutePanTiltPositionSpace/tt:YRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setAppsYRangeMin(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:AbsolutePanTiltPositionSpace/tt:YRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setAppsYRangeMax(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:AbsoluteZoomPositionSpace/tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setAzpsUri(value.trimmed());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:AbsoluteZoomPositionSpace/tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setAzpsXRangeMin(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:AbsoluteZoomPositionSpace/tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setAzpsXRangeMax(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:RelativePanTiltTranslationSpace/tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setRptsUri(value.trimmed());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:RelativePanTiltTranslationSpace/tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setRptsXRangeMin(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:RelativePanTiltTranslationSpace/tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setRptsXRangeMax(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:RelativePanTiltTranslationSpace/tt:YRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setRptsYRangeMin(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:RelativePanTiltTranslationSpace/tt:YRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setRptsYRangeMax(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:RelativeZoomTranslationSpace/tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setRztsUri(value.trimmed());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:RelativeZoomTranslationSpace/tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setRztsXRangeMin(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:RelativeZoomTranslationSpace/tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setRztsXRangeMax(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:ContinuousPanTiltVelocitySpace/tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setCpvsUri(value.trimmed());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:ContinuousPanTiltVelocitySpace/tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setCpvsXRangeMin(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:ContinuousPanTiltVelocitySpace/tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setCpvsXRangeMax(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:ContinuousPanTiltVelocitySpace/tt:YRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setCpvsYRangeMin(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:ContinuousPanTiltVelocitySpace/tt:YRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setCpvsYRangeMax(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:ContinuousZoomVelocitySpace/tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setCzvsUri(value.trimmed());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:ContinuousZoomVelocitySpace/tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setCzvsXRangeMin(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:ContinuousZoomVelocitySpace/tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setCzvsXRangeMax(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:PanTiltSpeedSpace/tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setPssUri(value.trimmed());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:PanTiltSpeedSpace/tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setPssXRangeMin(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:PanTiltSpeedSpace/tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setPssXRangeMax(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:ZoomSpeedSpace/tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setZssUri(value.trimmed());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:ZoomSpeedSpace/tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setZssXRangeMin(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:SupportedPTZSpaces/tt:ZoomSpeedSpace/tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setZssXRangeMax(value.trimmed().toFloat());

            query->setQuery(result->nameSpace()+"./tt:MaximumNumberOfPresets/string()");
            query->evaluateTo(&value);
            nodes->setMaximumNumberOfPresets(value.trimmed().toInt());

            query->setQuery(result->nameSpace()+"./tt:HomeSupported/string()");
            query->evaluateTo(&value);
            nodes->setHomeSupported(value.trimmed() == "true"?true:false);
            item = items.next();
        }
    }
    delete msg;
    delete result;
    return nodes;
}