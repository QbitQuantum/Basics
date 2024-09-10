ChordProgression ChordProgression::getStretchedVersion(int bpi) const
{
    if (!canBeUsed(bpi))
        return ChordProgression();// return a empty progression
    int newbeatsPerMesure = bpi/measures.size();

    int currentBpi = getBeatsPerInterval();
    if (currentBpi <= 0)// avoiding division by zero when calculating stretchFactor
        return ChordProgression(); // invalid bpi, returning empty progression
    float strechFactor = static_cast<float>(bpi/currentBpi);

    ChordProgression stretchedProgression;
    for (ChordProgressionMeasure originalMeasure : measures) {
        ChordProgressionMeasure newMeasure(newbeatsPerMesure);
        foreach (const Chord &chord, originalMeasure.getChords()) {
            int newChordBeat = chord.getBeat() * strechFactor;
            newMeasure.addChord(Chord(chord.getChordText(), newChordBeat));
        }
        stretchedProgression.addMeasure(newMeasure);
    }

    return stretchedProgression;
}