	void BackPropogate(matrix &next_layer_weights_, matrix &next_layer_delta_weights_)
	{
		anti_sigmoid(deltas_, nuerons_);

		// put the vector on the diagonal for next operation ...


		next_layer_weights_.transpose();

		deltas_ = deltas_ | next_layer_weights_ * next_layer_delta_weights_;

		next_layer_weights_.transpose();

	}