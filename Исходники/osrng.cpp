void NonblockingRng::GenerateBlock(byte *output, size_t size)
{
#ifdef CRYPTOPP_WIN32_AVAILABLE
    // Acquiring a provider is expensive. Do it once and retain the reference.
    static const MicrosoftCryptoProvider &hProvider = Singleton<MicrosoftCryptoProvider>().Ref();
# if defined(USE_MS_CRYPTOAPI)
    if (!CryptGenRandom(hProvider.GetProviderHandle(), (DWORD)size, output))
        throw OS_RNG_Err("CryptGenRandom");
# elif defined(USE_MS_CNGAPI)
    NTSTATUS ret = BCryptGenRandom(hProvider.GetProviderHandle(), output, (ULONG)size, 0);
    if (!(BCRYPT_SUCCESS(ret)))
    {
        // Hack... OS_RNG_Err calls GetLastError()
        SetLastError(NtStatusToErrorCode(ret));
        throw OS_RNG_Err("BCryptGenRandom");
    }
# endif
#else
    while (size)
    {
        ssize_t len = read(m_fd, output, size);
        if (len < 0)
        {
            // /dev/urandom reads CAN give EAGAIN errors! (maybe EINTR as well)
            if (errno != EINTR && errno != EAGAIN)
                throw OS_RNG_Err("read /dev/urandom");

            continue;
        }

        output += len;
        size -= len;
    }
#endif  // CRYPTOPP_WIN32_AVAILABLE
}