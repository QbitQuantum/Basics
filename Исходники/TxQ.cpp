std::pair<TER, bool>
TxQ::apply(Application& app, OpenView& view,
    std::shared_ptr<STTx const> const& tx,
        ApplyFlags flags, beast::Journal j)
{
    auto const allowEscalation =
        (view.rules().enabled(featureFeeEscalation,
            app.config().features));
    if (!allowEscalation)
    {
        return ripple::apply(app, view, *tx, flags, j);
    }

    auto const account = (*tx)[sfAccount];
    auto currentSeq = true;

    std::lock_guard<std::mutex> lock(mutex_);

    // If there are other transactions in the queue
    // for this account, account for that before the pre-checks,
    // so we don't get a false terPRE_SEQ.
    auto accountIter = byAccount_.find(account);
    if (accountIter != byAccount_.end())
    {
        auto const sle = view.read(
            keylet::account(account));

        if (sle)
        {
            auto const& txQAcct = accountIter->second;
            auto const t_seq = tx->getSequence();
            auto const a_seq = sle->getFieldU32(sfSequence);

            currentSeq = a_seq == t_seq;
            for (auto seq = a_seq; !currentSeq && seq < t_seq; ++seq)
            {
                auto const existingCandidate =
                    txQAcct.findCandidateAt(seq);
                currentSeq = !existingCandidate;
            }
        }
    }

    // See if the transaction is likely to claim a fee.
    auto const pfresult = preflight(app, view.rules(),
        *tx, flags | (currentSeq ? tapNONE: tapPOST_SEQ), j);
    auto const pcresult = preclaim(pfresult, app, view);
    if (!pcresult.likelyToClaimFee)
        return{ pcresult.ter, false };

    auto const baseFee = pcresult.baseFee;
    auto const feeLevelPaid = getFeeLevelPaid(*tx,
        feeMetrics_.baseLevel, baseFee);
    auto const requiredFeeLevel = feeMetrics_.scaleFeeLevel(view);
    auto const transactionID = tx->getTransactionID();

    // Too low of a fee should get caught by preclaim
    assert(feeLevelPaid >= feeMetrics_.baseLevel);

    // Is there a transaction for the same account with the
    // same sequence number already in the queue?
    if (accountIter != byAccount_.end())
    {
        auto const sequence = tx->getSequence();
        auto& txQAcct = accountIter->second;
        auto existingCandidate = txQAcct.findCandidateAt(sequence);
        if (existingCandidate)
        {
            // Is the current transaction's fee higher than
            // the queued transaction's fee?
            // Don't care about the overflow flag
            auto requiredRetryLevel = mulDiv(
                existingCandidate->feeLevel,
                setup_.retrySequencePercent, 100).second;
            JLOG(j_.trace) << "Found transaction in queue for account " <<
                account << " with sequence number " << sequence <<
                " new txn fee level is " << feeLevelPaid <<
                ", old txn fee level is " <<
                existingCandidate->feeLevel <<
                ", new txn needs fee level of " <<
                requiredRetryLevel;
            if (feeLevelPaid > requiredRetryLevel
                || (existingCandidate->feeLevel < requiredFeeLevel &&
                    feeLevelPaid >= requiredFeeLevel))
            {
                // The fee is high enough to either retry or
                // the prior txn could not get into the open ledger,
                //  but this one can.
                // Remove the queued transaction and continue
                JLOG(j_.trace) <<
                    "Removing transaction from queue " <<
                    existingCandidate->txID <<
                    " in favor of " << transactionID;
                auto byFeeIter = byFee_.iterator_to(*existingCandidate);
                assert(byFeeIter != byFee_.end());
                assert(existingCandidate == &*byFeeIter);
                assert(byFeeIter->sequence == sequence);
                assert(byFeeIter->account == txQAcct.account);
                erase(byFeeIter);
            }
            else
            {
                // Drop the current transaction
                JLOG(j_.trace) <<
                    "Ignoring transaction " <<
                    transactionID <<
                    " in favor of queued " <<
                    existingCandidate->txID;
                return { telINSUF_FEE_P, false };
            }
        }
    }

    JLOG(j_.trace) << "Transaction " <<
        transactionID <<
        " from account " << account <<
        " has fee level of " << feeLevelPaid <<
        " needs at least " << requiredFeeLevel <<
        " to get in the open ledger, which has " <<
        view.txCount() << " entries.";

    // Can transaction go in open ledger?
    if (currentSeq && feeLevelPaid >= requiredFeeLevel)
    {
        // Transaction fee is sufficient to go in open ledger immediately

        JLOG(j_.trace) << "Applying transaction " <<
            transactionID <<
            " to open ledger.";
        ripple::TER txnResult;
        bool didApply;

        std::tie(txnResult, didApply) = doApply(pcresult, app, view);

        JLOG(j_.trace) << "Transaction " <<
            transactionID <<
                (didApply ? " applied successfully with " :
                    " failed with ") <<
                        transToken(txnResult);

        return { txnResult, didApply };
    }

    if (! canBeHeld(tx))
    {
        // Bail, transaction cannot be held
        JLOG(j_.trace) << "Transaction " <<
            transactionID <<
            " can not be held";
        return { feeLevelPaid >= requiredFeeLevel ?
            terPRE_SEQ : telINSUF_FEE_P, false };
    }

    // It's pretty unlikely that the queue will be "overfilled",
    // but should it happen, take the opportunity to fix it now.
    while (isFull())
    {
        auto lastRIter = byFee_.rbegin();
        if (feeLevelPaid > lastRIter->feeLevel)
        {
            // The queue is full, and this transaction is more
            // valuable, so kick out the cheapest transaction.
            JLOG(j_.warning) <<
                "Removing end item from queue with fee of" <<
                lastRIter->feeLevel << " in favor of " <<
                transactionID << " with fee of " <<
                feeLevelPaid;
            erase(byFee_.iterator_to(*lastRIter));
        }
        else
        {
            JLOG(j_.warning) << "Queue is full, and transaction " <<
                transactionID <<
                " fee is lower than end item";
            return { telINSUF_FEE_P, false };
        }
    }

    // Hold the transaction.
    // accountIter was already set when looking for duplicate seq.
    std::string op = "existing";
    if (accountIter == byAccount_.end())
    {
        // Create a new TxQAccount object and add the byAccount lookup.
        bool created;
        std::tie(accountIter, created) = byAccount_.emplace(
            account, TxQAccount(tx));
        (void)created;
        assert(created);
        op = "new";
    }
    auto& candidate = accountIter->second.addCandidate(
    { tx, transactionID, feeLevelPaid, flags, pfresult });
    // Then index it into the byFee lookup.
    byFee_.insert(candidate);
    JLOG(j_.debug) << "Added transaction " << candidate.txID <<
        " from " << op << " account " << candidate.account <<
        " to queue.";

    return { terQUEUED, false };
}