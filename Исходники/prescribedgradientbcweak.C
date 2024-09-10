void PrescribedGradientBCWeak :: giveTractionElNormal(size_t iElInd, FloatArray &oNormal, FloatArray &oTangent) const
{
	FloatArray xS, xE;
	giveTractionElCoord(iElInd, xS, xE);

    oTangent.beDifferenceOf(xE, xS);
    oTangent.normalize();

    oNormal = {
        oTangent [ 1 ], -oTangent [ 0 ]
    };
}