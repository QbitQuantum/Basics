void sINLINE RNMarchingCubesBase<T>::func(const sVector31 &v,typename T::FieldType &pot,const funcinfo &fi)
{
  __m128 vx = _mm_load_ps1(&v.x);
  __m128 vy = _mm_load_ps1(&v.y);
  __m128 vz = _mm_load_ps1(&v.z);
  __m128 po = _mm_setzero_ps();           // p
  __m128 nx = _mm_setzero_ps();
  __m128 ny = _mm_setzero_ps();
  __m128 nz = _mm_setzero_ps();
  __m128 akkur = _mm_setzero_ps();
  __m128 akkug = _mm_setzero_ps();
  __m128 akkub = _mm_setzero_ps();
  __m128 akkua = _mm_setzero_ps();
  __m128 s255 = _mm_set_ps1(255.0f);
  
  sBool good = 0;

  for(sInt i=0;i<fi.pn4;i++)
  {
    const T::SimdType *part = fi.parts4 + i;

    __m128 dx = _mm_sub_ps(vx,part->x);
    __m128 dy = _mm_sub_ps(vy,part->y);
    __m128 dz = _mm_sub_ps(vz,part->z);
    __m128 ddx = _mm_mul_ps(dx,dx);
    __m128 ddy = _mm_mul_ps(dy,dy);
    __m128 ddz = _mm_mul_ps(dz,dz);
    __m128 pp = _mm_add_ps(_mm_add_ps(ddx,ddy),ddz);

    if(_mm_movemask_ps(_mm_cmple_ps(pp,fi.treshf4))!=0)
    {
      __m128 pp2 = _mm_sub_ps(_mm_div_ps(fi.one,pp),fi.tresh4);
      __m128 pp3 = _mm_max_ps(pp2,_mm_setzero_ps());
      po = _mm_add_ps(po,pp3);                  // p = p+pp;
      __m128 pp4 = _mm_mul_ps(pp3,pp3);         // pp*pp
      nx = _mm_add_ps(nx,_mm_mul_ps(pp4,dx));   // n += d*(pp*pp)
      ny = _mm_add_ps(ny,_mm_mul_ps(pp4,dy));
      nz = _mm_add_ps(nz,_mm_mul_ps(pp4,dz));
      if(T::Color==1)
      {
        akkur = _mm_add_ps(akkur,_mm_mul_ps(pp3,part->cr));
        akkug = _mm_add_ps(akkug,_mm_mul_ps(pp3,part->cg));
        akkub = _mm_add_ps(akkub,_mm_mul_ps(pp3,part->cb));
        good = 1;
      }
    }
  }

  sF32 p = 0;
  sVector30 n;
  
  _MM_TRANSPOSE4_PS(po,nx,ny,nz);
  __m128 r = _mm_add_ps(_mm_add_ps(_mm_add_ps(nx,ny),nz),po);
  n.x = r.m128_f32[1];
  n.y = r.m128_f32[2];
  n.z = r.m128_f32[3];
  p = r.m128_f32[0];

  if(p==0)
    n.Init(0,0,0);
  else
    n.UnitFast();
  pot.x = n.x;
  pot.y = n.y;
  pot.z = n.z;
  pot.w = p-fi.iso;
  if(T::Color)
  {
    if(good)
    {
      r = _mm_mul_ss(s255,_mm_rcp_ss(r));
  //    r = _mm_rcp_ss(r);
      _MM_TRANSPOSE4_PS(akkub,akkug,akkur,akkua);
      __m128 r2 = _mm_add_ps(_mm_add_ps(_mm_add_ps(akkur,akkug),akkub),akkua);

      r2 = _mm_mul_ps(r2,_mm_shuffle_ps(r,r,0x00));
      __m128i r3 = _mm_cvtps_epi32(r2);
      r3 = _mm_packs_epi32(r3,r3);
      __m128i r4 = _mm_packus_epi16(r3,r3);
      pot.c = r4.m128i_u32[0]|0xff000000;
    }
    else
    {
      pot.c = 0;
    }
  }
}