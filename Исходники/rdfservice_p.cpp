	void RDFGraphBasic::removeResources(RDFVariable const &variable)
	{
		QLinkedList<RDFVariable> removes;
		removes << variable;
		RDFTransactionPtr tx = createTransaction();
		while(1)
		{
			RDFStatementList removed_statements;
			executeQuery
					(RDFUpdate(service_context_data_->update())
					.addDeletion(*recurseRemoveResources
							(&removed_statements, removes.front(), &removes)));
			removes.pop_front();
			tx->commit();
			if(!removes.size())
				return;
			if(!(tx = createTransaction(RDFTransaction::Exclusive)))
			{
				warning() << "using recursive sharing removes requires that "
						"no transaction is active on the service";
				return;
			}
		}
	}