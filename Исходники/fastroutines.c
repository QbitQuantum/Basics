static int internal_rayHitsAABB(vec3f *abp, vec3f *p_ray, float *dist) {
#define ap &abp[0]
#define bp &abp[1]
#define p_pos &p_ray[0]
#define p_dir &p_ray[1]
  #define SF(VAR) (*(v4sf*) VAR)
  float dirprod = X(SF(p_dir)) * Y(SF(p_dir)) * Z(SF(p_dir));
  #undef SF
  v4si mask = (v4si) FOUR(1<<31);
  v4si signs = mask & *(v4si*)p_dir;
  v4sf a = (v4sf) (V4SI(*ap) ^ signs);
  v4sf b = (v4sf) (V4SI(*bp) ^ signs);
  v4sf pos = (v4sf) (V4SI(*p_pos) ^ signs);
  v4sf dir = (v4sf) (V4SI(*p_dir) ^ signs);
  v4sf b_ = b;
  // pretend ray starts at origin: -pos
  b = __builtin_ia32_maxps(a, b) - pos;
  
  // if (X(b) < 0 || Y(b) < 0 || Z(b) < 0) return 0; // ray is pointed away from aabb.
  v4si bsign = mask & *(v4si*)&b;
  if (IX(bsign) | IY(bsign) | IZ(bsign)) return 0;
  
  a = __builtin_ia32_minps(a, b_) - pos;
  // multiply every component with dir.(x*y*z)
  // vec3f dista = a / dir, distb = b / dir;
  vec3f *_vdir = (vec3f*) &dir;
  vec3f *_dista = (vec3f*) &a, *_distb = (vec3f*) &b;
#define vdir (*_vdir)
#define dista (*_dista)
#define distb (*_distb)
  
  if (LIKELY(vdir.x != 0 && vdir.y != 0 && vdir.z != 0)) {
    // vdir += (v4sf) {0, 0, 0, 1};
    *(v4si*) &dir &= (v4si) {-1, -1, -1, 0};
    dir += (v4sf) {0, 0, 0, 1};
    a /= dir;
    b /= dir;
  } else {
    if (LIKELY(vdir.x != 0)) { dista.x /= vdir.x; distb.x /= vdir.x; }
    else { dista.x = copysignf(INFINITY, dista.x); distb.x = copysignf(INFINITY, distb.x); }
    
    if (LIKELY(vdir.y != 0)) { dista.y /= vdir.y; distb.y /= vdir.y; }
    else { dista.y = copysignf(INFINITY, dista.y); distb.y = copysignf(INFINITY, distb.y); }
    
    if (LIKELY(vdir.z != 0)) { dista.z /= vdir.z; distb.z /= vdir.z; }
    else { dista.z = copysignf(INFINITY, dista.z); distb.z = copysignf(INFINITY, distb.z); }
  }
  float entry = fmaxf(dista.x, fmaxf(dista.y, dista.z));
  float exit = fminf(distb.x, fminf(distb.y, distb.z));
  if (dist) { *dist = entry; }
  return entry <= exit;
#undef dista
#undef vdir
#undef ap
#undef bp
#undef p_pos
#undef p_dir
}