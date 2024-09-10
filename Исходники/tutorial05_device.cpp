/* task that renders a single screen tile */
Vec3fa renderPixelStandard(float x, float y, const Vec3fa& vx, const Vec3fa& vy, const Vec3fa& vz, const Vec3fa& p)
{
  float weight = 1.0f;
  Vec3fa color = Vec3fa(0.0f);

  /* initialize ray */
  RTCRay2 primary;
  primary.org = p;
  primary.dir = normalize(x*vx + y*vy + vz);
  primary.tnear = 0.0f;
  primary.tfar = inf;
  primary.geomID = RTC_INVALID_GEOMETRY_ID;
  primary.primID = RTC_INVALID_GEOMETRY_ID;
  primary.mask = -1;
  primary.time = 0;
  primary.transparency = 0.0f;

  while (true)
  {
    /* intersect ray with scene */
    rtcIntersect(g_scene,*((RTCRay*)&primary)); // FIXME: use (RTCRay&) cast
    
    /* shade pixels */
    if (primary.geomID == RTC_INVALID_GEOMETRY_ID) 
      break;

    float opacity = 1.0f-primary.transparency;
    Vec3fa diffuse = colors[primary.primID];
    Vec3fa La = diffuse*0.5f;
    color = color + weight*opacity*La; // FIXME: +=
    Vec3fa lightDir = normalize(Vec3fa(-1,-1,-1));
      
    /* initialize shadow ray */
    RTCRay2 shadow;
    shadow.org = primary.org + primary.tfar*primary.dir;
    shadow.dir = neg(lightDir);
    shadow.tnear = 0.001f;
    shadow.tfar = inf;
    shadow.geomID = RTC_INVALID_GEOMETRY_ID;
    shadow.primID = RTC_INVALID_GEOMETRY_ID;
    shadow.mask = -1;
    shadow.time = 0;
    shadow.transparency = 1.0f;
    
    /* trace shadow ray */
    rtcOccluded(g_scene,*((RTCRay*)&shadow)); // FIXME: use (RTCRay&) cast
    
    /* add light contribution */
    if (shadow.geomID) {
      Vec3fa Ll = diffuse*shadow.transparency*clamp(-dot(lightDir,normalize(primary.Ng)),0.0f,1.0f);
      color = color + weight*opacity*Ll; // FIXME: +=
    }

    /* shoot transmission ray */
    weight *= primary.transparency;
    primary.tnear = 1.001f*primary.tfar;
    primary.tfar = inf;
    primary.geomID = RTC_INVALID_GEOMETRY_ID;
    primary.primID = RTC_INVALID_GEOMETRY_ID;
    primary.transparency = 0.0f;
  }
  return color;
}