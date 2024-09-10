KonqProfileDlg::KonqProfileItem::KonqProfileItem( KListWidget *parent, const QString & text )
    : QListWidgetItem( text, parent ), m_profileName( text )
{
    setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}