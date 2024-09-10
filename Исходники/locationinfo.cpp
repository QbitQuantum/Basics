void LocationInfo::write(ObjectOutputStream& os, Pool& p) const {
    if (lineNumber == -1 && fileName == NA && methodName == NA_METHOD) {
         os.writeNull(p);
    } else {
        unsigned char prolog[] = {
         0x72,
         0x00,
         0x21, 0x6F, 0x72, 0x67, 0x2E, 0x61, 0x70, 0x61, 0x63, 0x68, 0x65, 0x2E,
         0x6C, 0x6F, 0x67, 0x34, 0x6A, 0x2E, 0x73, 0x70, 0x69, 0x2E, 0x4C, 0x6F,
         0x63, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x49, 0x6E, 0x66, 0x6F, 0xED, 0x99,
         0xBB, 0xE1, 0x4A, 0x91, 0xA5, 0x7C, 0x02,
         0x00,
         0x01, 0x4C,
         0x00,
         0x08, 0x66, 0x75, 0x6C, 0x6C, 0x49, 0x6E, 0x66, 0x6F, 0x74,
         0x00,
         0x12, 0x4C, 0x6A, 0x61, 0x76, 0x61, 0x2F, 0x6C, 0x61, 0x6E, 0x67, 0x2F,
         0x53, 0x74, 0x72, 0x69, 0x6E, 0x67, 0x3B, 0x78, 0x70
        };
      os.writeProlog("org.apache.log4j.spi.LocationInfo", 2, (char*) prolog, sizeof(prolog), p);
        char* line = p.itoa(lineNumber);
        //
        //   construct Java-like fullInfo (replace "::" with ".")
        //
        std::string fullInfo(methodName);
        size_t openParen = fullInfo.find('(');
        if (openParen != std::string::npos) {
            size_t space = fullInfo.find(' ');
            if (space != std::string::npos && space < openParen) {
                fullInfo.erase(0, space + 1);
            }
        }
        openParen = fullInfo.find('(');
        if (openParen != std::string::npos) {
            size_t classSep = fullInfo.rfind("::", openParen);
            if (classSep != std::string::npos) {
                fullInfo.replace(classSep, 2, ".");
            } else {
                fullInfo.insert(0, ".");
            }
        }
        fullInfo.append(1, '(');
        fullInfo.append(fileName);
        fullInfo.append(1, ':');
        fullInfo.append(line);
        fullInfo.append(1, ')');
        os.writeUTFString(fullInfo, p);
    }
}