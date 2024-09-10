// Make sure this contract checks out. Very high level.
// Verifies ID and signature.
// I do NOT call VerifyOwner() here, because the server may
// wish to verify its signature on this account, even though
// the server may not be the actual owner.
// So if you wish to VerifyOwner(), then call it.
bool OTTransactionType::VerifyAccount(const Nym& theNym)
{
    // Make sure that the supposed AcctID matches the one read from the file.
    //
    if (!VerifyContractID()) {
        otErr << "Error verifying account ID in "
                 "OTTransactionType::VerifyAccount\n";

        return false;
    } else if (!VerifySignature(theNym)) {
        otErr << "Error verifying signature in "
                 "OTTransactionType::VerifyAccount.\n";

        return false;
    }

    LogTrace(OT_METHOD)(__FUNCTION__)(
        ": We now know that...\n1) The expected Account ID matches the ID that "
        "was found on the object.\n2) The SIGNATURE VERIFIED on the object.")
        .Flush();

    return true;
}