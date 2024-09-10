Tpresets::iterator Tpresets::findPreset(const char_t *presetName)
{
    for (iterator i=begin(); i!=end(); i++)
        if (_stricoll(presetName,(*i)->presetName)==0) {
            return i;
        }
    return end();
}