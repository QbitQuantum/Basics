void
AmendmentTableImpl::doVoting (Ledger::ref lastClosedLedger,
    SHAMap::ref initialPosition)
{

    // LCL must be flag ledger
    assert((lastClosedLedger->getLedgerSeq () % 256) == 0);

    AmendmentSet amendmentSet (lastClosedLedger->getParentCloseTimeNC ());

    // get validations for ledger before flag ledger
    ValidationSet valSet = getApp().getValidations ().getValidations (lastClosedLedger->getParentHash ());
    for (auto const& entry : valSet)
    {
        auto const& val = *entry.second;

        if (val.isTrusted ())
        {
            amendmentSet.addVoter ();
            if (val.isFieldPresent (sfAmendments))
            {
                for (auto const& amendment : val.getFieldV256 (sfAmendments))
                {
                    amendmentSet.addVote (amendment);
                }
            }
        }
    }
    reportValidations (amendmentSet);

    amendmentList_t lAmendments = getToEnable (lastClosedLedger->getCloseTimeNC ());
    for (auto const& uAmendment : lAmendments)
    {
        if (m_journal.warning) m_journal.warning <<
            "Voting for amendment: " << uAmendment;

        // Create the transaction to enable the amendment
        STTx trans (ttAMENDMENT);
        trans.setFieldAccount (sfAccount, Account ());
        trans.setFieldH256 (sfAmendment, uAmendment);
        uint256 txID = trans.getTransactionID ();

        if (m_journal.warning) m_journal.warning <<
            "Vote ID: " << txID;

        // Inject the transaction into our initial proposal
        Serializer s;
        trans.add (s, true);
#if RIPPLE_PROPOSE_AMENDMENTS
        SHAMapItem::pointer tItem = std::make_shared<SHAMapItem> (txID, s.peekData ());
        if (!initialPosition->addGiveItem (tItem, true, false))
        {
            if (m_journal.warning) m_journal.warning <<
                "Ledger already had amendment transaction";
        }
#endif
    }
}