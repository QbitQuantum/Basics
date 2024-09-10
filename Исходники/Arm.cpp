void Arm::update( const Vec2f &mouse ) {
    for ( auto& component : FullArm ) {
        component->update();
    }
    
    if ( mouse.x != 0 && mouse.y != 0 ) {
        // FullArm[3]->getBody()->SetTransform( Conversions::toPhysics( mouse ), 0.0f );
        Vec2f diff = mouse - Conversions::toScreen( FullArm[3]->getBody()->GetPosition() );
        diff.normalize();
        diff *= 20000.0f;
        FullArm[3]->getBody()->ApplyForce( Conversions::toPhysics( diff ), FullArm[3]->getBody()->GetPosition() );
    }
}