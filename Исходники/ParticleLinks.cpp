unsigned ParticleCableConstraint::addContact(ParticleContact * _contact, unsigned _limit) const
{
    // find the length of the cable
    real length = this->currentLength();
    
    // check if we're over-extended
    if (length < this->maxLength) {
        return 0;
    }
    
    // otherwise return the contact
    _contact->particle[0] = this->particle;
    _contact->particle[1] = 0;
    
    // calculate the normal
    Vector3 normal = this->anchor - particle->getPosition();
    normal.normalize();
    _contact->contactNormal = normal;
    
    _contact->penetration = length - this->maxLength;
    _contact->restitution = this->restitution;
    
    return 1;
}