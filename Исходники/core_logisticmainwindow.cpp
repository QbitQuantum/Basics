void CLogisticMainWindow::slotCustomerDictionary()
{
    QMdiSubWindow *msw = findMdiWindow("Заказчики");
    if (!msw){
         showMdiWindow(CLogisticApplication::instance()->createCustomer(),
                       "Заказчики",
                       QIcon(QString("data/picture/sidebar/customer.ico")));
    } else {
         msw->setFocus();
    }
}