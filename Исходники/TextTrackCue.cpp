bool TextTrackCue::operator==(const TextTrackCue& cue) const
{
    if (cueType() != cue.cueType())
        return false;

    if (m_endTime != cue.endTime())
        return false;
    if (m_startTime != cue.startTime())
        return false;
    if (m_content != cue.text())
        return false;
    if (m_settings != cue.cueSettings())
        return false;
    if (m_id != cue.id())
        return false;
    if (m_textPosition != cue.position())
        return false;
    if (m_linePosition != cue.line())
        return false;
    if (m_cueSize != cue.size())
        return false;
    if (align() != cue.align())
        return false;
    
    return true;
}