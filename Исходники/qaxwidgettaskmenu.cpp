void QAxWidgetTaskMenu::setActiveXControl()
{
    QAxSelect *dialog = new QAxSelect(m_axwidget->topLevelWidget());
    if (dialog->exec())    {
        QUuid clsid = dialog->clsid();
        QString key;

        IClassFactory2 *cf2 = 0;
        CoGetClassObject(clsid, CLSCTX_SERVER, 0, IID_IClassFactory2, (void**)&cf2);

        if (cf2)  {
            BSTR bKey;
            HRESULT hres = cf2->RequestLicKey(0, &bKey);
            if (hres == CLASS_E_NOTLICENSED) {
                QMessageBox::warning(m_axwidget->topLevelWidget(), tr("Licensed Control"),
                                     tr("The control requires a design-time license"));
                clsid = QUuid();
            } else {
                key = QString::fromWCharArray(bKey);
            }

            cf2->Release();
        }

        if (!clsid.isNull())  {
            QDesignerFormWindowInterface *formWin = QDesignerFormWindowInterface::findFormWindow(m_axwidget);

            Q_ASSERT(formWin != 0);
            QString value = clsid.toString();
            if (!key.isEmpty()) {
                value += QLatin1Char(':');
                value += key;
            }
            formWin->commandHistory()->push(new SetControlCommand(m_axwidget, formWin, value));
        }
    }
    delete dialog;
}