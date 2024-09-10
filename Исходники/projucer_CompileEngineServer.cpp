String createCommandLineForLaunchingServer (const String& pipeName, const String& projectUID, const File& cacheLocation)
{
    StringArray info;
    info.add (pipeName);
    info.add (projectUID);
    info.add (cacheLocation.getFullPathName());

   #if JUCE_WINDOWS
    info.add (String::toHexString (getCurrentProcessID()));
   #endif

    const File exe (File::getSpecialLocation (File::currentExecutableFile).getFullPathName());

    return "\"" + exe.getFullPathName() + "\" " + commandPrefix + info.joinIntoString (commandTokenSeparator);
}