void cutExtension(long maxNum)
{
    QDir Dir;
    QString loc=QCoreApplication::applicationDirPath()+"/data/video/";
    for (int i=1;i!=maxNum;++i)
    {
        Dir.rename(loc+QString::number(i)+".avi",loc+QString::number(i));
        Dir.rename(loc+QString::number(i)+"~1.avi",loc+QString::number(i)+"~1");
    }
}