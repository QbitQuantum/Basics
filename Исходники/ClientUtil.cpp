CString getLabelStringFromID(int id) {

    CString sourceName("");
    int labelStringID = -1;
    switch (id) {
        case SYNCSOURCE_CONTACTS:
        {
            labelStringID        = IDS_MAIN_CONTACTS;
            break;
        }
        case SYNCSOURCE_CALENDAR:
        {
            labelStringID        = IDS_MAIN_CALENDAR;
            break;
        }
        case SYNCSOURCE_TASKS:
        {
            labelStringID        = IDS_MAIN_TASKS;
            break;
        }
        case SYNCSOURCE_NOTES:
        {
            labelStringID        = IDS_MAIN_NOTES;
            break;
        }
        case SYNCSOURCE_PICTURES:
        {
            labelStringID        = IDS_MAIN_PICTURES;
            break;
        }
        case SYNCSOURCE_VIDEOS:
        {
            labelStringID        = IDS_MAIN_VIDEOS;
            break;
        }
        case SYNCSOURCE_FILES:
        {
            labelStringID        = IDS_MAIN_FILES;
            break;
        }
        default:
        {
            StringBuffer msg;
            msg.sprintf("[%s] wrong id: %d", __FUNCTION__, id);
            printLog(msg.c_str(), "ERROR");
            return sourceName;
        }
    }

    sourceName.LoadString(labelStringID); 
    return sourceName;
}