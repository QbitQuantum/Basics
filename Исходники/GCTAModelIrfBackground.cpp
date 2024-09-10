/***********************************************************************//**
 * @brief Evaluate function
 *
 * @param[in] event Observed event.
 * @param[in] obs Observation.
 * @return Function value.
 *
 * @exception GException::invalid_argument
 *            Specified observation is not of the expected type.
 *
 * @todo Make sure that DETX and DETY are always set in GCTAInstDir.
 ***************************************************************************/
double GCTAModelIrfBackground::eval(const GEvent& event,
                                    const GObservation& obs) const
{
    // Get pointer on CTA observation
    const GCTAObservation* cta = dynamic_cast<const GCTAObservation*>(&obs);
    if (cta == NULL) {
        std::string msg = "Specified observation is not a CTA observation.\n" +
                          obs.print();
        throw GException::invalid_argument(G_EVAL, msg);
    }

    // Get pointer on CTA IRF response
    const GCTAResponseIrf* rsp = dynamic_cast<const GCTAResponseIrf*>(cta->response());
    if (rsp == NULL) {
        std::string msg = "Specified observation does not contain an IRF response.\n" +
                          obs.print();
        throw GException::invalid_argument(G_EVAL, msg);
    }

    // Retrieve pointer to CTA background
    const GCTABackground* bgd = rsp->background();
    if (bgd == NULL) {
        std::string msg = "Specified observation contains no background"
                          " information.\n" + obs.print();
        throw GException::invalid_argument(G_EVAL, msg);
    }

    // Extract CTA instrument direction from event
    const GCTAInstDir* dir  = dynamic_cast<const GCTAInstDir*>(&(event.dir()));
    if (dir == NULL) {
        std::string msg = "No CTA instrument direction found in event.";
        throw GException::invalid_argument(G_EVAL, msg);
    }

    // Set DETX and DETY in instrument direction
    GCTAInstDir inst_dir = cta->pointing().instdir(dir->dir());

    // Evaluate function
    double logE = event.energy().log10TeV();
    double spat = (*bgd)(logE, inst_dir.detx(), inst_dir.dety());
    double spec = (spectral() != NULL)
                  ? spectral()->eval(event.energy(), event.time()) : 1.0;
    double temp = (temporal() != NULL)
                  ? temporal()->eval(event.time()) : 1.0;

    // Compute value
    double value = spat * spec * temp;

    // Apply deadtime correction
    value *= obs.deadc(event.time());

    // Return value
    return value;
}