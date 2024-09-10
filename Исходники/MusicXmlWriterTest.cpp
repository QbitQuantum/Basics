    void testNoteAccidentals()
    {
        Sheet* sheet = new Sheet();
        Bar* bar = sheet->addBar();
        Part* part = sheet->addPart("part");
        Voice* voice = part->addVoice();
        Staff* staff = part->addStaff();
        VoiceBar* vb = bar->voice(voice);

        for (int a = -2; a <= 2; a++) {
            Chord* c = new Chord(QuarterNote);
            c->addNote(staff, 0, a);
            vb->addElement(c);
        }

        validateOutput(sheet, "noteaccidentals.xml");
        delete sheet;
    }