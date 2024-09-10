void BlockParams::parseScheme(NxsToken& token, Category cat, nat &idCtr)
{
  auto numPart = tralnPtr->getNumberOfPartitions();
  auto partAppeared = std::vector<bool>(numPart, false); 

  token.GetNextToken();
  assert(token.GetToken().EqualsCaseInsensitive("=")); 
  token.GetNextToken();
  assert(token.GetToken().EqualsCaseInsensitive("(")); 

  auto scheme = std::vector<std::vector<nat>>{}; 
  while(not token.GetToken().EqualsCaseInsensitive(")") )
    {
      auto schemePart = std::vector<nat>{}; 
      bool startingNext = true; 
      
      // parse one partition part 
      while( not token.GetToken().EqualsCaseInsensitive(")") 	     
	     && (startingNext || not token.GetToken().EqualsCaseInsensitive(",")) )
	{
	  startingNext = false; 
	  // check if the separation item is an expasion item (-)
	  auto isLinkedRange =  token.GetToken().EqualsCaseInsensitive("-") ; 
	  auto isUnlinkedRange = token.GetToken().EqualsCaseInsensitive(":") ; 

	  token.GetNextToken();
	  nat part = token.GetToken().ConvertToInt();
	  nat start = ( isLinkedRange || isUnlinkedRange )  ? schemePart.back() +1  : part; 
	  nat end = part + 1 ;  

	  for(nat i = start ;  i < end ; ++i )
	    {
	      if(not (i < numPart))
		partitionError(i, numPart); 
	      if(partAppeared.at(i))
		{
		  tout << "error: partition " << i << " occurring twice in the same scheme. Check your parameter-block!" << std::endl; 
		  exitFunction(-1, true); 
		}
	      partAppeared.at(i) = true; 

	      if(isUnlinkedRange)
		{
		  scheme.push_back(schemePart);
		  schemePart = {i}; 
		}
	      else 
		schemePart.push_back(i); 
	    }

	  token.GetNextToken(); 
	}

      scheme.push_back(schemePart); 
    }

  // instantiate the parameters 
  for(auto schemePart : scheme )
    {
      assert(schemePart.size()  > 0 ); 
      parameters.push_back(CategoryFuns::getParameterFromCategory(cat,idCtr,getNumSeen(cat), schemePart, tralnPtr->getNumberOfTaxa()));
      ++idCtr; 
    }
}