//==============================================================================
std::vector <std::string>
getStackBacktrace()
{
    std::vector <std::string> result;

#if BEAST_ANDROID || BEAST_MINGW || BEAST_BSD
    assert(false); // sorry, not implemented yet!

#elif BEAST_WINDOWS
    HANDLE process = GetCurrentProcess();
    SymInitialize (process, nullptr, TRUE);

    void* stack[128];
    int frames = (int) CaptureStackBackTrace (0,
        std::distance(std::begin(stack), std::end(stack)),
        stack, nullptr);

    // Allow symbols that are up to 1024 characters long.
    std::size_t constexpr nameLength = 1024;

    alignas(SYMBOL_INFO) unsigned char symbuf[
        sizeof(SYMBOL_INFO) + nameLength * sizeof(SYMBOL_INFO::Name)];

    auto symbol = reinterpret_cast<SYMBOL_INFO*>(symbuf);

    for (int i = 0; i < frames; ++i)
    {
        DWORD64 displacement = 0;

        std::memset (symbol, 0, sizeof(symbuf));

        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen = nameLength;

        if (SymFromAddr (process, (DWORD64)stack[i], &displacement, symbol))
        {
            std::string frame;

            frame.append (std::to_string (i) + ": ");

            IMAGEHLP_MODULE64 moduleInfo { sizeof(moduleInfo) };

            if (::SymGetModuleInfo64 (process, symbol->ModBase, &moduleInfo))
            {
                frame.append (moduleInfo.ModuleName);
                frame.append (": ");
            }

            frame.append (symbol->Name);

            if (displacement)
            {
                frame.append ("+");
                frame.append (std::to_string (displacement));
            }

            result.push_back (frame);
        }
    }

#else
    void* stack[128];
    int frames = backtrace (stack,
        std::distance(std::begin(stack), std::end(stack)));

    std::unique_ptr<char*[], decltype(std::free)*> frame {
        backtrace_symbols (stack, frames), std::free };

    for (int i = 0; i < frames; ++i)
        result.push_back (frame[i]);
#endif

    return result;
}