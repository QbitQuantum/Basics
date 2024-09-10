/***********************************************************************//**
 * @brief Perform integration over temporal component
 *
 * @param[in] event Observed event.
 * @param[in] obs Observation.
 * @param[in] grad Evaluate gradients.
 *
 * @exception GException::no_response
 *            Observation has no valid instrument response
 * @exception GException::feature_not_implemented
 *            Temporal integration not yet implemented
 *
 * This method integrates the source model over the temporal component. If
 * the response function has no time dispersion then no temporal integration
 * is needed and the observed photon arrival time is identical to the true
 * photon arrival time.
 *
 * @todo Needs implementation of temporal integration to handle time
 *       dispersion.
 ***************************************************************************/
double GModelSky::temporal(const GEvent& event, const GObservation& obs,
                           bool grad) const
{
    // Initialise result
    double value = 0.0;

    // Get response function
    GResponse* rsp = obs.response();
    if (rsp == NULL) {
        throw GException::no_response(G_TEMPORAL);
    }

    // Determine if time integration is needed
    bool integrate = rsp->hastdisp();

    // Case A: Integraion
    if (integrate) {
        throw GException::feature_not_implemented(G_TEMPORAL);
    }

    // Case B: No integration (assume no time dispersion)
    else {
        value = spectral(event, event.time(), obs, grad);
    }

    // Compile option: Check for NaN/Inf
#if defined(G_NAN_CHECK)
    if (isnotanumber(value) || isinfinite(value)) {
        std::cout << "*** ERROR: GModelSky::temporal:";
        std::cout << " NaN/Inf encountered";
        std::cout << " (value=" << value;
        std::cout << ", event=" << event;
        std::cout << ")" << std::endl;
    }
#endif

    // Return value
    return value;
}