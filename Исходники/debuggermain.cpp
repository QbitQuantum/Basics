int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QStringList argList = a.arguments();

    if (argList.count() <= 0) {
        return -1;  // should at least have command name
    }

    SkString input;

    QStringList::const_iterator iter = argList.begin();

    SkString commandName(iter->toAscii().data());
    ++iter; // skip the command name

    for ( ; iter != argList.end(); ++iter) {
        if (0 == iter->compare("--help") || 0 == iter->compare("-h")) {
            usage(commandName.c_str());
            return -1;
        } else if (input.isEmpty()) {
            input = SkString(iter->toAscii().data());
        } else {
            usage(commandName.c_str());
            return -1;
        }
    }

    SkDebuggerGUI w;

    if (!input.isEmpty()) {
        if (SkStrEndsWith(input.c_str(), ".skp")) {
            w.openFile(input.c_str());
        } else {
            w.setupDirectoryWidget(input.c_str());
        }
    }

    w.show();
    return a.exec();
}