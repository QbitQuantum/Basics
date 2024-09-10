void WaterBall::update(float dt) {

  if(state == WATERDROP_STATE_NONE) {
    return ;
  }
  else if(state == WATERDROP_STATE_FILL) {
  
    if(drops.size() < 10) {
      uint64_t now = rx_hrtime();
      if(now >= spawn_timeout) {
        spawn_timeout = now + spawn_delay * 1000000ull;

        addRandomDrop();
    
        /*
          if(drops.size() == 10) {
          printf("We reached N drops, flush!\n");
          state = WATERDROP_STATE_FLUSH;
          flush_timeout = now + flush_delay * 1000000LLU;
          }
        */
      }
    }
  }
  else if(state == WATERDROP_STATE_FLUSH) {

#if 1
    // Remove the water drop when we need to flush (see below for a version where we remove 
    // water drops only when they are in a certain radius.
    uint64_t now = rx_hrtime();
    if(now >= flush_timeout) {
      if(drops.size()) {
        drops.erase(drops.begin());
        flush_timeout = now + flush_delay * 1000000ull;
        if(!drops.size()) {
          state = WATERDROP_STATE_FREE;
        }
      }
      else {
        state = WATERDROP_STATE_NORMAL;
      }
    }
#endif
  }

  if(!drops.size()) {
    return ;
  }

  vec2 dir;
  float dist = 0.0f;
  float dist_sq = 0.0f;
  vec2 f = 0.0f;
  float radius = drops.size() * radius_per_drop;
  float radius_sq = radius * radius;
  float neighbor_dist = 1;
  float neighbor_dist_sq = neighbor_dist * neighbor_dist;

  // REPEL FORCES:
#if 1
  for(size_t i = 0; i < drops.size(); ++i) {

    WaterDrop& a = drops[i];

    for(size_t j = i + i; j < drops.size(); ++j) {

      WaterDrop& b = drops[j];
      dir = b.position - a.position;
      dist_sq = dot(dir, dir);

      if(dist_sq > neighbor_dist_sq) {
        continue;
      }

      if(dist_sq < 0.01) {
        continue;
      }

      dir = normalized(dir);
      f = repel_force *  (1.0 - (1.0 / dist_sq)) * dir;
      a.forces -= f;
      b.forces += f;
    }
  }
#endif

  // ATTRACT FORCES
  float max_speed_sq = max_speed * max_speed;
  float speed_sq; 
  float k = 1.0f;
  uint64_t now = rx_hrtime();
   
  std::vector<WaterDrop>::iterator it = drops.begin();
  while(it != drops.end()) {
    WaterDrop& d = *it;
    {
      dir = position - d.position;
      dist = length(dir);

      if(dist < 0.01) {
        dist = 0.01;
      }

      if(dist > radius) {  /* when the particle is outiside the radius, it's attracted a lot more to the center */
        k = 15.0;
      }
#if 0
      // This is where we flush the water drops! 
      if(state == WATERDROP_STATE_FLUSH  && dist < radius) {
        if(now >= flush_timeout) {
          if(drops.size()) {
            it = drops.erase(drops.begin());
            flush_timeout = now + flush_delay * 1000000ull;

            if(!drops.size()) {
              state = WATERDROP_STATE_FREE;
              break;
            }
            continue;
          }
        }
      }
#endif

      dir /= dist;
      f = k * attract_force * (dist/radius) * dir;
      d.forces += f;
    }

    d.forces *= d.inv_mass * dt;
    d.velocity += d.forces * dt;
    d.position += d.velocity;
    d.forces = 0;

    // we do not add a fake drag force, but we limit the speed, this will make the 
    // particles bounce forever.
    speed_sq = dot(d.velocity, d.velocity);
    if(speed_sq > max_speed_sq) {
      d.velocity = normalized(d.velocity);
      d.velocity *= max_speed;
    }

    ++it;
  }
  /*
  glBindBuffer(GL_ARRAY_BUFFER, basic_vbo);

  size_t bytes_needed = sizeof(WaterDrop) * drops.size();
  if(bytes_needed > bytes_allocated) {
    glBufferData(GL_ARRAY_BUFFER, bytes_needed, drops[0].position.ptr(), GL_STREAM_DRAW);
  }
  else {
    glBufferSubData(GL_ARRAY_BUFFER, 0, bytes_needed, drops[0].position.ptr());
  }
  */
}