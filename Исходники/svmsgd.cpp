void SVMSGDImpl::updateWeights(InputArray _sample, bool positive, float stepSize, Mat& weights)
{
    Mat sample = _sample.getMat();

    int response = positive ? 1 : -1; // ensure that trainResponses are -1 or 1

    if ( sample.dot(weights) * response > 1)
    {
        // Not a support vector, only apply weight decay
        weights *= (1.f - stepSize * params.marginRegularization);
    }
    else
    {
        // It's a support vector, add it to the weights
        weights -= (stepSize * params.marginRegularization) * weights - (stepSize * response) * sample;
    }
}