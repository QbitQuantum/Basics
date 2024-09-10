float AIIdea::RateExplosion(const Character & shooter, const Point2i& position,
                            const ExplosiveWeaponConfig& config,
                            const float& expected_additional_distance)
{
  float rating = 0.0f;

  FOR_ALL_LIVING_CHARACTERS(team, character) {
    float distance = position.Distance(character->GetCenter());
    distance += expected_additional_distance;
    if (distance < 1.0f)
      distance = 1.0f;
    Double Dist = distance;
    float min_damage = GetDamageFromExplosion(config, Dist);
    float max_damage = min_damage;
    if (Dist <= config.blast_range) {
      float force = GetForceFromExplosion(config, Dist).tofloat();
      min_damage += MIN_DAMAGE_PER_FORCE_UNIT * force;
      max_damage += MAX_DAMAGE_PER_FORCE_UNIT * force;
    }
    bool is_friend = shooter.GetTeamIndex() == character->GetTeamIndex();
    if (is_friend) {
      rating -= RateDamageDoneToEnemy(min_damage, max_damage, *character);
    } else {
      rating += RateDamageDoneToEnemy(min_damage, max_damage, *character);
    }
  }