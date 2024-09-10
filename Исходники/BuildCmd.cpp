bool BuildCmd::ParseInternal(const Vector<String>& arguments, unsigned startIndex, String& errorMsg)
{
    String argument = arguments[startIndex].ToLower();
    String value = startIndex + 1 < arguments.Size() ? arguments[startIndex + 1] : String::EMPTY;

    if (argument != "build")
    {
        errorMsg = "Unable to parse build command";
        return false;
    }

    if (!value.Length())
    {
        errorMsg = "Unable to parse build platform";
        return false;
    }

    buildPlatform_ = value.ToLower();

    for (int i = startIndex + 2; i < arguments.Size(); ++i)
    {
        String option = arguments[i].ToLower();
        
        if (option == "-tag")
        {
            if (arguments.Size() == i + 1)
            {
                errorMsg = "Missing tag";
                return false;
            }
        }
        else if (option == "-autolog")
        {
            autoLog_ = true;
        }
        else
        {
            errorMsg = "Invalid option: " + option;
            return false;
        }
    }

    String tag = startIndex + 2 < arguments.Size() ? arguments[startIndex + 2] : String::EMPTY;

    assetsBuildTag_ = tag.ToLower();

    return true;
}