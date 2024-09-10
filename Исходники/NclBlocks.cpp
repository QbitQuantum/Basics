void MyCharactersBlock::HandleMatrix (NexusToken& token)
{
	int i, j;

	if (ntax == 0)
	{
		errormsg = "Must precede ";
      errormsg += id;
      errormsg += " block with a TAXA block or specify NEWTAXA and NTAX in the DIMENSIONS command";
		throw XNexus (errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
	}

	if (ntaxTotal == 0)
		ntaxTotal = taxa.GetNumTaxonLabels();

	// We use >= rather than just > below because someone might have
	// ELIMINATEd all characters, and we should allow that (even though it
	// is absurd)
	assert (nchar >= 0);

	if (matrix != NULL)
		delete matrix;
	mContData.clear();

	if (GetDataType() != continuous)
	{
		matrix = new DiscreteMatrix (ntax, nchar);
	}
	
	// Allocate memory for (and initialize) the arrays activeTaxon and
	// activeChar.
	// All characters and all taxa are initially active.
	activeTaxon = new bool[ntax];
	for (i = 0; i < ntax; i++)
		activeTaxon[i] = true;
		
	activeChar = new bool[nchar];
	for (j = 0; j < nchar; j++)
		activeChar[j] = true;

   // The value of ncharTotal is normally identical to the value of nchar
   // specified in the CHARACTERS block DIMENSIONS command.  If an
   // ELIMINATE command is processed, however, nchar < ncharTotal.  Note
   // that the ELIMINATE command will have already been read by now, and
   // the ELIMINATEd character numbers will be stored in the IntSet
   // eliminated.
   //
   // Note that if an ELIMINATE command has been read, charPos will have
   // already been created; thus, we only need to allocate and initialize
   // charPos if user  did not specify an ELIMINATE command
	if (charPos == NULL)
		BuildCharPosArray();

	// The value of ntaxTotal equals the number of taxa specified in the
	// TAXA block, whereas ntax equals the number of taxa specified in
	// the DIMENSIONS command of the CHARACTERS block.  These two numbers
   // will be identical unless some taxa were left out of the MATRIX
   // command of the CHARACTERS block, in which case ntax < ntaxTotal.
	if (taxonPos != NULL)
		delete [] taxonPos;
  	taxonPos = new int[ntaxTotal];
   for (i = 0; i < ntaxTotal; i++)
      taxonPos[i] = -1;

	if (GetDataType() == continuous)
		handleContMatrix (token);
   else if (transposing)
      HandleTransposedMatrix (token);
   else
      HandleStdMatrix (token);

   // If we've gotten this far, presumably it is safe to
   // tell the ASSUMPTIONS block that were ready to take on
   // the responsibility of being the current character-containing
   // block (to be consulted if characters are excluded or included
   // or if taxa are deleted or restored)
   assumptionsBlock.SetCallback(this);

   // this should be the terminating semicolon at the end of the matrix command
	if (GetDataType() != continuous)
   	token.GetNextToken();
   if (!token.Equals(";")) {
      errormsg = "Expecting ';' at the end of the MATRIX command; found ";
      errormsg += token.GetToken();
      errormsg += " instead";
		throw XNexus (errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
   }

}