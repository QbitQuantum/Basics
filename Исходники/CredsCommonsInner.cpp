// parses stream with configuration skipping comments (from # till the end of line)
// untill a line of form <non empty key>=<empty or no empty value>
// is found. Returns true when key and value FOUND, false when no more lines
bool CredsCommonsInnerBackend::getKeyAndValue(std::istream &f, const std::locale &loc,
                                              std::string &key, std::string &value) {
    std::string rawLine;
    while (std::getline(f, rawLine)) {
        std::istringstream rawLineStream(rawLine);
        std::string uncommentedLine;
        if (std::getline(rawLineStream, uncommentedLine, '#')) {
            size_t found = uncommentedLine.find_first_of("=");
            if (found != std::string::npos) {
                std::string tempKey = uncommentedLine.substr(0, found);
                std::string tempValue = uncommentedLine.substr(found + 1);
                if (!tempKey.empty()) {
                    key = normalizeString(tempKey, loc);
                    value = normalizeString(tempValue, loc);
                    return true;
                }
            }
       }
   }
   return false;
}