void Explosion::UpdateExplosion(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData[Update::P_TIMESTEP].GetFloat();

    rigidBody_->SetMass(Max(initialMass_*((0.1f - age_)/0.1f),0.01f));
    light_->SetBrightness(Max(initialBrightness_*(0.32f - age_)/0.32f,0.0f));

    if (rootNode_->IsEnabled() && masterControl_->world.scene->IsUpdateEnabled()) {
        PODVector<RigidBody* > hitResults;
        float radius = 2.0f * initialMass_ + age_ * 7.0f;
        if (masterControl_->PhysicsSphereCast(hitResults,rootNode_->GetPosition(), radius, M_MAX_UNSIGNED)) {
            for (int i = 0; i < hitResults.Size(); i++) {
                Vector3 hitNodeWorldPos = hitResults[i]->GetNode()->GetWorldPosition();
                if (!hitResults[i]->IsTrigger() && hitResults[i]->GetPosition().y_ > -0.1f) {
                    //positionDelta is used for force calculation
                    Vector3 positionDelta = hitNodeWorldPos - rootNode_->GetWorldPosition();
                    float distance = positionDelta.Length();
                    Vector3 force = positionDelta.Normalized() * Max(radius-distance, 0.0f)
                                    * timeStep * 2342.0f * rigidBody_->GetMass();
                    hitResults[i]->ApplyForce(force);
                    //Deal damage
                    unsigned hitID = hitResults[i]->GetNode()->GetID();
                    float damage = rigidBody_->GetMass()*timeStep;
                    if(masterControl_->spawnMaster_->spires_.Keys().Contains(hitID)) {
                        masterControl_->spawnMaster_->spires_[hitID]->Hit(damage, 1);
                    }
                    else if(masterControl_->spawnMaster_->razors_.Keys().Contains(hitID)) {
                        masterControl_->spawnMaster_->razors_[hitID]->Hit(damage, 1);
                    }
                }
            }
        }
    }
}