/*
 * fluid_midishare_wakeup
 */
static void fluid_midishare_wakeup (short r)
{
    MidiConnect (MidiShareDrvRef, r, true);
    MidiConnect (r, MidiShareDrvRef, true);
}