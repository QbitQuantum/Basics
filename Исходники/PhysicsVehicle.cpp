void PhysicsVehicle::initialize()
{
    GP_ASSERT(getNode());

    // Safe default values
    setSteeringGain(0.5f);
    setBrakingForce(350.0f);
    setDrivingForce(2000.0f);
    setSteerdown(0, 1);
    setBrakedown(1000, 0);
    setDrivedown(1000, 0);
    setBoost(0, 1);
    setDownforce(0);

    // Create the vehicle and add it to world
    btRigidBody* body = static_cast<btRigidBody*>(_rigidBody->getCollisionObject());
    btDynamicsWorld* dynamicsWorld = Game::getInstance()->getPhysicsController()->_world;
    _vehicleRaycaster = new VehicleNotMeRaycaster(dynamicsWorld, body);
    _vehicle = bullet_new<btRaycastVehicle>(_vehicleTuning, body, _vehicleRaycaster);
    body->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addVehicle(_vehicle);
    _vehicle->setCoordinateSystem(0, 1, 2);

    // Advertise self among ancestor nodes so that wheels can bind to self.
    // See PhysicsVehicleWheel and Node for more details.
    for (Node* n = getNode()->getParent(); n; n = n->getParent())
    {
        n->addAdvertisedDescendant(getNode());
    }
}