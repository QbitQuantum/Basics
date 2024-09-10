void GameObject::updatePosition(sf::Time elapsedTime)
{
    sf::Vector2f acceleration(resultantForce.x / mass, resultantForce.y / mass);

    //calculate velocity
    sf::Vector2f newVelocity = velocity + acceleration*elapsedTime.asSeconds();
    float newVelocityLen = ezo::vecLength(newVelocity.x, newVelocity.y);
    if(newVelocityLen > maxVelocity)
        velocity = {newVelocity.x/newVelocityLen*maxVelocity, newVelocity.y/newVelocityLen*maxVelocity};
    else
        velocity = newVelocity;

    oldPosition = representation.getPosition();
    representation.setPosition(representation.getPosition() + velocity*elapsedTime.asSeconds());
}