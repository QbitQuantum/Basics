void CollisionSystem::CollideBodies(std::shared_ptr<Entity> entity1,
    std::shared_ptr<Entity> entity2)
{
    LOG_D("[CollisionSystem] Colliding entities: " << entity1->GetId() << " and " << entity2->GetId());

    auto particleComponent1 = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity1, "ParticleComponent"));
    auto particleComponent2 = std::static_pointer_cast<ParticleComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity2, "ParticleComponent"));
    auto colliderComponent1 = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity1, "ColliderComponent"));
    auto colliderComponent2 = std::static_pointer_cast<ColliderComponent>(Engine::GetInstance().GetSingleComponentOfClass(entity2, "ColliderComponent"));
    float radius1 = colliderComponent1->GetRadius();
    float radius2 = colliderComponent2->GetRadius();
    Vector position1 = particleComponent1->GetPosition();
    Vector position2 = particleComponent2->GetPosition();
    float distance = position1.CalculateDistance(position2);
    float difference = radius1 + radius2 - distance;

    Vector direction = position2 - position1;
    direction.Normalize();

    // Applying force contrary to the collision direction. This force should
    // depend on the energy of the collision
    float forceMag = 100;
    Vector force1 = direction*(-forceMag);
    Vector force2 = direction*(forceMag);

    particleComponent1->SetForce(force1);
    particleComponent2->SetForce(force2);
    
    // Avoiding overlapping
    position1 += direction*(-difference/2);
    position2 += direction*(difference/2);

    particleComponent1->SetPosition(position1);
    particleComponent2->SetPosition(position2);
}