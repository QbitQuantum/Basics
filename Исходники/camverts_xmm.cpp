//////////////////////////////////////////////////////////////////////////////
//
// LightProjectClipXmm()
//
// works in model space with the old pipe
// assumes SetupLightsModel has been called
// if dstV and dstCount are non NULL bucket mem 
//
void Camera::LightProjectClipXmm( Plane *srcP, Vector *srcVect, Vector *srcNorm, UVPair *srcUV, U32 countV, U16 *srcI, U32 countI, VertexTL **dstV, U32 *dstVCount, U32 *dstICount) // = NULL, = NULL, = NULL)
{
  ASSERT( countI <= MAXINDICES);

  // temp pools : FIXME : eliminate temp copying
  U16              notCulledV[MAXVERTS];
  static VertexTL  litV_unaligned[MAXVERTS+1];
  static VertexTL *litV = (VertexTL*) (((U32)litV_unaligned+0x0000000f) & 0xfffffff0);
  U16              litI[MAXINDICES];

  BackfaceCull(srcP, notCulledV, countV, srcI, litI, countI);

  if (!countV)
  {
    // no forward faces
    if (dstV)
    {
      *dstV = NULL;
      *dstVCount = 0;
      *dstICount = 0;
    }
    return;
  }

  Material &material = *DxLight::Manager::curMaterial;
  Color diffa = (Color) Utils::FtoL( material.desc.diffuse.a * 255.0f) << 24;

  // calculate the parts of the diffuse color that are the same for all output vertexes
  ColorValueXmm diffInit;

  // FIXME: do we really want to ignore material ambient values (yes for DR2)
//  diffInit.r = curMaterial->desc.diffuse.r * Vid::renderState.ambientR + curMaterial->desc.emissive.r;
//  diffInit.g = curMaterial->desc.diffuse.g * Vid::renderState.ambientG + curMaterial->desc.emissive.g;
//  diffInit.b = curMaterial->desc.diffuse.b * Vid::renderState.ambientB + curMaterial->desc.emissive.b;

  diffInit.Set(
    Vid::renderState.ambientR + material.desc.emissive.r,
    Vid::renderState.ambientG + material.desc.emissive.g,
    Vid::renderState.ambientB + material.desc.emissive.b,
    material.desc.diffuse.a);

  const static __m128 zero = _mm_setzero_ps();
  const static ColorValueXmm specInit(zero, zero, zero, _mm_set_ps1(1.0f));

  // make the count a multiple of four by lighting the last vert multiple times
  notCulledV[countV+0] = notCulledV[countV+1] = notCulledV[countV+2] = notCulledV[countV+3] = notCulledV[countV-1];
  U32 countV_rem = ((4 - (countV % SIMD_WIDTH)) << 30) >> 30;
  countV += countV_rem;
  ASSERT( (countV % SIMD_WIDTH) == 0 );

  U8 clip_flags[MAXVERTS];

  for ( U32 vc = 0; vc < countV; vc += SIMD_WIDTH )
  {
    // set-up xmm vertex
    U16 i0 = notCulledV[vc+0], 
        i1 = notCulledV[vc+1], 
        i2 = notCulledV[vc+2], 
        i3 = notCulledV[vc+3];

    VertexXmm vert;
    vert.V0 = _mm_loadu_ps(&srcVect[i0]);
    vert.V1 = _mm_loadu_ps(&srcVect[i1]);
    vert.V2 = _mm_loadu_ps(&srcVect[i2]);
    vert.V3 = _mm_loadu_ps(&srcVect[i3]);

    __m128 lit[4];
    SetHomogeneousFromModelXmm(lit, &vert.V0);

    // generate clip flags
    const static U32 pos_w_mask_U32 = 0x7fffffff, 
                     neg_w_mask_U32 = 0x80000000;
    const static __m128 pos_w_mask = _mm_set_ps1(*((F32*) &pos_w_mask_U32)),
                        neg_w_mask = _mm_set_ps1(*((F32*) &neg_w_mask_U32));

    __m128 neg_w, pos_w;

#define COMPUTE_SUTHERLAND(i)                                                           \
    {                                                                                   \
      pos_w = _mm_and_ps(pos_w_mask, _mm_shuffle_ps(lit[(i)], lit[(i)], 0xff));         \
      neg_w = _mm_or_ps (neg_w_mask, pos_w);                                            \
      clip_flags[vc+(i)] = 0;                                                           \
      clip_flags[vc+(i)] |= (U8) (_mm_movemask_ps(_mm_cmplt_ps(lit[(i)], neg_w)));      \
      clip_flags[vc+(i)] << 4;                                                          \
      clip_flags[vc+(i)] |= (U8) (_mm_movemask_ps(_mm_cmplt_ps(pos_w, lit[(i)])));      \
      clip_flags[vc+(i)] &= 0x77;                                                       \
    }

    COMPUTE_SUTHERLAND(0);
    COMPUTE_SUTHERLAND(1);
    COMPUTE_SUTHERLAND(2);
    COMPUTE_SUTHERLAND(3);

    TRANSPOSE_4X4(vert.V0, vert.V1, vert.V2, vert.V3);
    vert.NV.Set(srcNorm[i0], srcNorm[i1], srcNorm[i2], srcNorm[i3]);
    vert.DIFFUSE = diffInit;
    vert.SPECULAR = specInit;

    // light four verts
    DxLight::Manager::LightModel(vert, material);

    VertexTL &out0 = litV[vc+0], 
             &out1 = litV[vc+1], 
             &out2 = litV[vc+2], 
             &out3 = litV[vc+3];

    _mm_storeu_ps(&out0, lit[0]);
    _mm_storeu_ps(&out1, lit[1]);
    _mm_storeu_ps(&out2, lit[2]);
    _mm_storeu_ps(&out3, lit[3]);

    vert.DIFFUSE.GetRGBA (out0.diffuse,  out1.diffuse,  out2.diffuse,  out3.diffuse );
    vert.SPECULAR.GetRGBA(out0.specular, out1.specular, out2.specular, out3.specular);

    out0.uv = srcUV[i0];
    out1.uv = srcUV[i1];
    out2.uv = srcUV[i2];
    out3.uv = srcUV[i3];
  }

  countV -= countV_rem;

  ClipToBucket( litV, countV, litI, countI, clip_flags, dstV, dstVCount, dstICount);
}