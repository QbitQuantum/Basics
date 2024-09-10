TER TransactionEngine::applyTransaction (
    STTx const& txn,
    TransactionEngineParams params,
    bool& didApply)
{
    WriteLog (lsTRACE, TransactionEngine) << "applyTransaction>";
    didApply = false;
    assert (mLedger);
    uint256 const& txID = txn.getTransactionID ();
    mNodes.init (mLedger, txID, mLedger->getLedgerSeq (), params);

#ifdef BEAST_DEBUG
    if (1)
    {
        Serializer ser;
        txn.add (ser);
        SerializerIterator sit (ser);
        STTx s2 (sit);

        if (!s2.isEquivalent (txn))
        {
            WriteLog (lsFATAL, TransactionEngine) <<
                "Transaction serdes mismatch";
            WriteLog (lsINFO, TransactionEngine) << txn.getJson (0);
            WriteLog (lsFATAL, TransactionEngine) << s2.getJson (0);
            assert (false);
        }
    }
#endif

    if (!txID)
    {
        WriteLog (lsWARNING, TransactionEngine) <<
            "applyTransaction: invalid transaction id";
        return temINVALID;
    }

    TER terResult = Transactor::transact (txn, params, this);

    if (terResult == temUNKNOWN)
    {
        WriteLog (lsWARNING, TransactionEngine) <<
            "applyTransaction: Invalid transaction: unknown transaction type";
        return temUNKNOWN;
    }

    if (ShouldLog (lsDEBUG, TransactionEngine))
    {
        std::string strToken;
        std::string strHuman;

        transResultInfo (terResult, strToken, strHuman);

        WriteLog (lsDEBUG, TransactionEngine) <<
            "applyTransaction: terResult=" << strToken <<
            " : " << terResult <<
            " : " << strHuman;
    }

    if (isTesSuccess (terResult))
        didApply = true;
    else if (isTecClaim (terResult) && !(params & tapRETRY))
    {
        // only claim the transaction fee
        WriteLog (lsDEBUG, TransactionEngine) << "Reprocessing to only claim fee";
        mNodes.clear ();

        SLE::pointer txnAcct = entryCache (ltACCOUNT_ROOT,
            getAccountRootIndex (txn.getSourceAccount ()));

        if (!txnAcct)
            terResult = terNO_ACCOUNT;
        else
        {
            std::uint32_t t_seq = txn.getSequence ();
            std::uint32_t a_seq = txnAcct->getFieldU32 (sfSequence);

            if (a_seq < t_seq)
                terResult = terPRE_SEQ;
            else if (a_seq > t_seq)
                terResult = tefPAST_SEQ;
            else
            {
                STAmount fee        = txn.getTransactionFee ();
                STAmount balance    = txnAcct->getFieldAmount (sfBalance);
                STAmount balanceVBC = txnAcct->getFieldAmount(sfBalanceVBC);

                // We retry/reject the transaction if the account
                // balance is zero or we're applying against an open
                // ledger and the balance is less than the fee
                if ((balance == zero) || (balanceVBC.getNValue() == 0) ||
                    ((params & tapOPEN_LEDGER) && (balance < fee)))
                {
                    // Account has no funds or ledger is open
                    terResult = terINSUF_FEE_B;
                }
                else
                {
                    if (fee > balance)
                        fee = balance;
                    txnAcct->setFieldAmount (sfBalance, balance - fee);
                    txnAcct->setFieldAmount(sfBalanceVBC, balanceVBC);
                    txnAcct->setFieldU32 (sfSequence, t_seq + 1);
                    entryModify (txnAcct);
                    didApply = true;
                }
            }
        }
    }
    else
        WriteLog (lsDEBUG, TransactionEngine) << "Not applying transaction " << txID;

    if (didApply)
    {
        if (!checkInvariants (terResult, txn, params))
        {
            WriteLog (lsFATAL, TransactionEngine) <<
                "Transaction violates invariants";
            WriteLog (lsFATAL, TransactionEngine) <<
                txn.getJson (0);
            WriteLog (lsFATAL, TransactionEngine) <<
                transToken (terResult) << ": " << transHuman (terResult);
            WriteLog (lsFATAL, TransactionEngine) <<
                mNodes.getJson (0);
            didApply = false;
            terResult = tefINTERNAL;
        }
        else
        {
            // Transaction succeeded fully or (retries are not allowed and the
            // transaction could claim a fee)
            Serializer m;
            mNodes.calcRawMeta (m, terResult, mTxnSeq++);

            txnWrite ();

            Serializer s;
            txn.add (s);

            if (params & tapOPEN_LEDGER)
            {
                if (!mLedger->addTransaction (txID, s))
                {
                    WriteLog (lsFATAL, TransactionEngine) <<
                        "Tried to add transaction to open ledger that already had it";
                    assert (false);
                    throw std::runtime_error ("Duplicate transaction applied");
                }
            }
            else
            {
                if (!mLedger->addTransaction (txID, s, m))
                {
                    WriteLog (lsFATAL, TransactionEngine) <<
                        "Tried to add transaction to ledger that already had it";
                    assert (false);
                    throw std::runtime_error ("Duplicate transaction applied to closed ledger");
                }

                // Charge whatever fee they specified.
                STAmount saPaid = txn.getTransactionFee ();
                mLedger->destroyCoins (saPaid.getNValue ());
            }
        }
    }

    mTxnAccount.reset ();
    mNodes.clear ();

    if (!(params & tapOPEN_LEDGER) && isTemMalformed (terResult))
    {
        // XXX Malformed or failed transaction in closed ledger must bow out.
    }

    return terResult;
}