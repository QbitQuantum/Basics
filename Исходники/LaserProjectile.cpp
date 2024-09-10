int CLaserProjectile::ShieldRepulse(CPlasmaRepulser* shield, float3 shieldPos, float shieldForce, float shieldMaxSpeed)
{
    if (!luaMoveCtrl) {
        const float3 rdir = (pos - shieldPos).Normalize();

        if (rdir.dot(speed) < 0.0f) {
            speed -= (rdir * rdir.dot(speed) * 2.0f);
            dir = speed;
            dir.Normalize();
            return 1;
        }
    }

    return 0;
}