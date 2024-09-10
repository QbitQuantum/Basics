data_STEMDIRECTION LayerElement::GetDrawingStemDir()
{
    if (this->Is() == NOTE) {
        Note *note = dynamic_cast<Note*>(this);
        assert( note );
        return note->GetDrawingStemDir();
    }
    if (this->Is() == CHORD) {
        Chord *chord = dynamic_cast<Chord*>(this);
        assert( chord );
        return chord->GetDrawingStemDir();
    }
    return STEMDIRECTION_NONE;
}