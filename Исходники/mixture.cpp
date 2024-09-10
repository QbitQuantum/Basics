bool CMT::Mixture::train(
	const MatrixXd& data,
	const MatrixXd& dataValid,
	const Parameters& parameters,
	const Component::Parameters& componentParameters)
{
	if(parameters.initialize && !initialized())
		initialize(data, parameters, componentParameters);

	ArrayXXd logJoint(numComponents(), data.cols());
	Array<double, Dynamic, 1> postSum;
	Array<double, 1, Dynamic> logLik;
	ArrayXXd post;
	ArrayXXd weights;

	// training and validation log-loss for checking convergence
	double avgLogLoss = numeric_limits<double>::infinity();
	double avgLogLossNew;
	double avgLogLossValid = evaluate(dataValid);
	double avgLogLossValidNew = avgLogLossValid;
	int counter = 0;

	// backup model parameters
	VectorXd priors = mPriors;
	vector<Component*> components;

	for(int k = 0; k < numComponents(); ++k)
		components.push_back(mComponents[k]->copy());

	for(int i = 0; i < parameters.maxIter; ++i) {
		// compute joint probability of data and assignments (E)
		#pragma omp parallel for
		for(int k = 0; k < numComponents(); ++k)
			logJoint.row(k) = mComponents[k]->logLikelihood(data) + log(mPriors[k]);

		// compute normalized posterior (E)
		logLik = logSumExp(logJoint);

		// average negative log-likelihood in bits per component
		avgLogLossNew = -logLik.mean() / log(2.) / dim();

		if(parameters.verbosity > 0) {
			if(i % parameters.valIter == 0) {
				// print training and validation error
				cout << setw(6) << i;
				cout << setw(14) << setprecision(7) << avgLogLossNew;
				cout << setw(14) << setprecision(7) << avgLogLossValidNew << endl;
			} else {
				// print training error
				cout << setw(6) << i << setw(14) << setprecision(7) << avgLogLossNew << endl;
			}
		}

		// test for convergence
		if(avgLogLoss - avgLogLossNew < parameters.threshold)
			return true;
		avgLogLoss = avgLogLossNew;

		// compute normalized posterior (E)
		post = (logJoint.rowwise() - logLik).exp();
		postSum = post.rowwise().sum();
		weights = post.colwise() / postSum;

		// optimize prior weights (M)
		if(parameters.trainPriors) {
			mPriors = postSum / data.cols() + parameters.regularizePriors;
			mPriors /= mPriors.sum();
		}

		// optimize components (M)
		if(parameters.trainComponents) {
			#pragma omp parallel for
			for(int k = 0; k < numComponents(); ++k)
				mComponents[k]->train(data, weights.row(k), componentParameters);
		} else {
			return true;
		}

		if((i + 1) % parameters.valIter == 0) {
			// check validation error
			avgLogLossValidNew = evaluate(dataValid);

			if(avgLogLossValidNew < avgLogLossValid) {
				// backup new found model parameters
				priors = mPriors;
				for(int k = 0; k < numComponents(); ++k)
					*components[k] = *mComponents[k];
				
				avgLogLossValid = avgLogLossValidNew;
			} else {
				counter++;

				if(parameters.valLookAhead > 0 && counter >= parameters.valLookAhead) {
					// set parameters to best parameters found during training
					mPriors = priors;

					for(int k = 0; k < numComponents(); ++k) {
						*mComponents[k] = *components[k];
						delete components[k];
					}

					return true;
				}
			}
		}
	}

	if(parameters.verbosity > 0)
		cout << setw(6) << parameters.maxIter << setw(11) << setprecision(5) << evaluate(data) << endl;

	return false;
}