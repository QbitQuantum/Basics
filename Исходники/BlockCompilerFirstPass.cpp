void BlockCompilerFirstPass::Perform(State* s, Address startFromAddress, Decoder& decoder, std::unordered_map<Address, std::shared_ptr<SimulationUnit>>* simulationUnitTable, BlockCompilerSimulatorEngine& simulatorEngine)
{
	s_ = s;
	simulationUnitTable_ = simulationUnitTable;

	discoveredStartAddresses_.clear();
	while (toProcessStartAddresses_.empty() == false)
		toProcessStartAddresses_.pop();

	AddToDiscoveredQueue_(startFromAddress);

	while (toProcessStartAddresses_.empty() == false)
	{
		address_ = toProcessStartAddresses_.front();
		toProcessStartAddresses_.pop();

		simulatorEngine.CreateInterpretedBlockStart(address_);
		
		isEndOfBasicBlockFound_ = false;
		while (isEndOfBasicBlockFound_ == false)
		{
			auto operation = decoder.Decode(address_);
			if (operation == nullptr)
			{
				isEndOfBasicBlockFound_ = true;
			}
			else
			{
				int length = operation->GetMetadata().GetLengthInBytes();
				for (int i = 0; i < length; ++i)
					s_->m[address_ + (Address)i].isCode = true;

				auto outgoingEdges = operation->GetOutgoingEdges();
				outgoingEdges->Accept(*this);
			}
		}
	}
}