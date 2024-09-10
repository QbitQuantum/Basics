bool sRprop::step(arr& w, const arr& grad, uint *singleI) {
    if(!stepSize.N) { //initialize
        stepSize.resize(w.N);
        lastGrad.resize(w.N);
        lastGrad.setZero();
        stepSize = delta0;
    }
    CHECK(grad.N==stepSize.N, "Rprop: gradient dimensionality changed!");
    CHECK(w.N==stepSize.N   , "Rprop: parameter dimensionality changed!");

    uint i=0, I=w.N;
    if(singleI) {
        i=*(singleI);
        I=i+1;
    }
    for(; i<I; i++) {
        if(grad.elem(i) * lastGrad(i) > 0) { //same direction as last time
            if(rMax) dMax=fabs(rMax*w.elem(i));
            stepSize(i) = _mymin(dMax, incr * stepSize(i)); //increase step size
            w.elem(i) += stepSize(i) * -_sgn(grad.elem(i)); //step in right direction
            lastGrad(i) = grad.elem(i);                    //memorize gradient
        } else if(grad.elem(i) * lastGrad(i) < 0) { //change of direction
            stepSize(i) = _mymax(dMin, decr * stepSize(i)); //decrease step size
            w.elem(i) += stepSize(i) * -_sgn(grad.elem(i)); //step in right direction (undo half the step)
            lastGrad(i) = 0;                               //memorize to continue below next time
        } else {                              //after change of direcion
            w.elem(i) += stepSize(i) * -_sgn(grad.elem(i)); //step in right direction
            lastGrad(i) = grad.elem(i);                    //memorize gradient
        }
    }

    return stepSize.max() < incr*dMin;
}