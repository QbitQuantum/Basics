/*! \brief Called when a connection has been performed
    \param which
*/
void ApplicationViewWidget::onConConnect(int which)
{
    QTreeWidgetItem *it = ui->connectionList->topLevelItem(which);
    if(it){
        it->setText(2,"connected");
        it->setIcon(0,QIcon(":/images/connected_ico.png"));
        it->setTextColor(2,QColor("#008C00"));
    }

           /* row[m_conColumns.m_col_status] = "connected";
            row[m_conColumns.m_col_editable] = false;
            row[m_conColumns.m_col_color] = Gdk::Color("#008C00");
            row.set_value(0, m_refPixConnected);*/

        reportErrors();

}