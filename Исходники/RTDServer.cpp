/******************************************************************************
*  ConnectData -- Adds new topics from a real-time data server. The ConnectData
*  method is called when a file is opened that contains real-time data
*  functions or when a user types in a new formula which contains the RTD
*  function.
*  Parameters: TopicID -- value assigned by Excel to identify the topic
*              Strings -- safe array containing the strings identifying the
*                         data to be served.
*              GetNewValues -- BOOLEAN indicating whether to retrieve new
*                              values or not.
*              pvarOut -- initial value of the topic
*  Returns: S_OK
*           E_POINTER
*           E_FAIL
******************************************************************************/
STDMETHODIMP RTDServer::ConnectData(long TopicID,
                                    SAFEARRAY **Strings,
                                    VARIANT_BOOL *GetNewValues,
                                    VARIANT *pvarOut)
{
    //Check the arguments first
    if (pvarOut == NULL) return E_POINTER;

    HRESULT hr = S_OK;

    std::stringstream topicValue;
    bool addTopic = true;

    TopicData topicData;
    topicData.name = getSafeArrayElementAsStr(Strings, 0);

    if (topicData.name != MONITOR_HEARTBEAT) {
        topicData.monitorId = getSafeArrayElementAsStr(Strings, 1);

        Monitor::RTDMonitor* monitor = getMonitor(topicData);

        if (topicData.name == MONITOR_NEW_MONITOR) {
            if (monitor != NULL) {
                monitor->newRepo("");

                delete monitor;
                this->monitors.erase(topicData.monitorId);
            }

            monitor = new Monitor::RTDMonitor;
            this->monitors.insert(Monitors::value_type(topicData.monitorId, monitor));

            addTopic = false;

            topicValue << "True";
        } else if (topicData.name == MONITOR_REMOVE_MONITOR) {
            if (monitor != NULL) {
                monitor->newRepo("");

                delete monitor;
                this->monitors.erase(topicData.monitorId);
            }
            addTopic = false;
            topicValue << "True";
        } else if (topicData.name == MONITOR_ATTACH_INFOREPO) {
            if (monitor != NULL) {
                std::string ior = getSafeArrayElementAsStr(Strings, 2);
                bool success = monitor->newRepo(ior);

                topicValue << (success ? "True" : "False");
            } else {
                topicValue << "False";
            }
            addTopic = false;
        } else if (topicData.name == MONITOR_DETACH_INFOREPO) {
            if (monitor != NULL) {
                bool success = monitor->newRepo("");

                topicValue << (success ? "True" : "False");
            } else {
                topicValue << "True";
            }

            addTopic = false;
        } else if (topicData.name == MONITOR_COLUMN_COUNT) {
            topicValue << (monitor ? monitor->getColumnCount() : 0);

        } else if (topicData.name == MONITOR_IS_NODE_VALID) {
            std::string id = getSafeArrayElementAsStr(Strings, 2);
            topicData.parameters.push_back(id);

            bool isNodeValid = (monitor ? monitor->isNodeValid(id) : false);
            topicValue << (isNodeValid ? "True" : "False");

        } else if (topicData.name == MONITOR_NODE_VALUE) {
            std::string id = getSafeArrayElementAsStr(Strings, 2);
            topicData.parameters.push_back(id);

            std::string indexStr = getSafeArrayElementAsStr(Strings, 3);
            int index = atoi(indexStr.c_str());
            topicData.parameters.push_back(indexStr);

            if (monitor == NULL) {
                topicValue << "#Error: unable to find monitor with id: " << topicData.monitorId;
            } else {
                topicValue << monitor->getNodeValue(id, index);
            }

        } else if (topicData.name == MONITOR_NODE_COLOR) {
            std::string id = getSafeArrayElementAsStr(Strings, 2);
            topicData.parameters.push_back(id);

            std::string indexStr = getSafeArrayElementAsStr(Strings, 3);
            int index = atoi(indexStr.c_str());
            topicData.parameters.push_back(indexStr);

            if (monitor != NULL) {
                topicValue << monitor->getNodeColor(id, index);
            }
        } else if (topicData.name == MONITOR_NODE_CHILDREN) {
            std::string parentId = getSafeArrayElementAsStr(Strings, 2);

            topicData.parameters.push_back(parentId);

            if (monitor == NULL) {
                topicValue << "{}";
            } else {
                topicValue << convertToDelimitedString(monitor->getNodeChildren(parentId));
            }

        } else {
            topicValue << "<unsupported request>";

            hr = E_FAIL;
        }
    }

    if (addTopic) {
        m_pTopicList.insert(TopicList::value_type(TopicID, topicData));
    }

    VariantInit(pvarOut);
    pvarOut->vt = VT_BSTR;

    std::wstring ws;
    std::string s = topicValue.str();
    ws.assign(s.begin(), s.end());

    pvarOut->bstrVal = SysAllocString(ws.c_str());

    return hr;
}