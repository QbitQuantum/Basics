/****************************************
** Author:      Joe Li
** Purpose:     Save log data
** Comments:  
****************************************/
bool DOSaveAppData::SaveLogData(const CComBSTR& targetPath, LOG_TYPE logToSave)
{
    if (targetPath.Length() != 0)
        return SaveLog(targetPath, logToSave);

	return false;
}