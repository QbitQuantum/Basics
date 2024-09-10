void WT0420RT0430::apply(Tx& a_tx)
{
  string id = a_tx.getId();
  try
	{
	  Message* currentIn_sp = a_tx.getCurrentIn();
	  {
		QueryManager queryManager;
		queryManager.begin();
		queryManager.updateTx(
							  id
							  ,ecc::pp::txs::state::ABORT
							  ,ecc::pp::txs::evolve::PASIVE
							  );
		queryManager.isCommit(true);
	  }
	  a_tx.setState( Tx::END );
	  a_tx.setEvent( Tx::UNDEFINED );
	}catch(Exception& e){
	  e
		<< "catch in WT0420RT0430::apply\n"
		;
	  a_tx.setState( Tx::END );
	  a_tx.setEvent( Tx::EXCEPTION );
	  throw;
	}catch(...){
	  a_tx.setState( Tx::END );
	  a_tx.setEvent( Tx::EXCEPTION );
	  throw;
	}
}