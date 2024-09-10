bool Phong::Sample(const Vector3 &wi,
                   const Vector3 &normal,
                   const Vector2 st,
                   const Vector2 rndParam,
                   const Float uDiscrete,
                   Vector3 &wo,
                   Vector3 &contrib,
                   Float &cosWo,
                   Float &pdf,
                   Float &revPdf) const {
    Float cosWi = Dot(wi, normal);
    if (fabs(cosWi) < c_CosEpsilon) {
        return false;
    }

    Vector3 normal_ = normal;
    if (cosWi < Float(0.0)) {
        if (twoSided) {
            cosWi = -cosWi;
            normal_ = -normal_;
        } else {
            return false;
        }
    }

    const Float expo = exponent->Eval(st)[0];
    const Vector3 R = Reflect(wi, normal_);
    Float g;
    Vector3 n;
    if (uDiscrete > KsWeight) {
        g = Float(1.0);
        n = normal_;
    } else {
        g = expo;
        n = R;
    }
    const Float power = Float(1.0) / (g + Float(1.0));
    const Float cosAlpha = pow(rndParam[1], power);
    assert(cosAlpha >= Float(0.0) && cosAlpha <= Float(1.0));
    const Float sinAlpha = sqrt(Float(1.0) - square(cosAlpha));
    const Float phi = c_TWOPI * rndParam[0];
    const Vector3 localDir = Vector3(sinAlpha * cos(phi), sinAlpha * sin(phi), cosAlpha);
    Vector3 b0;
    Vector3 b1;
    CoordinateSystem(n, b0, b1);
    wo = localDir[0] * b0 + localDir[1] * b1 + localDir[2] * n;

    cosWo = Dot(normal_, wo);
    if (cosWo < c_CosEpsilon) {
        return false;
    }
    contrib = Vector3::Zero();
    pdf = Float(0.0);
    if (KsWeight > Float(0.0)) {
        const Float alpha = fmax(Dot(R, wo), Float(0.0));
        const Float weight = pow(alpha, expo) * c_INVTWOPI;
        const Float expoConst1 = (expo + Float(1.0));
        const Float expoConst2 = (expo + Float(2.0));
        if (weight > Float(1e-10)) {
            contrib = Ks->Eval(st) * (expoConst2 * weight);
            pdf = KsWeight * expoConst1 * weight;
        }
        // Phong lobe sampling is symmetric
        revPdf = pdf;
    }
    if (KsWeight < Float(1.0)) {
        contrib += Kd->Eval(st) * c_INVPI;
        pdf += (Float(1.0) - KsWeight) * cosWo * c_INVPI;
        // reverse cosine hemisphere sampling is not symmetric
        revPdf += (Float(1.0) - KsWeight) * cosWi * c_INVPI;
    }
    contrib *= cosWo;

    if (pdf < Float(1e-10)) {
        return false;
    }

    assert(pdf > Float(0.0));
    contrib *= inverse(pdf);

    return true;
}