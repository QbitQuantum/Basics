/*
    010509 Carl Corcoran
*/
void CCString::Path_StripToFilename()
{
    PathStripPathW(this->wszString);
}