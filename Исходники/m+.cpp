int MyProcessDatFileIII(char* DatFileBuffer, int procid, vector<int> AllColumnIDList, vector<vector<int> > ColKeyToAllAlleleByPopList, vector<vector<vector<int> > >& AllAlleleByPopList, vector<std::string>& FullAccessionNameList, vector<std::string>& IndivPerPop, vector<int>& AllAlleles, std::string Rarify)
{
	//declare variables
	std::string foo;
	vector<std::string> foovector;
	std::string OldLocusName;
	std::string CurrLocusName;
	vector<std::string> LocusNames;
	vector<vector<std::string> > ActiveAlleleList;
	vector<std::string> OldAlleles;
	vector<vector<std::string> > TempList2d;
	vector<std::string> FilteredData;
	vector<std::string> ListToFilter;
	std::string IsNewPop = "no";
	vector<std::string>::iterator it;
	
	//initialize important data structures, unsized
	vector<vector<set<int> > > AllAlleleByPopListSet; //structure of this 3D vector is:
	// { { {pop1,loc1 alleles},{pop1,loc2 alleles},...}, { {pop2,loc1 alleles},{pop2,loc2 alleles},...} } }
	// this is the same structure as the vector<vector<vector<int> > > AllAlleleByPopList
	// if Rarify == "yes", AllAlleleByPopList just becomes ByPop3d.  if Rarify == "no", ByPop3d is reduced
	// to unique alleles at each locus using AllAlleleByPopListSet, then converted back into the vector
	// AllAlleleByPopList, which is updated as a reference


	unsigned int i,j,k,l;
	vector<std::string> bufvec;
	std::string NewPopID;
	std::string OldPopID = "init*@#rt4"; //use an unlikely population name for the initialization value

	if (procid == 0) cout << "  Reading data matrix...\n";
	//start the clock
	time_t startm,endm;
	time (&startm);

	//put giant char array buffer into a stream, then delete the buffer to save memory 
	stringstream s(DatFileBuffer);
	strcpy(DatFileBuffer,""); //clear char* 
	
	
	//read buffer into a vector, one line per item
	while (getline(s, foo))//get line from s, put in foo, consecutively
	{
		bufvec.push_back(foo);  
	}
	
	s.str(""); //clear stringstream
	int row = bufvec.size();
		
	//sort vector so that individuals from the same population form consecutive elements
	std::sort(bufvec.begin(), bufvec.end()); //no need to use fancy sort, lexicographic should be fine
		
	//split lines of bufvec into 2d vector
	vector<vector<std::string> > bufvec2d(bufvec.size()); 
	for (i=0;i<bufvec.size();++i) bufvec2d[i] = split(bufvec[i]);
	vector<std::string>().swap(bufvec); //clear bufvec
	
	//stop the clock
	time (&endm);
	double dif = difftime (endm,startm);
	if (procid == 0) 
	{
		if (dif==1) cout << "    " << dif << " second.\n";	
		else cout << "    " << dif << " seconds.\n";
	}
	
	//convert alleles to integer coding to save memory, vector access order 2
	if (procid == 0) 
	{
		cout << "  Recoding data...\n";
		time (&startm);
	}

	vector<vector<int> > bufvec2dint(bufvec2d.size(), vector<int>(bufvec2d[0].size())); //declare and size vector to hold new integer coded alleles
	unsigned int iz = ColKeyToAllAlleleByPopList.size();
	for (unsigned int i=0;i<iz;++i) //go thru each locus
	{
		//get all alleles at the locus
		vector<std::string> AllelesEncountered; //will contain the unique set of alleles at the locus
		unsigned int kz = bufvec2d.size();
		for (unsigned int k=0;k<kz;++k) //go thru all individuals
		{
			unsigned int jz = ColKeyToAllAlleleByPopList[i].size();
			for (unsigned int j=0;j<jz;++j) //get all alleles for an individual at this locus, then move to next indiv
			{
				int ColIndex = ColKeyToAllAlleleByPopList[i][j];
				std::string a = bufvec2d[k][ColIndex];  
				if (a == "9999") bufvec2dint[k][ColIndex] = -9999; //add the missing data value
				else
				{
					int AlleleInt; //the new, integerized, name of the allele
					std::vector<std::string>::iterator itr = std::find(AllelesEncountered.begin(), AllelesEncountered.end(), a);
					if (itr != AllelesEncountered.end()) //the allele has been found before
					{
						AlleleInt = itr - AllelesEncountered.begin(); //convert itr to index, the index is the integerized allele name
						bufvec2dint[k][ColIndex] = AlleleInt; //add the new name
					}
					else // you have a new allele
					{
						AllelesEncountered.push_back(a); //add new allele to list of those encountered
						AlleleInt = AllelesEncountered.size() - 1;  //calculate integerized allele name, starts at 0
						bufvec2dint[k][ColIndex] = AlleleInt;
					}
				}
			}
		}
	}
	
	//stop the clock
	if (procid == 0) 
	{
		time (&endm);
		dif = difftime (endm,startm);
		if (dif==1) cout << "    " << dif << " second.\n";	
		else cout << "    " << dif << " seconds.\n";	
	}

	
	if (procid == 0) cout << "  Building data structures...\n";
	time (&startm);
	
	//simplify bufvec2d by retaining only the first column, with POPID, then swap clear to save memory
	vector<string> PopIDvec;
	for (i=0;i<bufvec2d.size();++i)
		PopIDvec.push_back(bufvec2d[i][0]);
	vector<vector<std::string> >().swap(bufvec2d); //clear bufvec2d

	//break up vector into a 3d vector by population:  { { {pop1ind1elems},{pop1ind2elems},...}, { {pop2ind1elems},{pop2ind2elems},...} }
	vector<vector<vector<int> > > ByPop3d;
	for (i=0;i<bufvec2dint.size();++i)
	{
		//NewPopID = bufvec2d[i][0];  //access string in bufvec2d
		NewPopID = PopIDvec[i];
		IndivPerPop.push_back(NewPopID); //add the pop ID to a list to calc pop sizes later

		if (NewPopID != OldPopID) //then create a new population in ByPop3D
		{
			ByPop3d.resize(ByPop3d.size() + 1);
			
			//add the new population name to the AccessionNameList
			FullAccessionNameList.push_back(NewPopID);
		}
		
		//push row of integer elements on current line, onto last item of ByPop3d, which might be a new population as added just above
		//remember that the first three columns are 0 in bufvec2dint, so will also be 0 in ByPop3d
		ByPop3d[ByPop3d.size()-1].push_back(bufvec2dint[i]);
		
		OldPopID = NewPopID;
	}
	vector<vector<int> >().swap(bufvec2dint); //clear bufvec2dint, the integerized data is in ByPop3d

	//stop the clock
	time (&endm);
	if (procid == 0) 
	{
		dif = difftime (endm,startm);
		if (dif==1) cout << "    " << dif << " second.\n";	
		else cout << "    " << dif << " seconds.\n";	
	}

/*	//print out ByPop3d
	for (i=0;i<ByPop3d.size();++i)
	{
		cout << "Pop" << i << "\n";
		for (j=0;j<ByPop3d[i].size();++j)
		{
			cout << " Ind" << j << "  ";
			for (k=0;k<ByPop3d[i][j].size();++k)
			{
				cout << ByPop3d[i][j][k] << ",";
			}
			cout << "\n";
		}
	
	}
*/

	if (procid == 0) cout << "  Condensing data...\n";
	time (&startm);

	//When Rarify=yes, information on allele frequencies must be retained so all alleles are
	//placed into the AllAlleleByPopList (excluding -9999 missing data).  When Rarify=no, 
	//all alleles are passaged through a set (AllAlleleByPopListSet) so that only unique 
	//alleles end up in AllAlleleByPopList.
	if (Rarify == "yes")
	{
		//resize AllAlleleByPopList
		AllAlleleByPopList.resize(ByPop3d.size());//resize number of populations
		for (i=0;i<AllAlleleByPopList.size();++i)
		{
			AllAlleleByPopList[i].resize(ColKeyToAllAlleleByPopList.size()); //resize number of loci
		}
		
		//calculate size of AllAlleles
		AllAlleles.reserve(row*AllColumnIDList.size());

		//condense alleles by locus in AllAllelesByPopList, within each population
		int AlleleIndex;
		for (i=0;i<ByPop3d.size();++i) //go thru pops
		{
			for (j=0;j<ByPop3d[i].size();++j) //go thru indivs
			{
				for (k=0;k<ColKeyToAllAlleleByPopList.size();++k) //go through each locus
				{
					for (l=0;l<ColKeyToAllAlleleByPopList[k].size();++l) //assign columns to loci
					{
						AlleleIndex = ColKeyToAllAlleleByPopList[k][l];
						int NewAllele = ByPop3d[i][j][AlleleIndex]; //get the allele in the specified column
						AllAlleles.push_back(NewAllele); //add the allele to the list of all alleles, missing data included
						if (NewAllele != -9999) //exclude missing data
							AllAlleleByPopList[i][k].push_back(NewAllele); //add the allele to the set of unique alleles at locus k, pop i	
					}
				}
			}
		}
		
 		//stop the clock on Condensing data...
		time (&endm);
		if (procid == 0) 
		{
			dif = difftime (endm,startm);
			if (dif==1) cout << "    " << dif << " second.\n";	
			else cout << "    " << dif << " seconds.\n";	
		}
	}
	else if (Rarify == "no")
	{
		//resize AllAlleleByPopListSet
		AllAlleleByPopListSet.resize(ByPop3d.size());//resize number of populations
		for (i=0;i<AllAlleleByPopListSet.size();++i)
		{
			AllAlleleByPopListSet[i].resize(ColKeyToAllAlleleByPopList.size()); //resize number of loci
																		   //the index in ColKey is the locus index in AllAllelesByPopList level 2
																		   //the value of ColKey is the index of the allele in ByPop3d level 3
		}
		
		//calculate size of AllAlleles
		AllAlleles.reserve(row*AllColumnIDList.size());

		//condense alleles by locus in AllAllelesByPopListSet, within each population
		int AlleleIndex;
		for (i=0;i<ByPop3d.size();++i) //go thru pops
		{
			for (j=0;j<ByPop3d[i].size();++j) //go thru indivs
			{
				for (k=0;k<ColKeyToAllAlleleByPopList.size();++k) //go through each locus
				{
					for (l=0;l<ColKeyToAllAlleleByPopList[k].size();++l) //assign columns to loci
					{
						AlleleIndex = ColKeyToAllAlleleByPopList[k][l];
						int NewAllele = ByPop3d[i][j][AlleleIndex]; //get the allele in the specified column
						AllAlleles.push_back(NewAllele); //add the allele to the list of all alleles, missing data included
						if (NewAllele != -9999) //exclude missing data
							AllAlleleByPopListSet[i][k].insert(NewAllele); //add the allele to the set of unique alleles at locus k, pop i	
					}
				}
			}
		}
	
		//stop the clock on Condensing data...
		time (&endm);
		if (procid == 0) 
		{
			dif = difftime (endm,startm);
			if (dif==1) cout << "    " << dif << " second.\n";	
			else cout << "    " << dif << " seconds.\n";	
		}
		
		//start the clock on Converting...
		time_t startd,endd;
		if (procid == 0) 
		{
			cout << "  Converting data structures...\n";
			time (&startd);
		}

		//resize AllAlleleByPopList
		AllAlleleByPopList.resize(ByPop3d.size());//resize number of populations
		for (i=0;i<AllAlleleByPopList.size();++i)
		{
			AllAlleleByPopList[i].resize(ColKeyToAllAlleleByPopList.size()); //resize number of loci
		}
		//convert set to vector for further processing
		for (i=0;i<AllAlleleByPopList.size();++i)
		{
			for (j=0;j<AllAlleleByPopList[i].size();++j)
			{
				vector<int> ttvec(AllAlleleByPopListSet[i][j].begin(), AllAlleleByPopListSet[i][j].end()); //use constructor to convert set to vector	
				AllAlleleByPopList[i][j] = ttvec;
			}
		}
		vector<vector<set<int> > >().swap(AllAlleleByPopListSet); //clear variable, no longer needed
	
		//stop the clock on Converting...
		if (procid == 0) 
		{
			time (&endd);
			dif = difftime (endd,startd);
			if (dif==1) cout << "    " << dif << " second.\n";	
			else cout << "    " << dif << " seconds.\n";	
		}
	}
	
	vector<vector<vector<int> > >().swap(ByPop3d); //clear ByPop3d
			
	return 0;
}