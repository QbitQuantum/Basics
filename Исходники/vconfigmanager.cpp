bool VConfigManager::isValidKeySequence(const QString &p_seq)
{
    return p_seq.isEmpty()
           || (p_seq.toLower() != "ctrl+q" && !QKeySequence(p_seq).isEmpty());
}