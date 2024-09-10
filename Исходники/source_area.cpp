//get digit number from qlineEdit
int source_area::text_from_edit(QLineEdit &ledit)
{
    bool ok=true;
    int ret=ledit.text().toInt(&ok);
    if(!ok)
    {
        ledit.setFocus();
        return -1;
    }
    return ret;
}