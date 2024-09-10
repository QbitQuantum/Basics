/** Apply a matrix of input values to the neural network and
return the output values from all neurons.
@param input The matrix of input values.
@return Return true if successful or false if an error occured. */
bool BPN::unoptimisedGetAnswer(const Matrix<float>& input)
{
#ifdef _DEBUG
	// check input dimensions
	if(input.height!=weights[0].height) return false;
	if(input.width!=1) return false;
#endif

	outputs[0] = input;

	Matrix<float> temp;
	for(int l=0;l<weightsSize;l++)
	{
		// use references for speed
		const Matrix<float>& thisWeights = weights[l];
		const Matrix<float>& thisOutputs = outputs[l];

		temp.resize(thisWeights.width, thisOutputs.width);
		// previous layer output transposed * next layer weights
		thisOutputs.transpose().multiply(thisWeights, temp);
		// net + bias weights
		temp.sum(biasWeights[l], temp);
		// temp = f(net)
		activationFN(temp, temp, l);
		outputs[l+1] = temp.transpose();
	}
	return true;
}