/**
 * perform a line search what step size in along the Newton direction is ideal, this one is used for extrapolation.
 * @param t potential scaling factor
 * @param rdm TPM containing the current approximation of the rdm.
 * @param ham Hamiltonian of the problem
 * @return the steplength
 */
double TPM::line_search(double t,const TPM &rdm,const TPM &ham){

   SUP P;

   P.fill(rdm);

   P.invert();

   return this->line_search(t,P,ham);

}