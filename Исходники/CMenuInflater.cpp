Char32 CMenuInflater::MenuState::GetShortcut(
    /* [in] */ const String& shortcutString)
{
    if (shortcutString.IsNull()) {
        return 0;
    }
    else {
        return shortcutString.GetChar(0);
    }
}