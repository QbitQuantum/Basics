bool SetTime::recover_system_time()
{
    backups1->wYear=setting->getValue("back1_year",2013);
    backups1->wMonth=setting->getValue("back1_mon",1);
    backups1->wDay=setting->getValue("back1_day",1);
    backups1->wHour=setting->getValue("back1_hour",0);
    backups1->wMinute=setting->getValue("back1_min",0);
    backups1->wSecond=setting->getValue("back1_second",0);
    backups2->wYear=setting->getValue("back2_year",2013);
    backups2->wMonth=setting->getValue("back2_mon",1);
    backups2->wDay=setting->getValue("back2_day",1);
    backups2->wHour=setting->getValue("back2_hour",0);
    backups2->wMinute=setting->getValue("back2_min",0);
    backups2->wSecond=setting->getValue("back2_second",0);
    qDebug()<<"back1:"<<backups1->wMonth<<backups1->wDay<<backups1->wHour<<backups1->wMinute<<backups1->wSecond;
    qDebug()<<"back2:"<<backups2->wMonth<<backups2->wDay<<backups2->wHour<<backups2->wMinute<<backups2->wSecond;
    GetSystemTime(st);
    qDebug()<<"st:"<<st->wMonth<<st->wDay<<st->wHour<<st->wMinute<<st->wSecond;
    st=time_addition(time_subduction(st,backups2),backups1);
    qDebug()<<"st:"<<st->wMonth<<st->wDay<<st->wHour<<st->wMinute<<st->wSecond;
    if(!SetSystemTime(st))
        return false;
    else
        return true;
}