// Used to be I could just call pTrade->VerifySignature(nym), which is what
// I still call here, inside this function. But that's a special case -- an
// override
// from the OTScriptable / OTSmartContract version, which verifies parties and
// agents, etc.
//
bool OTTrade::VerifyNymAsAgent(Nym& nym,
                               Nym&, // Not needed in this version of
                                     // the override.
                               mapOfNyms*) const
{
    return VerifySignature(nym);
}