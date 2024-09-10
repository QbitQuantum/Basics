    polyIdPairs::polyIdPairs
    (
        const polyMesh& mesh,
        const potential& pot
    )
    :
    coeffVals_(),
    coeffNames_(),
    coeffNumIds_(),
    nIds_(0),
    coeffSize_(0),
    coeffType_("")
    {
        
        IOdictionary potentialDict
        (
            IOobject
            (
                "potentialDict",
             mesh.time().system(),
             mesh,
             IOobject::MUST_READ,
             IOobject::NO_WRITE
            )
        );
       
	//obtain information about pairs from pair subdict inside potentialdict 
        const dictionary& pairDict(potentialDict.subDict("pair"));
	List<word> pairs(pairDict.toc());//generate list of pairs
	nIds_ = pot.siteIdList().size();//obtain size of siteidlist
	label coeffsize = 0; 
        /**
         * traverse throught the list of pairs excluding electrostatic
         * further checking for interactions in pairs to take the total number
         * of species found which essentially provides a size of dynamic array
         * to be formed
         * loop until the first existing of coefficients are found after that
         * the loop is broken and no further traversal is done.
         */
        
        
	for(int i = 0;i<pairs.size();i++){
		if(pairs[i] != "electrostatic")
		{
			word pp = pairDict.subDict(pairs[i]).lookup("pairPotential");
			if(pp!="noInteraction"){
				List<word> coeff(pairDict.subDict(pairs[i]).subDict(pp+"Coeffs").toc());
                                //get the number of coeff's available
				coeffsize = coeff.size();
                                //set the size of coeffnames followed by generating
                                //coeff names into coeffnames array
                                coeffNames_.setSize(coeffsize);
                                coeffVals_.setSize(coeffsize);//set the size of variables
                                coeffNumIds_.setSize(coeffsize);
                                coeffSize_ = coeffsize;
                                coeffType_ = pp;
                                
                                for(int k=0; k<coeffsize;++k){
                                    coeffNames_[k] = coeff[k];
                                    coeffNumIds_[k] = k;
                                }
				break;//break if the first existence of coeff found
			}
		}
			
	}
       
	int c = 0;
	for(;c < coeffsize; ++c)
		coeffVals_[c].setSize(nIds_); 
	for(c = 0; c < coeffsize; ++c)
		for(int b = 0; b < nIds_; b++)
			coeffVals_[c][b].setSize(nIds_);
        
        //make the coeffs zero
        for(c=0;c < coeffsize; ++c){
            for(int i=0; i<nIds_; ++i){
                for(int j=0; j<nIds_; ++j){
                    coeffVals_[c][i][j] = 0;
                }
            }
        }

/*
 * loop over each potential site id list to form pairs of each site id with another
 * essentially two loops a and b will be running on each site id to form pairs.
 * 
 * for each pair created it will be checked with corresponding pairs inside potentialDict
 * if found pairPotential value for that pair will be obtained.
 *
 * if the obtained pair potential is not "noInteraction" then the resultant pairPotential value
 * will be used to form coeff string to determine "*Coeffs" value which could correspond to 
 * 'lennardJonesCoeffs', 'morseCoeffs', '*Coeffs' anything related with pairPotential value for that
 * particular pair.
 *
 * further to read each value for the N species inside the coeffs we will be using coeffsize variable
 * value obtained at the beginning which essentially consists of number of Species inside coeffs, subsequently
 * we will be traversing the loop and will use the list of species name inside coeffsNames_ array
 */
        for(int a=0; a<nIds_; a++)
        {
            word idA = pot.siteIdList()[a];
            for(int b=0; b<nIds_; b++)
            {
                word idB = pot.siteIdList()[b];
		word pname = idA+"-"+idB;
		if(pairDict.found(pname)){
			word pp = pairDict.subDict(pname)
				.lookup("pairPotential");
			if(pp!="noInteraction"){
				const dictionary& coeffs = pairDict
						.subDict(pname)
						.subDict(pp+"Coeffs");
				for(c=0; c<coeffsize; ++c){
					scalar temp = readScalar(coeffs.lookup(coeffNames_[c]));
					coeffVals_[c][a][b] = temp;
					coeffVals_[c][b][a] = temp;
				}//c loop ends
			}//no interaction if ends
		}//first if condition ends
            }//b loop ends
        }//a loop ends
        
    }//end function