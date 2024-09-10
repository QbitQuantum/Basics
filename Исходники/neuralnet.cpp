void neuralNet::feedForward_layer(layerIterator_t nLayer)
{
	constFloatIterator_t pActivations, cWeight, endWeight;
	__m256 vTotal, vSub0, vSub1;
	__m256 *vWeight, *vAct, *vEndWeight;

	// summate each neuron's contribution
	for (neuronIterator_t cNeuron = nLayer->begin(), end = nLayer->end(); 
		cNeuron != end; 
		++cNeuron)
	{
		// foreach [previous neuron, current weight], up to endWeight
		pActivations = activations.begin() + (nLayer - 1)->front().iNeuronIndex;
		cWeight = cNeuron->weightsBegin(*this);
		endWeight = cNeuron->weightsEnd(*this);

		// (first 15 neurons) (TODO: redesign preamble and remove assertions for multiple of 16 size widths in neuralNet.h!)

		// summate all neurons of previous layer: (remaining batches of 8 neurons)
		vWeight = (__m256*)&cWeight[0];
		vAct = (__m256*)&pActivations[0];

		vEndWeight = (__m256*)&endWeight[0];

		// initialize the activation of this neuron to its bias weight. The bias weight's neuron is always on:
		vTotal = _mm256_set_ps(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, *endWeight); // can this be made with an aligned load?

		do // Take advantage of SIMD instructions by doing 16 multiplies per iteration
		{
			/* 
			 * each neuron's contribution is:
			 * input[j] += weight[i,j] * activation[i]
			 */
			// multiply:
			vSub0 = _mm256_mul_ps(vWeight[0], vAct[0]);
			vSub1 = _mm256_mul_ps(vWeight[1], vAct[1]);

			// prefetch next values: (these don't appear to help, are the networks too small for this to matter?)
			//_mm_prefetch((char*)(vWeight0+4), _MM_HINT_T0);
			//_mm_prefetch((char*)(vAct0+4), _MM_HINT_T0);

			// add to accumulator:
			vTotal = _mm256_add_ps(vTotal, vSub0);
			vTotal = _mm256_add_ps(vTotal, vSub1);

			// increment pointers:
			vWeight += 2;
			vAct += 2;
		}
		while (vWeight != vEndWeight);

		//finalize: (combine all 4 accumulators)
		{
			vTotal = _mm256_hadd_ps(vTotal, vTotal);
			vTotal = _mm256_hadd_ps(vTotal, vTotal);
			__m128 vUpperTotal = _mm256_extractf128_ps(vTotal, 1);
			vUpperTotal = _mm_add_ps(vUpperTotal, _mm256_castps256_ps128(vTotal));

			// store the lowest float into cInput:
			_mm_store_ss(&activations[cNeuron->iNeuronIndex], vUpperTotal);
		}
	}

	// activate all neurons in this layer:
	float* cActivation = (&activations.front() + nLayer->front().iNeuronIndex);
	float* lActivation = (&activations.front() + nLayer->back().iNeuronIndex + 1);
	float* lVectorActivation = lActivation - ((lActivation - cActivation)&(ALIGN_SIZE-1)); // equivalent to mod ALIGN_SIZE

	// aligned activations:
	while (cActivation != lVectorActivation)
	{
		activation_approx_avx(cActivation, cActivation);
		cActivation += ALIGN_SIZE;
	};

	// postscript: (unaligned activations):
	{
		size_t dActivation = (lActivation - cActivation);
		switch(dActivation)
		{
		case 7:
			activation_approx(cActivation+6,cActivation+6);
		case 6:
			activation_approx(cActivation+5,cActivation+5);
		case 5:
			activation_approx(cActivation+4,cActivation+4);
		case 4:
			activation_approx_sse(cActivation+0,cActivation+0);
			break;
		case 3:
			activation_approx(cActivation+2, cActivation+2);
		case 2:
			activation_approx(cActivation+1, cActivation+1);
		case 1:
			activation_approx(cActivation+0, cActivation+0);
		case 0:
			break;
		}
	}
}; // endOf feedForward_layer