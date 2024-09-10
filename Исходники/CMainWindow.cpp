/*!
 \brief 解压缩槽函数

 \fn CMainWindow::on_actionExtract_triggered
*/
void CMainWindow::on_actionExtract_triggered()
{
    DeletePathFile("project");
    QDir dir = QDir::current();
    dir.remove("project.tar");
    system("7z.exe x project.tar.gz -y");
    system("7z.exe x project.tar -y");
}