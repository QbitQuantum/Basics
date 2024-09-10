IsEltCentral::IsEltCentral(const SMWord& word)
  : Supervisor( ! word.getParent().gic.haveFastWordProblem() ),
    theWord( word ),
    theChecker( word.getParent() ),
    normalClosure( *this, word.getParent().gcm().normalClosure ),
    abelianInvariants( *this, word.getParent().gcm().abelianInvariants ),
    kbSupervisor( *this, word.getParent().gcm().kbSupervisor ),
    agSupervisor( *this, word.getParent().gcm().agSupervisor ),
    computeBasis( *this, word.getParent().gcm().computeBasis ),
    nilpotentQuotients( *this, word.getParent().gcm().nilpotentQuotients ),
    nilpotentWPInQuotients(*this),
    nilpotentWP( *this ),
    genetic( *this )
{
  SetOf<Word> comms;
  int numOfGens = word.getParent().getFPGroup().numberOfGenerators();
  Word w = word.getWord();
  
  for( int i = 0; i < numOfGens; ++i ) {
    Word gen = Word(Generator(i+1));
    comms |= (w.inverse() * gen.inverse() * w * gen).freelyReduce();
  }

  theChecker.replaceTheSet(comms);
  nilpotentWP->initialize(comms,&theWord.getParent());
  nilpotentWPInQuotients->initialize(comms,&theWord.getParent());
  genetic->init(theWord.getParent().getFPGroup(), comms, 
		GeneticWPCM::COMMUTATORS);

  if ( !displayInFE() ) adminStart();
}