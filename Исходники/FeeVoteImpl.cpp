void
FeeVoteImpl::doVoting (Ledger::ref lastClosedLedger,
    SHAMap::ref initialPosition)
{
    // LCL must be flag ledger
    assert ((lastClosedLedger->getLedgerSeq () % 256) == 0);

    detail::VotableInteger<std::uint64_t> baseFeeVote (
        lastClosedLedger->getBaseFee (), target_.reference_fee);

    detail::VotableInteger<std::uint32_t> baseReserveVote (
        lastClosedLedger->getReserve (0), target_.account_reserve);

    detail::VotableInteger<std::uint32_t> incReserveVote (
        lastClosedLedger->getReserveInc (), target_.owner_reserve);

    // get validations for ledger before flag
    ValidationSet const set =
        getApp().getValidations ().getValidations (
            lastClosedLedger->getParentHash ());
    for (auto const& e : set)
    {
        SerializedValidation const& val = *e.second;

        if (val.isTrusted ())
        {
            if (val.isFieldPresent (sfBaseFee))
            {
                baseFeeVote.addVote (val.getFieldU64 (sfBaseFee));
            }
            else
            {
                baseFeeVote.noVote ();
            }

            if (val.isFieldPresent (sfReserveBase))
            {
                baseReserveVote.addVote (val.getFieldU32 (sfReserveBase));
            }
            else
            {
                baseReserveVote.noVote ();
            }

            if (val.isFieldPresent (sfReserveIncrement))
            {
                incReserveVote.addVote (val.getFieldU32 (sfReserveIncrement));
            }
            else
            {
                incReserveVote.noVote ();
            }
        }
    }

    // choose our positions
    std::uint64_t const baseFee = baseFeeVote.getVotes ();
    std::uint32_t const baseReserve = baseReserveVote.getVotes ();
    std::uint32_t const incReserve = incReserveVote.getVotes ();

    // add transactions to our position
    if ((baseFee != lastClosedLedger->getBaseFee ()) ||
            (baseReserve != lastClosedLedger->getReserve (0)) ||
            (incReserve != lastClosedLedger->getReserveInc ()))
    {
        if (journal_.warning) journal_.warning <<
            "We are voting for a fee change: " << baseFee <<
            "/" << baseReserve <<
            "/" << incReserve;

        SerializedTransaction trans (ttFEE);
        trans.setFieldAccount (sfAccount, Account ());
        trans.setFieldU64 (sfBaseFee, baseFee);
        trans.setFieldU32 (sfReferenceFeeUnits, 10);
        trans.setFieldU32 (sfReserveBase, baseReserve);
        trans.setFieldU32 (sfReserveIncrement, incReserve);

        uint256 txID = trans.getTransactionID ();

        if (journal_.warning)
            journal_.warning << "Vote: " << txID;

        Serializer s;
        trans.add (s, true);

        SHAMapItem::pointer tItem = std::make_shared<SHAMapItem> (
            txID, s.peekData ());

        if (!initialPosition->addGiveItem (tItem, true, false))
        {
            if (journal_.warning) journal_.warning <<
                "Ledger already had fee change";
        }
    }
}