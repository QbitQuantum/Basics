double GACPforORGSolverGene::fitness( )
{
  if( fit==-1 ) {
    
    Word newWord = theWord2;
    Word relator = theGroup.relator();

    for( int pos=theWord2.length()-1 ; pos>=0 ; pos-- ) {
      for( unsigned c=0 ; c<lengthes[pos] ; ++c ) {
	GACPforORGSolverChromosome *chr = chromosomes[pos][c];
	Word w1;
	if( chr->deg ) w1 = chr->con * relator * chr->con.inverse( );
	else w1 = chr->con * relator.inverse( ) * chr->con.inverse( );
	GAConjProblemForORGroupSolver::insert( newWord , w1 , pos );
      }
    }

    newWord = GAConjProblemForORGroupSolver::greedyReduce( theGroup , newWord );

    //if new word shorter than second word
    if( newWord.length( )<theWord2.length( ) ) {
      
      hasShorterWords = true;

      //if newWord shorter than first word, change their places      
      if( newWord.length()<theWord1.length() ) {
	*this = GACPforORGSolverGene( theGroup , newWord , theWord1 );
	// here you needn't to check gene, because this function was invoked in Solver::tournament()
	// and if flag hasShorterWords sets, it invoke toStart() func., that resets all genes
	// check( );
	fit = proximity( theWord1 , theWord2 );
      }
      else {
	*this = GACPforORGSolverGene( theGroup , theWord1 , newWord );
	// here you needn't to check gene, because this function was invoked in Solver::tournament()
	// and if flag hasShorterWords sets, it invoke toStart() func., that resets all genes
	// check( );
	fit = proximity( theWord1 , theWord2 );
      }
    }	
    else {
      int c1 , c2;
      fit = proximity( theWord1 , newWord , &c1 , &c2 );
      
      //int L = theWord2.length( )-theWord1.length();
      //L>=0 always
      
      //There's two way
      //if reduced more than half of words, I do conjecture that other two parts are equal
      //if obtained a pair like ( w , w x ), I do conjecture that x==1
      if( fit/(theWord2.length( )+theWord1.length()) < 0.5 && theWord2.length( )+theWord1.length()>10 &&
	  //prev. condition (line) may be changed by next condition (line), prev. condition stronger than next one
	  //fit<=L  &&  
	  fit!=0  &&  
	  theWord1.length( )>3 ) 
	{
	  Word conjWord1;
	  Word conjWord2 = ( theWord1.inverse( ).cyclicallyPermute(c1) * newWord.cyclicallyPermute(c2) );
	  conjWord2 = conjWord2.freelyReduce();

	  hasConjecture = true;
	  conjectureWord = conjWord2;
	}
    }
    
  }
  return fit;
}