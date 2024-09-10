double MultiLayerNN::LearnCrossValidation(int maxIteration, int k, double& ErrorAverage, double& ErrorStandarDesviation, bool doFeedBack, std::ostream& feedbackStream) throw(std::exception)
{
	if( k >= mLearnBook.size() )
		throw (new std::exception("No se puede hacer leave-k-out con k mas grande o igual a la particion universal"));

	std::stringstream firstNetwork;//Save the first Network
	Serialize(firstNetwork);

	 //Create necesary variables
	double** Y  = NULL;
	double** ro = NULL;
	double*  e  = NULL;
	std::vector< std::vector< std::vector<double> > > deltaWeights(mLayerCount);
	std::vector< std::vector< std::vector<double> > > deltaWeightsPrevious(mLayerCount);
	_LearnInicialization(Y,ro,e,deltaWeights,deltaWeightsPrevious);//reserve initialize variables

	
	int PartitionsNumber = ceil(mLearnBook.size()/(double)k);

	double* aux = new double[mOutputsNumber];//to calculate output error with learning data

	int* errors  = new int[PartitionsNumber];
	std::fill(errors,errors+PartitionsNumber, 0);
	double errorsThreshold = 0;

	Partition validationPartition(mLearnBook);

	validationPartition.InitLeaveKOut(k);

	for(int curPart=0;;++curPart)//until no more leave-k-out partitions
	{
		std::vector<int> shuffle(validationPartition.mLearnPartition.size());//creates shuffe here could be optimized
		validationPartition.GetShuffle(shuffle);
		std::vector<LearnInfo*>& LearnData = validationPartition.mLearnPartition;

		Load(firstNetwork);//each partition start again

		if( doFeedBack )
			feedbackStream<<"Particion Numero: "<<curPart<<std::endl;

		for(int k=0; k < maxIteration; ++k)//iterates the learning of the patrons
		{

			//Learn each patron
			for(int sample=0; sample < LearnData.size(); ++sample)
			{
				LearnInfo& info = *LearnData[shuffle[sample]];
				std::copy(info.mInputs.begin(), info.mInputs.end(), mInputs);
				_ProcessAll(Y);

				std::fill(aux,aux+mOutputsNumber, -1.0);
				aux[(int)info.mOutput] = 1.0;

				for(int j=0; j < mOutputsNumber; ++j)
					e[j] = mErrorFunction(Y[mLayerCount-1][j], aux[j]);

				_Retropropagate(Y,ro,e,deltaWeights,deltaWeightsPrevious);
			}

		}

		std::vector<double> Outputs(mOutputsNumber);
		std::vector<LearnInfo*>& TestData = validationPartition.mTestPartition;

		//Test each patron
		for(int sample=0; sample < TestData.size(); ++sample)
		{
			LearnInfo& info = *TestData[sample];
			std::copy(info.mInputs.begin(), info.mInputs.end(), mInputs);
			
			Outputs = Process();

			std::fill(aux,aux+mOutputsNumber, -1.0);
			aux[(int)info.mOutput] = 1.0;

			for(int j=0; j < mOutputsNumber; ++j)
			{
				e[j] = mErrorFunction(mSignFunction(Outputs[j]), aux[j]);
				if( e[j] != 0 )
					e[j] = e[j]/e[j];
			}

			//Errors to check with tolerance
			double newErrors = 0.0;
			for(int j=0; j < mOutputsNumber; ++j)
				aux[j] = abs(e[j]);
			Math::Sum(aux,mOutputsNumber,newErrors);
			errorsThreshold += newErrors;

			if(std::find(e,e+mOutputsNumber,1) != e+mOutputsNumber)
				++errors[curPart];
		}

		//Next Partitions
		if( !validationPartition.NextLeaveKOut() )
			break;
	}

	//errors / (double)PartitionsNumber;
	//errorsThreshold / (double)PartitionsNumber;
	ErrorAverage = 0.0;
	Math::Sum(errors, PartitionsNumber,ErrorAverage);
	ErrorAverage /= (double)PartitionsNumber;

	ErrorStandarDesviation = 0;
	for(int i=0; i < PartitionsNumber; ++i)
		ErrorStandarDesviation += errors[i]*errors[i];
	ErrorStandarDesviation = sqrt(ErrorStandarDesviation)/(double)PartitionsNumber;

	_LearnFinish(Y,ro,e,deltaWeights,deltaWeightsPrevious);

	Load(firstNetwork);//Keep the first Network

	firstNetwork.clear();

	delete[] aux;
	delete[] errors;
	return 1.0;
	//return ( errors/(double)mLearnBook.size() );
}