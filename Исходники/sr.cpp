void SR::boostAndRotate(SR::vec &fourVector, arma::vec3 boostDirection, double beta, arma::vec3 rotationAxis, double angle)
{
    boostDirection = normalise(boostDirection);
    rotationAxis = normalise(rotationAxis);
    arma::mat44 omega;
    omega.zeros();

    double gamma = 1.0/sqrt(1 - beta*beta);
    double chi = acosh(gamma);

    for(int mu=1; mu<=3; mu++) {
        // direction is a 3-vector, so subtract 1 to go from 4-vector indices to 3-vector index
        omega(0,mu) = boostDirection(mu-1)*chi;
        omega(mu,0) = boostDirection(mu-1)*chi;

        for(int nu=1; nu<=3; nu++) {
            if(mu==nu) continue;
            // Sum of all indices is 1+2+3 = 6.
            // So the third index is then 6 - mu - nu = 6 - (mu+nu)
            int axisOfRotation = 6 - (mu+nu);
            omega(mu,nu) = angle*rotationAxis(axisOfRotation);
            omega(nu,mu) = -angle*rotationAxis(axisOfRotation);
        }
    }

    mat44 rotationOperator = LorentzGenerator::generateElement(omega);
    fourVector.applyOperator(rotationOperator);

}