ECode CFastXmlSerializer::WriteText(
    /* [in] */ const String& text)
{
    if (mInTag) {
        FAIL_RETURN(Append('>'));
        mInTag = FALSE;
    }
    FAIL_RETURN(EscapeAndAppendString(text));
    if (mIndent) {
        mLineStart = text.GetLength() > 0 && (text.GetChar(text.GetLength()-1) == '\n');
    }
    return NOERROR;
}