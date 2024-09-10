/***********************************************************************//**
 * @brief Evaluate function and gradients
 *
 * @param[in] event Observed event.
 * @param[in] obs Observation.
 * @return Function value.
 *
 * @exception GException::invalid_argument
 *            No CTA instrument direction found in event.
 *
 * Evaluates tha CTA background model and parameter gradients. The CTA
 * background model is a factorization of a spatial, spectral and
 * temporal model component. This method also applies a deadtime correction
 * factor, so that the normalization of the model is a real rate
 * (counts/exposure time).
 *
 * @todo Add bookkeeping of last value and evaluate only if argument 
 *       changed
 ***************************************************************************/
double GCTAModelBackground::eval_gradients(const GEvent& event,
                                           const GObservation& obs) const
{
    // Get pointer on CTA observation
    const GCTAObservation* ctaobs = dynamic_cast<const GCTAObservation*>(&obs);
    if (ctaobs == NULL) {
        std::string msg = "Specified observation is not a CTA observation.\n" +
                          obs.print();
        throw GException::invalid_argument(G_EVAL_GRADIENTS, msg);
    }

    // Extract CTA instrument direction
    const GCTAInstDir* dir  = dynamic_cast<const GCTAInstDir*>(&(event.dir()));
    if (dir == NULL) {
        std::string msg = "No CTA instrument direction found in event.";
        throw GException::invalid_argument(G_EVAL_GRADIENTS, msg);
    }

    // Create a Photon from the event
    // We need the photon to evaluate the spatial model
    // For the background, GEvent and GPhoton are identical
    // since the IRFs are not folded in
    GPhoton photon = GPhoton(dir->dir(), event.energy(),event.time());

    // Evaluate function and gradients
    double spat = (spatial() != NULL)
                  ? spatial()->eval_gradients(photon) : 1.0;
    double spec = (spectral() != NULL)
                  ? spectral()->eval_gradients(event.energy(), event.time()) : 1.0;
    double temp = (temporal() != NULL)
                  ? temporal()->eval_gradients(event.time()) : 1.0;

    // Compute value
    double value = spat * spec * temp;

    // Apply deadtime correction
    double deadc = obs.deadc(event.time());
    value       *= deadc;

    // Multiply factors to spatial gradients
    if (spatial() != NULL) {
        double fact = spec * temp * deadc;
        if (fact != 1.0) {
            for (int i = 0; i < spatial()->size(); ++i)
                (*spatial())[i].factor_gradient( (*spatial())[i].factor_gradient() * fact );
        }
    }

    // Multiply factors to spectral gradients
    if (spectral() != NULL) {
        double fact = spat * temp * deadc;
        if (fact != 1.0) {
            for (int i = 0; i < spectral()->size(); ++i)
                (*spectral())[i].factor_gradient( (*spectral())[i].factor_gradient() * fact );
        }
    }

    // Multiply factors to temporal gradients
    if (temporal() != NULL) {
        double fact = spat * spec * deadc;
        if (fact != 1.0) {
            for (int i = 0; i < temporal()->size(); ++i)
                (*temporal())[i].factor_gradient( (*temporal())[i].factor_gradient() * fact );
        }
    }

    // Return value
    return value;
}