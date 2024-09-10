void Adaptive::updateProbsAdvanced(const double wgt, \
                                   const vector<Flashcard> & cards)
{   // Updates probabilities
    double probUnasked = 0.0;
    const double pStar = probability[currentIndex];
    int numOfNumAskedIs0 = 0;
    double alpha = fdim(1.0,pStar), beta;
    double gamma = 0.01, gamWeight = 1.0;   // Experiment with different gammas

    for (usInt ii = 0; ii < probability.size(); ii++)
    {
        if (cards[ii].data.getNumAsked() == 0 && ii != currentIndex)
        {
            probUnasked += probability[ii];
            numOfNumAskedIs0++;
        }
    }

    // Divide-by-zero guard
    if (numOfNumAskedIs0 < (probability.size() - 2))
    {
        gamma = 0.01;
        beta = (gamma * probUnasked / wgt + pStar * alpha) / (alpha - probUnasked);
        gamWeight = 1.0;
    }
    else
    {
        beta = pStar;
        gamWeight = -wgt;
        gamma = beta;
    }

    for (usInt ii = 0; ii < probability.size(); ii++)
    {
        if ( ii == currentIndex )
            probability[ii] *= fma(wgt,alpha,1.0);
        else if ( cards[ii].data.getNumAsked() != 0 )
            probability[ii] *= fma(-wgt,beta,1.0);
        else
            probability[ii] *= fma(gamWeight,gamma,1.0);
    }
}