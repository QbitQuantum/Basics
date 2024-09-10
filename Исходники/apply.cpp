ApplyResult
applyTransaction (Application& app, OpenView& view,
    STTx const& txn,
        bool retryAssured, ApplyFlags flags,
            beast::Journal j)
{
    // Returns false if the transaction has need not be retried.
    if (retryAssured)
        flags = flags | tapRETRY;

    JLOG (j.debug()) << "TXN "
        << txn.getTransactionID ()
        //<< (engine.view().open() ? " open" : " closed")
        // because of the optional in engine
        << (retryAssured ? "/retry" : "/final");

    try
    {
        auto const result = apply(app,
            view, txn, flags, j);
        if (result.second)
        {
            JLOG (j.debug())
                << "Transaction applied: " << transHuman (result.first);
            return ApplyResult::Success;
        }

        if (isTefFailure (result.first) || isTemMalformed (result.first) ||
            isTelLocal (result.first))
        {
            // failure
            JLOG (j.debug())
                << "Transaction failure: " << transHuman (result.first);
            return ApplyResult::Fail;
        }

        JLOG (j.debug())
            << "Transaction retry: " << transHuman (result.first);
        return ApplyResult::Retry;
    }
    catch (std::exception const&)
    {
        JLOG (j.warn()) << "Throws";
        return ApplyResult::Fail;
    }
}