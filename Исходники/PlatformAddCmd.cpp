bool PlatformAddCmd::Parse(const Vector<String>& arguments, unsigned startIndex, String& errorMsg)
{
    String argument = arguments[startIndex].ToLower();
    String value = startIndex + 1 < arguments.Size() ? arguments[startIndex + 1] : String::EMPTY;

    if (argument != "platform-add")
    {
        errorMsg = "Unable to parse build command";
        return false;
    }

    if (!value.Length())
    {
        errorMsg = "Unable to parse platform";
        return false;
    }

    platformToAdd_ = value.ToLower();

    return true;
}