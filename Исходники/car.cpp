void Car::update(const sf::Time & _time) {
    
    // keep location as last valid
    if (!this->mDriftedOffTrack) {
        this->mCurrentPassedDistance += length(this->mCurrentLocation - this->mLastLocation);
        this->mLastLocation = this->mCurrentLocation;
        
       // std::cout << "Passed Distance: " << this->mCurrentPassedDistance << std::endl;
    }
    
    // compute cars offset to the track segment and adjust it
    sf::Vector2f proj = project(this->mCurrentLocation, this->mTrack[this->mSegmentStart], this->mTrack[this->mSegmentEnd]);
    sf::Vector2f positionAdjust = proj - this->mCurrentLocation;
   
    // apply drag friction
    if (this->mVelocity > 0.0f) {
       // this->mForce -= abs(Car::FRICTION_FORCE * (this->mVelocity) * (this->mDriftedOffTrack ? Car::DRAG_FRICTION_OFF_TRACK : Car::DRAG_FRICTION_ON_TRACK));
        this->mForce -= abs(Car::FRICTION_FORCE * (this->mVelocity));
        this->mForce -= abs(this->mIsAccelerating ? 0.0f : Car::BREAK_FRICTION * this->mVelocity);
        this->mForce -= abs(!this->mDriftedOffTrack ? 0.0f : Car::DRAG_FRICTION_OFF_TRACK * this->mVelocity);
        
        this->mIsAccelerating = false;
    }
    
    // compute acceleration A = F / M
    float acceleration = this->mForce / Car::DEFAULT_MASS;
    
    // compute velocity
    this->mVelocity += acceleration * _time.asSeconds();
    this->mVelocity = fmax(fmin(this->mVelocity, Car::MAX_VELOCITY), 0.0f);
    //std::cout << "Velocity: " << this->mVelocity << std::endl;
        
    // compute new position
    this->mCurrentLocation += this->mCurrentDirection * (this->mVelocity * _time.asSeconds());
    this->mCurrentLocation += positionAdjust;
    
    this->keepOnTrack();
    this->updateGhosts();
    
    // compute rotation
    float angle = heading(this->mCurrentDirection);
    
    this->mCarDrawable.setRotation(RAD_TO_DEG(angle));
    this->mCarDrawable.setPosition(this->mCurrentLocation);
    
    // debug stuff
    this->mLocationPoint.setPosition(this->mCurrentLocation);
    this->mDirectionShape.setPosition(this->mCurrentLocation);
}