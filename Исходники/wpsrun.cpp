bool WPSRun::MoveWrfOut(QString s_dir, QString& report)
{
    QDir currentDir = QDir(work_folder);
    QStringList files;
    QStringList filters;
    filters << "wrfout*";
    files = currentDir.entryList(filters,QDir::Files | QDir::NoSymLinks);
    QDir outDir = QDir(s_dir);
    if(!outDir.exists())
    {
        if(!outDir.mkdir(s_dir))
        {
            report = "Can not create directory ";
            report+=s_dir;
            return false;
        }
    }
    if(files.count() == 0)
    {
        report = "No wrfout* files in directory";
        return false;
    }
    for(int i=0;i<files.count();i++)
    {
        if(!currentDir.rename(work_folder+files[i],s_dir + files[i]))
        {
            report = "Can not move file ";
            report+=files[i];
            return false;
        }
        report.append(files[i]);
        report+="\n";
    }
    report += "moved to ";
    report += s_dir;
    return true;

}