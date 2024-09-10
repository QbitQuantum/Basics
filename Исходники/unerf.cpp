int main(int argc, char **argv) {
    try {
        std::vector<Common::UString> args;
        Common::Platform::getParameters(argc, argv, args);

        Aurora::GameID game = Aurora::kGameIDUnknown;

        int returnValue = 1;
        Command command = kCommandNone;
        Common::UString archive;
        std::set<Common::UString> files;
        std::vector<byte> password;

        if (!parseCommandLine(args, returnValue, command, archive, files, game, password))
            return returnValue;

        Aurora::ERFFile erf(new Common::ReadFile(archive), password);

        if      (command == kCommandInfo)
            displayInfo(erf);
        else if (command == kCommandList)
            listFiles(erf, game);
        else if (command == kCommandListVerbose)
            listVerboseFiles(erf, game);
        else if (command == kCommandExtract)
            extractFiles(erf, game, files, kExtractModeStrip);
        else if (command == kCommandExtractSub)
            extractFiles(erf, game, files, kExtractModeSubstitute);

    } catch (...) {
        Common::exceptionDispatcherError();
    }

    return 0;
}