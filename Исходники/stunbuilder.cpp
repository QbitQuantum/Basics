HRESULT CStunMessageBuilder::AddRandomTransactionId(StunTransactionId* pTransId)
{
    StunTransactionId transid;
    uint32_t stun_cookie_nbo = htonl(STUN_COOKIE);

    uint32_t entropy=0;


    // on x86, the rdtsc instruction is about as good as it gets for a random sequence number
    // on linux, there's /dev/urandom


#ifdef _WIN32
    // on windows, there's lots of simple stuff we can get at to give us a random number
    // the rdtsc instruction is about as good as it gets
    uint64_t clock = __rdtsc();
    entropy ^= (uint32_t)(clock);
#else
    // on linux, /dev/urandom should be sufficient
    {
        int randomfile = ::open("/dev/urandom", O_RDONLY);
        if (randomfile >= 0)
        {
            int readret = read(randomfile, &entropy, sizeof(entropy));
            UNREFERENCED_VARIABLE(readret);
            ASSERT(readret > 0);
            close(randomfile);
        }
    }


    if (entropy == 0)
    {
        entropy ^= getpid();
        entropy ^= reinterpret_cast<uintptr_t>(this);
        entropy ^= time(NULL);
        entropy ^= AtomicIncrement(&g_sequence_number);
    }

#endif


    srand(entropy);


    // the first four bytes of the transaction id is always the magic cookie
    // followed by 12 bytes of the real transaction id
    memcpy(transid.id, &stun_cookie_nbo, sizeof(stun_cookie_nbo));
    for (int x = 4; x < (STUN_TRANSACTION_ID_LENGTH-4); x++)
    {
        transid.id[x] = (uint8_t)(rand() % 256);
    }

    if (pTransId)
    {
        *pTransId = transid;
    }

    return AddTransactionId(transid);
}