bool LOCACC::updateElement(QStringList newElementData, QTreeWidgetItem *currentItem)
{
    QString elementId = currentItem->text(0);
    QJsonArray jArray = m_jsonMasterObj["locAccData"].toArray();
    QString parentScreen = currentItem->parent()->text(0);
    QJsonObject tempObj ;
    for(int i = 0 ; i < jArray.count() ; i++ )
    {
        tempObj = jArray.at(i).toObject();
        if(tempObj["id"] == parentScreen)
        {
            QJsonArray eleJArray = tempObj["elements"].toArray();
            QJsonObject eleObject ;
            for(int j = 0 ; j < eleJArray.count() ; j++)
            {
                eleObject = eleJArray.at(j).toObject();
                if(eleObject["id"] == elementId)
                {
                    eleJArray.removeAt(j);
                    if(elementExistance(newElementData,eleJArray))
                    {
                        return false;
                    }
                    QJsonObject newEleJson = getElementJson(newElementData);
                    newEleJson["messages"] = eleObject["messages"];
                    eleJArray.insert(j,newEleJson);
                    tempObj["elements"] = eleJArray;
                    jArray.replace(i,tempObj);
                    break;
                }
            }
        }
    }
    m_jsonMasterObj["locAccData"] = jArray;
    currentItem->setText(0,newElementData.at(0));
    writeFile();
    return true;
}