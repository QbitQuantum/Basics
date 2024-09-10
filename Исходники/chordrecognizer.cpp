void ChordRecognizer::RegisterNewChordType(const QList<QString> &TheoryNotes, const ChordDescriptor &ChordDescr)
{
    QList<QString> SimplifiedChord = Chord(TheoryNotes).Simplify();
    if (SimplifiedChord != TheoryNotes)
    {
        //qDebug() << "Warning! Registering non-minimized chord " << ChordDescr.GetBaseName() << ","
        //         << ChordDescr.GetModifier() << "," << ChordDescr.GetSlash();
        // first register the non-simplified chord as it may be a special name for an inversion
        QList<int> IntervalPattern = Chord(Chord(TheoryNotes).WithoutDuplicateNotes()).ToIntervalPattern();
        QString Key = Chord::PatternToKey(IntervalPattern);
        unsigned int BaseNoteIndex = TheoryNotes.indexOf(QString(TheoryNotes[0]));
        /*
        if (m_PatternToDescriptor.contains(Key))
            qDebug() << ChordDescr.GetBaseName() << "," << ChordDescr.GetModifier() << "," << ChordDescr.GetSlash() << " overwrites existing "
                     << m_PatternToDescriptor[Key].first.GetBaseName() << "," << m_PatternToDescriptor[Key].first.GetModifier()
                     << "," << m_PatternToDescriptor[Key].first.GetSlash();
        */
        if (!m_PatternToDescriptor.contains(Key))
            m_PatternToDescriptor[Key] = QPair<ChordDescriptor, unsigned int>(ChordDescr, BaseNoteIndex);
    }

    QList<int> IntervalPattern = Chord(SimplifiedChord).ToIntervalPattern();
    QString Key = Chord::PatternToKey(IntervalPattern);
    unsigned int BaseNoteIndex = SimplifiedChord.indexOf(QString(TheoryNotes[0]));
    /*
    if (m_PatternToDescriptor.contains(Key))
        qDebug() << ChordDescr.GetBaseName() << "," << ChordDescr.GetModifier() << "," << ChordDescr.GetSlash() << " was prevented from overwriting existing "
                 << m_PatternToDescriptor[Key].first.GetBaseName() << "," << m_PatternToDescriptor[Key].first.GetModifier()
                 << "," << m_PatternToDescriptor[Key].first.GetSlash();

    */
    if (!m_PatternToDescriptor.contains(Key))
        m_PatternToDescriptor[Key] = QPair<ChordDescriptor, unsigned int>(ChordDescr, BaseNoteIndex);
}