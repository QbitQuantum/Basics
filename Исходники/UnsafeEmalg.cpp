/** Only maximization step included
 *
 *  This function performs maximization based on the evidence collected from tab file
 *  Since there's no belief propagation stage, it does not return proper likelihood.
 */
Real UnsafeEmalg::iterateWithoutEstep(MaximizationStep &mstep) {
    Real logZ = 0;
    Real likelihood = 0;

    // Expectation calculation
    int nProcessed = 0;

    for( Evidence::const_iterator e = _evidence.begin(); e != _evidence.end(); ++e ) {
        InfAlg* clamped = _estep.clone();

        // Apply evidence
        for( Evidence::Observation::const_iterator i = e->begin(); i != e->end(); ++i )
            clamped->clamp( clamped->fg().findVar(i->first), i->second );

        mstep.addExpectations( *clamped );

        delete clamped;

        nProcessed++;

        if (nProcessed % 10 == 0) {
            cout << nProcessed << " number of samples processed" << endl;
        }
    }

    // Maximization of parameters
    mstep.maximize(_estep.fg());

    return likelihood;
}