Chord Chord::getTransposedVersion(int semitones) const
{
    if (semitones == 0)
        return Chord(getChordText(), getBeat());
    QString newRootKey = getTransposedRoot(getRootKey(), semitones);
    QString newChordText = newRootKey;

    if (hasLettersAfterRoot())
        newChordText += getLettersAfterRoot();

    if (hasLastPart())
        newChordText += getLastPart();

    if (hasBassInversion()) {
        QString newBassInversionRoot = getTransposedRoot(getBassInversion(), semitones);
        newChordText += "/" + newBassInversionRoot;
    }

    return Chord(newChordText, getBeat());
}