void StartGen (short f)
{
  genRef = MidiOpen(GenName);
  MidiConnect (genRef, 0, true);
  GenProcess (MidiGetTime(), genRef, MidiGetTime(), 0, f * 100);
}