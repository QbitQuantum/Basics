void ParticleBungee::updateForce(Particle *particle, real duration) {
    // Calculate the vector of the spring
    Vector2D force;
    particle->getPosition(&force);
    force -= other->getPosition();

    // Check if the bungee is compressed
    real magnitude = force.magnitude();
    if (magnitude <= restLength) return;

    // Calculate the magnitude of the force
    magnitude = springConstant * (restLength - magnitude);

    // Calculate the final force and apply it
    force.normalize();
    force *= -magnitude;
    particle->addForce(force);
}