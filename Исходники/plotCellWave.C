static int 
buildMainMenu( aString *menu0,
               aString *&menu,
               RealGridCollectionFunction & u,
               aString *sequenceName,
               const int & numberOfSolutions,
               const int & numberOfComponents,
               const int & numberOfSequences,
               int & chooseAComponentMenuItem,
               int & chooseASolutionMenuItem,
               int & numberOfSolutionMenuItems,
               int & chooseASequenceMenuItem,
               int & numberOfSequenceMenuItems,
               const int & maxMenuSolutions,
	       const int & maximumNumberOfSolutionsInTheMenu,
	       int & solutionIncrement,
	       const int & maxMenuSequences,
	       const int & maximumNumberOfSequencesInTheMenu,
	       int & sequenceIncrement )
{
  // create the real menu by adding in the component names, these will appear as a 
  // cascaded menu
  char buff[120];

  chooseAComponentMenuItem=0;  // menu[chooseAComponentMenuItem]=">choose a component"
  chooseASolutionMenuItem=0;  
  numberOfSolutionMenuItems=0;
  chooseASequenceMenuItem=0;  
  numberOfSequenceMenuItems=0;

  int numberOfMenuItems0=0;
  while( menu0[numberOfMenuItems0]!="" )
  {
    numberOfMenuItems0++;
  }  
  numberOfMenuItems0++;

  // const int maxMenuSolutions=25;  // cascade solution menu if there are more than this many solutions
  // const int maximumNumberOfSolutionsInTheMenu=400;  // stride through the solutions if there are more
  // than this many solutions.
  // int solutionIncrement=1;                          // Here is the stride.

  // const int maxMenuSequences=25;  // cascade sequence menu if there are more than this many sequences
  // const int maximumNumberOfSequencesInTheMenu=400;  // stride through the sequences if there are more
  // than this many sequences.
  // int sequenceIncrement=1;                          // Here is the stride.

  delete [] menu;
  menu = new aString [numberOfMenuItems0+numberOfComponents+numberOfSolutions
		    +numberOfSolutions/maxMenuSolutions 
		    +numberOfSequences+numberOfSequences/maxMenuSequences +2];

  int i=-1;
  for( int i0=0; i0<numberOfMenuItems0 ; i0++ )
  {
    menu[++i]=menu0[i0];    
    if( menu[i]==">choose a component" )
    {
      chooseAComponentMenuItem=i;
      for( int j=0; j<numberOfComponents; j++ )
      {
	menu[++i]=u.getName(u.getComponentBase(0)+j);
	if( menu[i] == "" || menu[i]==" " )
	  menu[i]=sPrintF(buff,"component%i",u.getComponentBase(0)+j);
      }
    }
    else if( menu[i]=="<>choose a solution" )
    {
      // make menu items that display all the solutions. If there many solutions then we cascade the solutions
      // into groups, each group has maxMenuSolutions entries
      chooseASolutionMenuItem=i;
      solutionIncrement=1;
      if( numberOfSolutions>maximumNumberOfSolutionsInTheMenu )
	solutionIncrement=(numberOfSolutions+maximumNumberOfSolutionsInTheMenu-1)/maximumNumberOfSolutionsInTheMenu;
	  
      int k=0;
      for( int j=0; j<numberOfSolutions; j+=solutionIncrement )
      {
	if( numberOfSolutions>maxMenuSolutions && ( k % maxMenuSolutions==0) )
	{
	  if( j==0 )
	    menu[++i]=sPrintF(buff,">solutions %i to %i",j,j+maxMenuSolutions*solutionIncrement-1);
	  else
	    menu[++i]=sPrintF(buff,"<>solutions %i to %i",j,
			      min(j+maxMenuSolutions*solutionIncrement-1,numberOfSolutions-1));
	}
	menu[++i]=sPrintF(buff,"solution%i",j);
	k++;
      }
      if( numberOfSolutions>maxMenuSolutions )
	menu[++i]="< ";
      numberOfSolutionMenuItems=i-chooseASolutionMenuItem;
    }
    else if( menu[i]==">sequence" )
    {
      // make menu items that display all the sequences. If there many sequences then we cascade them into groups.
      chooseASequenceMenuItem=i;
      sequenceIncrement=1;
      if( numberOfSequences>maximumNumberOfSequencesInTheMenu )
	sequenceIncrement=(numberOfSequences+maximumNumberOfSequencesInTheMenu-1)/maximumNumberOfSequencesInTheMenu;
	  
      int k=0;
      for( int j=0; j<numberOfSequences; j+=sequenceIncrement )
      {
	if( numberOfSequences>maxMenuSequences && ( k % maxMenuSequences==0) )
	{
	  if( j==0 )
	    menu[++i]=sPrintF(buff,">sequences %i to %i",j,j+maxMenuSequences*sequenceIncrement-1);
	  else
	    menu[++i]=sPrintF(buff,"<>sequences %i to %i",j,
			      min(j+maxMenuSequences*sequenceIncrement-1,numberOfSequences-1));
	}
	menu[++i]=sequenceName[j];
	k++;
      }
      if( numberOfSequences>maxMenuSequences )
	menu[++i]="< ";
      numberOfSequenceMenuItems=i-chooseASequenceMenuItem;
    }
  }
  return 0;
}