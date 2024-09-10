void HumanStream::write(const Bytes& b) {
    outputCache.append(b.get(),b.length());
    while (outputCache.find('\n')!=std::string::npos) {
        size_t idx = outputCache.find('\n');
        std::string show;
        show.append(outputCache.c_str(),idx);
        std::cout << "*** TYPE THIS ON THE OTHER TERMINAL: " << show << std::endl;
        outputCache = outputCache.substr(idx+1);
        SystemClock::delaySystem(1);
    }
}