    //
    // Процедура обрабатывает нажатие кнопки "Откл.(0)".
    //
void Window::bn_switch_off_Clicked()
{
 int key = h_ListItem2index[m_SelectedItem];
 struct s_sdb_recode *sdb = hash_sdb_recode[key];
 int port =  sdb->O_PORT_ADAM;
 int addr =  sdb->O_ADR_ADAM;
 int nr  =  sdb->O_NR_ADAM;

 qDebug() << "Откл.(0)  " << m_SelectedItem->text()
          << "    ADAM PORT=" << port
          <<           "ADR=" << addr
          <<            "NR="   << nr;
 int state=WritePort( port, addr, nr, 0 );
 if ( state!=0) {
   qDebug() << "Bad";
   messbox("Ошибка записи");
   lwg->setFocus( Qt::TabFocusReason );   // Установить фокус на список.
   return;
}
 else         qDebug() << "Ok";
 lwg->setFocus( Qt::TabFocusReason );   // Установить фокус на список.

}