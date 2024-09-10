const BSDF *MetalMaterial::GetBSDF(const DifferentialGeometry &i_dg, size_t i_triangle_index, MemoryPool &i_pool) const
  {
  BSDF *p_bsdf = new ( i_pool.Alloc(sizeof(BSDF)) ) BSDF(i_dg);

  SpectrumCoef_d r, a;
  if (mp_refractive_index && mp_absorption)
    {
    r = mp_refractive_index->Evaluate(i_dg, i_triangle_index);
    a = mp_absorption->Evaluate(i_dg, i_triangle_index);
    }
  else
    {
    ASSERT(mp_reflectance);
    SpectrumCoef_d reflectance = mp_reflectance->Evaluate(i_dg, i_triangle_index);
    reflectance.Clamp(0.0, 1.0);

    ApproximateFresnelParameters(reflectance, r, a);
    }
  FresnelConductor fresnel(r, a);

  BxDF *p_bxdf;
  if (mp_roughness)
    {
    typedef Microfacet<FresnelConductor,BlinnDistribution> BlinnMicrofacetMetal;
    double roughness = MathRoutines::Clamp(mp_roughness->Evaluate(i_dg, i_triangle_index), 0.001, 1.0);
    BlinnDistribution blinn(1.0/roughness);

    p_bxdf = new ( i_pool.Alloc(sizeof(BlinnMicrofacetMetal)) ) BlinnMicrofacetMetal(SpectrumCoef_d(1.0), fresnel, blinn);
    }
  else
    {
    ASSERT(mp_u_roughness && mp_v_roughness);

    typedef Microfacet<FresnelConductor,AnisotropicDistribution> AnisotropicMicrofacetMetal;
    double u_roughness = MathRoutines::Clamp(mp_u_roughness->Evaluate(i_dg, i_triangle_index), 0.001, 1.0);
    double v_roughness = MathRoutines::Clamp(mp_v_roughness->Evaluate(i_dg, i_triangle_index), 0.001, 1.0);
    AnisotropicDistribution anisotropic(1.0/u_roughness, 1.0/v_roughness);

    p_bxdf = new ( i_pool.Alloc(sizeof(AnisotropicMicrofacetMetal)) ) AnisotropicMicrofacetMetal(SpectrumCoef_d(1.0), fresnel, anisotropic);
    }

  p_bsdf->AddBxDF(p_bxdf);
  return p_bsdf;
  }