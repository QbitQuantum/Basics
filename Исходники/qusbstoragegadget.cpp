/*!
    \reimp
*/
void QUsbStorageGadgetProvider::activate()
{
    if (!value("active", false).toBool()) {
        if (!d->manager)
            d->manager = new QUsbManager;

        if (d->manager->canActivate(GADGET_NAME)) {
            loadModule();
        } else {
            connect(d->manager, SIGNAL(deactivateCompleted()), this, SLOT(loadModule()));
            connect(d->manager, SIGNAL(deactivateAborted()), this, SLOT(abort()));
            d->manager->deactivateGadgets();
        }
    }
}