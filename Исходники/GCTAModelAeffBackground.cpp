/***********************************************************************//**
 * @brief Evaluate function
 *
 * @param[in] event Observed event.
 * @param[in] obs Observation.
 * @param[in] gradients Compute gradients?
 * @return Function value.
 *
 * @exception GException::invalid_argument
 *            Specified observation is not of the expected type.
 *
 * If the @p gradients flag is true the method will also set the parameter
 * gradients of the model parameters.
 *
 * @todo Make sure that DETX and DETY are always set in GCTAInstDir.
 ***************************************************************************/
double GCTAModelAeffBackground::eval(const GEvent&       event,
                                     const GObservation& obs,
                                     const bool&         gradients) const
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

    // Retrieve pointer to CTA Effective Area
    const GCTAAeff* aeff = rsp->aeff();
    if (aeff == NULL) {
        std::string msg = "Specified observation contains no effective area"
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

    // Set theta and phi from instrument coordinates
    double theta = std::sqrt(inst_dir.detx() * inst_dir.detx() +
                             inst_dir.dety() * inst_dir.dety());
    double phi   = gammalib::atan2d(inst_dir.dety(), inst_dir.detx()) *
                   gammalib::deg2rad;

    // Evaluate function
    double logE = event.energy().log10TeV();
    double spat = (*aeff)(logE, theta, phi,
                          cta->pointing().zenith(),
                          cta->pointing().azimuth(), false);
    double spec = (spectral() != NULL)
                  ? spectral()->eval(event.energy(), event.time(), gradients)
                  : 1.0;
    double temp = (temporal() != NULL)
                  ? temporal()->eval(event.time(), gradients) : 1.0;

    // Compute value
    double value = spat * spec * temp;

    // Apply deadtime correction
    double deadc = obs.deadc(event.time());
    value       *= deadc;

    // Optionally compute partial derivatives
    if (gradients) {

        // Multiply factors to spectral gradients
        if (spectral() != NULL) {
            double fact = spat * temp * deadc;
            if (fact != 1.0) {
                for (int i = 0; i < spectral()->size(); ++i)
                    (*spectral())[i].factor_gradient((*spectral())[i].factor_gradient() * fact );
            }
        }

        // Multiply factors to temporal gradients
        if (temporal() != NULL) {
            double fact = spat * spec * deadc;
            if (fact != 1.0) {
                for (int i = 0; i < temporal()->size(); ++i)
                    (*temporal())[i].factor_gradient((*temporal())[i].factor_gradient() * fact );
            }
        }

    } // endif: computed partial derivatives

    // Return value
    return value;
}