void GenericLayer::initWeights() {
	int j(0);
	MTRand mt;
	
	if ( this->hasChild && this->numNeurons > 0 && this->childLayer->numNeurons > 0) {
		this->weights.clear();
		this->weights.resize(this->numNeurons);
		
//		#pragma omp parallel for private(j) if(this->numNeurons > 500)
		for (int i=0; i<this->numNeurons; ++i) {
			this->weights.at(i).clear();
			this->weights.at(i).resize(this->childLayer->numNeurons);
			
			for (j=0; j<this->childLayer->numNeurons; ++j) {
				this->weights.at(i).at(j) = mt.rand(2)-1.0f;
			}
		}
	}
}