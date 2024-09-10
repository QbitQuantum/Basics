//We use a modified Separating Axis Test to test for polygon-circle collisions
bool PolygonBody::checkCollision(CircleBody& circle, Collision& collision) {
    float radiusSum = _radius + circle.radius();
    
    if ((circle.position() - _position).lengthSquared() > radiusSum * radiusSum)
        return false;
    
    std::vector<Vector2f> axes;
    this->calculateNormals(axes);
    
    //We need the axis from the center of the circle to the closest vertex on the polygon
    Vector2f additionalAxis = _verticesWorldSpace[0] - circle.position();
    
    for (size_t i = 1; i < _verticesWorldSpace.size(); ++i) {
        Vector2f v = _verticesWorldSpace[i] - circle.position();
        
        if (v.lengthSquared() < additionalAxis.lengthSquared())
            additionalAxis = v;
    }
    
    additionalAxis.normalize();
    axes.push_back(additionalAxis);
    
    float minOverlap = std::numeric_limits<float>::max();
    Vector2f minOverlapAxis;
    
    for (size_t i = 0; i < axes.size(); ++i) {
        Vector2f& axis = axes[i];
        
        float projection = axis.dotProduct(_verticesWorldSpace.front());
        float aMinProjection = projection;
        float aMaxProjection = projection;
        
        for (size_t j = 1; j < _verticesWorldSpace.size(); ++j) {
            projection = axis.dotProduct(_verticesWorldSpace[j]);
            
            aMinProjection = std::min(aMinProjection, projection);
            aMaxProjection = std::max(aMaxProjection, projection);
        }
        
        projection = axis.dotProduct(circle.position());
        float bMinProjection = projection - circle.radius();
        float bMaxProjection = projection + circle.radius();
        
        if (bMinProjection > bMaxProjection)
            std::swap(bMinProjection, bMaxProjection);
        
        if ((aMaxProjection < bMinProjection) || (bMaxProjection < aMinProjection))
            return false; //This axis has no overlap, a collision is not possible
        
        float lowerOverlap = aMaxProjection - bMinProjection;
        float upperOverlap = bMaxProjection - aMinProjection;
        
        if (lowerOverlap < minOverlap) {
            minOverlap = lowerOverlap;
            minOverlapAxis = axis;
        }
        
        if (upperOverlap < minOverlap) {
            minOverlap = upperOverlap;
            minOverlapAxis = -axis;
        }
    }

    collision.bodyA = this;
    collision.bodyB = &circle;
    collision.normal = minOverlapAxis;
    collision.depth = minOverlap;
    collision.contactPoints.push_back(circle.position() - collision.normal * (circle.radius() - collision.depth));

    return true;
}