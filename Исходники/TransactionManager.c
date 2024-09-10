struct Transaction *AddTransactionImpl(MESSAGE *message, struct TransactionUser *user, int type)
{
    if (type == TRANSACTION_TYPE_SERVER_NON_INVITE) {
        if (!ValidatedNonInviteMethod(message)) return NULL;
    }

    struct Transaction *t = CreateTransaction(message, user, type);
    _AddTransaction(t);
    RunFsm(t, TRANSACTION_EVENT_INIT);
    
    return t;

}