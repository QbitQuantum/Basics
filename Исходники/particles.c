void
plStepParticleSystem(PLparticles *ps, float dt)
{
  assert(ps != NULL);
  if (ps->enabled == false) return;

  size_t activeParticles = 0;
  for (size_t i = 0 ; i < ps->particleCount ; ++i) {
    if (ps->particles[i].active) {
      ps->particles[i].p += vf3_s_mul(ps->particles[i].v, dt) + vf3_s_mul(ps->obj->v, dt);
      ps->particles[i].age += dt;
      activeParticles++;

      if (ps->particles[i].age > ps->particles[i].lifeTime) {
        ps->particles[i].active = false;
        int_array_push(&ps->freeParticles, i);
        activeParticles --;
      }
    }
  }

  // Auto disable
  if (ps->autoDisable) {
    if (activeParticles == 0) {
      ps->enabled = false;
    }

    return;
  }

  // Not off or disabled, emitt new particles
  float newPartCount = ps->emissionRate * dt * (1.0 + rand_percent(10));
  float intPart;
  float frac = modff(newPartCount, &intPart);
  unsigned newParticles = (unsigned) intPart;

  // The fraction is handled with randomisation
  int rval = random() % 128;
  if ((float)rval/128.0f < frac) newParticles ++;

  for (unsigned i = 0 ; i < newParticles ; ++i) {
    if (ps->freeParticles.length > 0) {
      int i = int_array_remove(&ps->freeParticles, 0);
      ps->particles[i].active = true;
      ps->particles[i].age = 0.0;
      // Adjust lifetime by +-20 %
      ps->particles[i].lifeTime = ps->lifeTime + ps->lifeTime * rand_percent(20);
      ps->particles[i].p = v_q_rot(ps->p, ps->obj->q);
      ps->particles[i].v = v_q_rot(ps->v * vf3_set(rand_percent(10), rand_percent(10), rand_percent(10)), ps->obj->q);
      ps->particles[i].rgb = ps->rgb;
    } else {
      break;
    }
  }
}