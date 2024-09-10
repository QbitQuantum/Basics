    /// Evaluate the BRDF for the given pair of directions
    Color3f eval(const BSDFQueryRecord &bRec) const {

        /* This is a smooth BRDF -- return zero if the measure
           is wrong, or when queried for illumination on the backside */
        if (bRec.measure != ESolidAngle
            || Frame::cosTheta(bRec.wi) <= 0
            || Frame::cosTheta(bRec.wo) <= 0)
            return Color3f(0.0f);

        Vector3f wh = (bRec.wi + bRec.wo).normalized();

        float cosThetai = Frame::cosTheta(bRec.wi);
        float cosThetao = Frame::cosTheta(bRec.wo);


        //compute the Beckman term
        float D =  Microfacet::D(m_alpha, wh) / Frame::cosTheta(wh);
        //float D = Warp::squareToBeckmannPdf(wh, m_alpha) / Frame::cosTheta(wh);


        //compute the Fresnel term
        float F = fresnel(wh.dot(bRec.wi), m_extIOR, m_intIOR);

        //compute the geometry term
        float G = Microfacet::G(m_alpha, bRec.wi, bRec.wo, wh);
        //float G = G1(bRec.wi, wh) * G1(bRec.wo, wh);

        return (m_kd * INV_PI) + (m_ks * ((D * F * G)/(4.0f * cosThetai * cosThetao)));
    }