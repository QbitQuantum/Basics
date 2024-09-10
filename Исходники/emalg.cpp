Real EMAlg::iterate( MaximizationStep &mstep ) {
    Real logZ = 0;
    Real likelihood = 0;

    _estep.run();
    logZ = _estep.logZ();

    // Expectation calculation
    for( Evidence::const_iterator e = _evidence.begin(); e != _evidence.end(); ++e ) {
        InfAlg* clamped = _estep.clone();
        // Apply evidence
        for( Evidence::Observation::const_iterator i = e->begin(); i != e->end(); ++i )
            clamped->clamp( clamped->fg().findVar(i->first), i->second );
        clamped->init();
        clamped->run();

        likelihood += clamped->logZ() - logZ;

        mstep.addExpectations( *clamped );

        delete clamped;
    }

    // Maximization of parameters
    mstep.maximize( _estep.fg() );

    return likelihood;
}