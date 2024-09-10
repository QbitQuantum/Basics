int fton_fton(t_fton *x, double f)
{
	char *notes[12];
	if(x->accdntls == 1){
		char *sharps[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
		memcpy(notes, sharps, 12 * sizeof(char *));
	} else if (x->accdntls == 0) {
		char *flats[] = {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};
		memcpy(notes, flats, 12 * sizeof(char *));
	} else {
		object_error((t_object *)x, "accidental mode can be 0: flats or 1: sharps only");
		return 0;
	}
	
	double mCents, cents;
	int mNote, oct;
	char *roundCents, *noteSym;
	t_atom outList[2];
	
	if(f){
		mCents = 69 + (12 * log2(fabs(f)/x->a4));
	
		switch (x->centMode) {
			case 1:
				if(mCents > 0){
					asprintf(&roundCents, "%0.5f", mCents);
					mNote = (int)trunc(atof(roundCents) + 0.5);
				} else {
					asprintf(&roundCents, "%0.5f", mCents);
					mNote = (int)trunc(atof(roundCents) - 0.5);
				}
				//post("%d", mNote);
				if(mNote >= 0){
					oct = (mNote / 12) - 1;
					asprintf(&noteSym, "%s%d", notes[mNote%12], oct);
				} else {
					oct = ((mNote+1) / 12) - 2;
					asprintf(&noteSym, "%s%d", notes[(288+mNote)%12], oct);	
				}
//				post("%s", noteSym);
				atom_setsym(outList, gensym(noteSym));

				cents = 100 * (mCents - mNote);
				if (fabs(cents) < 0.001)//round off error tweak
					cents = 0;
				
				char *centSym;
				if(cents >= 0){
					asprintf(&centSym, "%+.2lf", (double)(lround(cents * 1000))/1000.);
				//	post("%s %f", centSym, cents);
					atom_setsym(outList+1, gensym(centSym));
				} else {
					asprintf(&centSym, "%+.2lf", (double)(lround(cents * 1000))/1000.);
				//	post("%s %f", centSym, cents);
					atom_setfloat(outList+1, (float)atof(centSym));
				}
				
				free(centSym);
				break;
			case 0:
				asprintf(&roundCents, "%0.5f", mCents);
				mNote = (int)trunc(atof(roundCents));

				if(mNote >= 0){
					oct = (mNote / 12) - 1;
					asprintf(&noteSym, "%s%d", notes[mNote%12], oct);
				} else {
					oct = ((mNote+1) / 12) - 2;
					asprintf(&noteSym, "%s%d", notes[(288+mNote)%12], oct);	
				}
				atom_setsym(outList, gensym(noteSym));
				
				cents = 100 * (mCents - mNote);
				if (fabs(cents) < 0.001)//round off error tweak
					cents = 0;
				atom_setfloat(outList+1, cents);
				break;
			default:
				break;
		}
		critical_enter(x->lock);
		memcpy(x->n, outList, 2 * sizeof(t_atom));
		critical_exit(x->lock);
		free(noteSym);
		free(roundCents);
		return 1;
	} else {
		outlet_anything(x->outlet, gensym("zero"), 0, NULL);
		free(noteSym);
		free(roundCents);
		return 0;
	}
}