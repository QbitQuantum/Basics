QString PackageKitProxy::getUpdatesList()
{
    TransactionProxy *transaction = createTransaction();
    transaction->getUpdates();
    return transaction->name();
}