bool KCharSelectData::isDisplayable(CharSelectData* charselect, uint16_t unicode)
{
    // Qt internally uses U+FDD0 and U+FDD1 to mark the beginning and the end of frames.
    // They should be seen as non-printable characters, as trying to display them leads
    //  to a crash caused by a Qt "noBlockInString" assertion.
    if(c == 0xFDD0 || c == 0xFDD1)
        return false;

    return !isIgnorable(c) && isPrint(c);
}