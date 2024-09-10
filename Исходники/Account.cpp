CAccountHD* CHDSeed::GenerateAccount(AccountType type, CWalletDB* Db)
{
    CAccountHD* account = nullptr;
    switch (type)
    {
        case Desktop:
            assert(m_nAccountIndex < HDMobileStartIndex);
            account = GenerateAccount(m_nAccountIndex, type);
            if (!account)
                return nullptr;
            ++m_nAccountIndex;
            break;
        case Mobi:
            assert(m_nAccountIndexMobi < HDWitnessStartIndex);
            account = GenerateAccount(m_nAccountIndexMobi, type);
            if (!account)
                return nullptr;
            ++m_nAccountIndexMobi;
            break;
        case PoW2Witness:
            assert(m_nAccountIndexWitness < HDFutureReservedStartIndex);
            account = GenerateAccount(m_nAccountIndexWitness, type);
            if (!account)
                return nullptr;
            ++m_nAccountIndexWitness;
            break;
        default:
            ; // fall through on purpose with null account
    }

    if (Db)
    {
        //fixme: (2.1) Can we just set dirty or something and then it gets saved later? That would be cleaner than doing this here.
        Db->WriteHDSeed(*this);
    }

    if (IsCrypted())
    {
        account->Encrypt(vMasterKey);
    }
    return account;
}