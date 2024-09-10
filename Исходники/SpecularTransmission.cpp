SpectrumCoef_d SpecularTransmission::TotalScattering(bool i_hemisphere, SamplesSequence2D i_samples1, SamplesSequence2D i_samples2) const
{
    // Here we don't really need two samples for one integral's sample since specular transmission defines the reflected direction uniquely.
    size_t num_samples = std::distance(i_samples1.m_begin, i_samples1.m_end);
    ASSERT(num_samples > 0);

    double eta, Z_sign;
    if (i_hemisphere)
    {
        eta=m_refractive_index_outer/m_refractive_index_inner;
        Z_sign=1.0;
    }
    else
    {
        eta=m_refractive_index_inner/m_refractive_index_outer;
        Z_sign=-1.0;
    }

    double eta_sqr = eta*eta;

    SpectrumCoef_d ret;
    SamplesSequence2D::Iterator it=i_samples1.m_begin;
    for(size_t i=0; i<num_samples; ++i)
    {
        Point2D_d sample_incident = *(it++);

        Vector3D_d incident = SamplingRoutines::UniformHemisphereSampling(sample_incident);
        ASSERT(incident.IsNormalized());

        double sin_theta_incident_sqr = 1.0-incident[2]*incident[2];
        double sin_theta_exitant_sqr = eta_sqr*sin_theta_incident_sqr;
        ASSERT(sin_theta_exitant_sqr>=0.0);

        // Handle total internal reflection for transmission.
        if (sin_theta_exitant_sqr >= 1.0)
            continue;

        SpectrumCoef_d fresnel = m_fresnel(incident[2]*Z_sign);
        ASSERT(InRange(fresnel,0.0,1.0));

        ret.AddWeighted(SpectrumCoef_d(1.0)-fresnel, incident[2]);
    }

    ret *= m_transmittance*(2.0/num_samples);

    // Clamp spectrum values because a surface can not physically scatter more light than it received.
    ret.Clamp(0.0,1.0);
    return ret;
}