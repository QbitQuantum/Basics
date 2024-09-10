//Advance the solution one step.
// Stops and returns true if the error is less than the given value
void cgSolver::iterate(void)
{
    //Decide how far to advance
    comm.matrixVectorProduct(s_k,tmp);
    double s_kDot;
    s_kDot=comm.dotProduct(s_k,tmp);
    double alpha=residualMagSq/s_kDot;

    //Advance solution along the search direction
    fma(n,x_k, x_k,alpha,s_k);

    //Update residual
    double oldMagSq=residualMagSq;
    fma(n,r_k, r_k,-alpha,tmp);
    residualMagSq=comm.dotProduct(r_k,r_k);

    //printf("residualMagSq=%g\n",residualMagSq);
    //if (sqrt(fabs(residualMagSq))<=maxErr) return true; //We're done

    //Update search direction
    double beta=residualMagSq/oldMagSq;
    fma(n,s_k, r_k,beta,s_k);
}