bool Bot::MayKeepRunningInCombat() const
{
    if (!HasEnemy())
        FailWith("MayKeepRunningInCombat(): there is no enemy");

    Vec3 enemyToBotDir = Vec3(self->s.origin) - EnemyOrigin();
    bool enemyMayHit = true;
    if (IsEnemyAStaticSpot())
    {
        enemyMayHit = false;
    }
    else if (EnemyFireDelay() > 300)
    {
        enemyMayHit = false;
    }
    else
    {
        Vec3 enemyLookDir = EnemyLookDir();
        float squaredDistance = enemyToBotDir.SquaredLength();
        if (squaredDistance > 1)
        {
            float distance = 1.0f / Q_RSqrt(squaredDistance);
            enemyToBotDir *= 1.0f / distance;
            // Compute a cosine of angle between enemy look dir and enemy to bot dir
            float cosPhi = enemyLookDir.Dot(enemyToBotDir);
            // Be aware of RL splash on this range
            if (distance < 150.0f)
                enemyMayHit = cosPhi > 0.3;
            else if (cosPhi <= 0.3)
                enemyMayHit = false;
            else
            {
                float cotPhi = Q_RSqrt((1.0f / (cosPhi * cosPhi)) - 1);
                float sideMiss = distance / cotPhi;
                // Use hitbox height plus a bit as a worst case
                float hitboxLargestSectionSide = 8.0f + playerbox_stand_maxs[2] - playerbox_stand_mins[2];
                enemyMayHit = sideMiss < hitboxLargestSectionSide;
            }
        }
    }

    if (enemyMayHit)
        return false;

    vec3_t botLookDir;
    AngleVectors(self->s.angles, botLookDir, nullptr, nullptr);
    // Check whether the bot may hit while running
    return ((-enemyToBotDir).Dot(botLookDir) > 0.99);
}