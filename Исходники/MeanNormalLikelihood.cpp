double MeanNormalLikelihood::logValue(RefArrayXd modelParameters)
{
    unsigned long n = observations.size();
    double lambda0;
    double lambda;
    ArrayXd argument;
    ArrayXd predictions;

    predictions.resize(n);
    predictions.setZero();
    model.predict(predictions, modelParameters);
    argument = (observations - predictions);
    argument = argument.square()*weights;

    lambda0 = lgammal(n/2.) - log(2) - (n/2.)*log(Functions::PI) + 0.5*weights.log().sum();
    lambda = lambda0 - (n/2.)*log(argument.sum());

    return lambda;
}