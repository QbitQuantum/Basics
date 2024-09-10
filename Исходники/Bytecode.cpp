void Bytecode::OptimizeFixups()
{
	Fixup *f;
	int codeLength = GetLength();

	// the remap array initially is marked with bytes that
	// are to be deleted, then later it becomes the map
	// from old index to new one
	int *remap = new int[codeLength+1];
	memset(remap, 0, (codeLength+1) * sizeof(int));

	for(f=fFixups.GetHead(); f; f=f->GetNext()) {
		if (ShortenFixup(*f)) {
			// mark byte to be deleted
			remap[f->fLocation+1] = 1;

			// change the opcode
			fData[f->fLocation - f->fOpcodeOffset] = f->fShortOpcode;
		}
	}

	// trim the code and compute the remap array
	int offset = 0;
	for(int i=0; i<codeLength; ++i) {
		if (!remap[i]) {
			fData[offset] = fData[i];
			remap[i] = offset++;
		}
		else {
			remap[i] = offset;
		}
	}
	fData.resize(offset);

	// add remap entry for end-of-program
	remap[codeLength] = offset;

	// adjust the labels
	int i;
	for(i=0; i<(int)fLabels.size(); ++i) {
		fLabels[i] = remap[fLabels[i]];
	}

	// adjust the fixups
	for(f=fFixups.GetHead(); f; f=f->GetNext()) {
		f->fLocation = remap[f->fLocation];
	}

	// adjust source tags
	for(i=0; i<(int)fTags.size(); ++i) {
		fTags[i].fAddress = remap[fTags[i].fAddress];
	}

	delete [] remap;
}