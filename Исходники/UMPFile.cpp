void UMPFile::parse (Tokeniser &tokeniser)
{
    std::string token = tokeniser.getToken();
    while (token.length()) {
        if (token == "base") {
            _base = tokeniser.getToken();
            if (_base.empty()) {
                globalErrorStream() << _fileName << ": base without parameter given\n";
                return;
            }
        } else if (token == "tile") {
            try {
                parseTile(tokeniser);
            } catch (UMPException &e) {
                globalErrorStream() << _fileName << ": " << e.getMessage() << "\n";
                return;
            }
        }
        token = tokeniser.getToken();
    }
}