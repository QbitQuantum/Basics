bool BasisSet::ReadMolDenBasisSet(BufferFile * Buffer, long NumAtoms) {
	bool result = true;
//	bool use5D=false, use7F=false, use10G=false;
	char	LineText[kMaxLineLength];
	long	shellCount = 0;
	
	Buffer->SkipnLines(1);
	for (int i=0; i<NumAtoms; i++) {
		long shellStart = shellCount;
		long atomNum=-1;
		Buffer->GetLine(LineText);
		sscanf(LineText, "%ld", &atomNum);
		if (atomNum != (i+1)) return false;	//incorrect order? Need to log a message...
		Buffer->GetLine(LineText);
		while (!IsBlank(LineText)) {
			char	token[kMaxLineLength];
			int		numPrims;
			if (sscanf(LineText, "%s %d", token, &numPrims) == 2) {
				short	ShellType;
				if (strlen(token) == 1) {
					switch (toupper(token[0])) {
						case 'S':
							ShellType = SShell;
							break;
						case 'P':
							ShellType = PShell;
							break;
						case 'D':
							ShellType = DShell;
							break;
						case 'F':
							ShellType = FShell;
							break;
						case 'G':
							ShellType = GShell;
							break;
						case 'H':
							ShellType = HShell;
							break;
						case 'I':
							ShellType = IShell;
							break;
						default:
							wxString msg;
							msg.Printf(_("Unknown shell type encountered, shell label = %s"), token);
							wxLogMessage(msg);
							return false; //invalid type
					}
				} else if (strlen(token) == 2) {
					if ((toupper(token[0])=='S')&&(toupper(token[1])=='P'))
						ShellType = -1;
					else return false;
				} else return false; //invalid shell type
				if (numPrims <= 0) return false;
				
				BasisShell t;
				Shells.push_back(t);
				Shells[shellCount].NumPrims = numPrims;
				Shells[shellCount].ShellType = ShellType;
				std::vector<float> & Exponent = Shells[shellCount].Exponent;
				std::vector<float> & NormCoef = Shells[shellCount].NormCoef;
				std::vector<float> & InputCoef = Shells[shellCount].InputCoef;
				Exponent.reserve(numPrims);
				if (ShellType >= 0) {
					NormCoef.reserve(numPrims);
					InputCoef.reserve(numPrims);
				} else {
					NormCoef.reserve(2*numPrims);
					InputCoef.reserve(2*numPrims);
				}
				for (long iprim=0; iprim<numPrims; iprim++) {
					InputCoef.push_back(0.0);
					NormCoef.push_back(0.0);
					if (ShellType<0) {
						InputCoef.push_back(0.0);
						NormCoef.push_back(0.0);
					}
					Exponent.push_back(0.0);
				}
				for (long iprim=0; iprim<numPrims; iprim++) {
					float	fexp, fcoef, fcoefp;
					Buffer->GetLine(LineText);
					ConvertExponentStyle(LineText);
					if (ShellType >= 0) {
						if (sscanf(LineText, "%f %f", &fexp, &fcoef) != 2) return false;
					} else {
						if (sscanf(LineText, "%f %f %f", &fexp, &fcoef, &fcoefp) == 3) {
							InputCoef[iprim+numPrims] = fcoefp;
						} else return false;
					}
					Exponent[iprim] = fexp;
					InputCoef[iprim] = fcoef;
				}
				NumFuncs += Shells[shellCount].GetNumFuncs(false);
				NumShells ++;
				shellCount ++;
			} else return false;
			Buffer->GetLine(LineText);
		}
		BasisMap[2*i] = shellStart;
		BasisMap[2*i+1] = shellCount - 1;
	}
	return result;
}