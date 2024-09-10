Vector3
Lambert::shade(const Ray& ray, const HitInfo& hit, const Scene& scene) const
{
    Vector3 L = Vector3(0.0f, 0.0f, 0.0f);
    
    const Vector3 viewDir = -ray.d; // d is a unit vector
    
    const Lights *lightlist = scene.lights();

    // reflectance
    if (m_ks != 0 && ray.times <3) {
      Vector3 Wr = -2 * dot(ray.d, hit.N) * hit.N + ray.d;
      Wr.normalize();
      Ray r(hit.P + (EPSILON * Wr), Wr);
      HitInfo hi;
      r.times = ray.times + 1;

      if(scene.trace(hi, r))
          L += m_spec * m_ks * hi.material->shade(r, hi, scene);
    }

    // cellular noise texture
    if(m_noisiness > 0) {
      float at[3] = { hit.P.x, hit.P.y, hit.P.z };
      const long mO = 3;
      float F[mO];
      float delta[mO][3];
      unsigned long *ID = new unsigned long();

      WorleyNoise::noise3D(at, mO, F, delta, ID);
      L += m_noisiness * (0.5f * (F[2] - F[1]));// + PerlinNoise::noise(at[0], at[1], at[2]));
    }

    // loop over all of the lights
    Lights::const_iterator lightIter;
    for (lightIter = lightlist->begin(); lightIter != lightlist->end(); lightIter++)
    {
        PointLight* pLight = *lightIter;
    
        Vector3 l = pLight->position() - hit.P;
        
        // the inverse-squared falloff
        float falloff = l.length2();
        
        // normalize the light direction
        l /= sqrt(falloff);

        // get the diffuse component
        float nDotL = dot(hit.N, l);
        Vector3 result = pLight->color();
        result *= f_diff * m_kd;
        
        L += std::max(0.0f, nDotL/falloff * pLight->wattage() / PI) * result;

        // highlights
        //if (m_ks != 0)
        L += m_spec * pLight->color() * m_ks * max(0.f, pow(dot(viewDir, l), SPECULAR_CONST));
          // / dot(hit.N, l);
    }

    // refraction
    if (m_trans != 0 && ray.times <3) {
      float n = (ray.times % 2 == 0) ? (ENV_INDEX / m_refInd) : (m_refInd / ENV_INDEX);
      float wn = dot(viewDir, hit.N);
      if (wn < 0) wn = -wn;

      Vector3 Wt = -1 * n * (viewDir - wn * hit.N) -
        sqrtf(1 - (n * n) * (1 - wn * wn)) * hit.N;
      Wt.normalize();

      Ray r(hit.P + (EPSILON * Wt), Wt);
      r.times = ray.times + 1;
      HitInfo hi;

      if (scene.trace(hi, r))
        L += m_trans * m_kt * hi.material->shade(r, hi, scene);
    }
    
    // add the ambient component
    L += m_ka;

    if(DO_BOUNCE && ray.times < BOUNCES) {
      float v = rand() / (float)RAND_MAX;
      float u = rand() / (float)RAND_MAX;
      Vector3 coord = hemisphereSample_cos(u,v);

      Vector3 unv = Vector3(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX);
      Vector3 v1 = cross(hit.N, unv);
      Vector3 v2 = cross(v1, hit.N);
      Vector3 dir = coord.x * v1 + coord.z * hit.N + coord.y * v2;
      dir.normalize();
      Ray r(hit.P, dir);
      r.times = ray.times + 1;
      HitInfo hi;

      if(scene.trace(hi, r))
        L+= m_kd * dot(r.d, hit.N) * hit.material->shade(r, hi, scene);
    }
    
    return L;
}