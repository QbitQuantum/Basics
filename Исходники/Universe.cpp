/** Determine the closest object intersected by a ray given by the pick origin and direction.
  * This method returns true if any object was intersected. If the value of result is not
  * null, it will be updated with information about which object was hit by the pick ray.
  *
  * @param t The time given as the number of seconds since 1 Jan 2000 12:00:00 UTC.
  * @param pickOrigin origin of the pick ray
  * @param pickDirection direction of the pick ray (does not need to be normalized)
  * @param pixelAngle angle in radians subtended by a pixel
  * @param result pointer to a PickResult object that will be filled in if the pick ray
  *    hits something.
  */
bool
Universe::pickObject(double t,
                     const Vector3d& pickOrigin,
                     const Vector3d& pickDirection,
                     double pixelAngle,
                     PickResult* result) const
{
    double closest = numeric_limits<double>::infinity();
    PickResult closestResult;

    for (EntityTable::const_iterator iter = m_entities.begin(); iter != m_entities.end(); ++iter)
    {
        Entity* entity = iter->ptr();

        if (entity->geometry() || entity->hasVisualizers())
        {
            if (entity->isVisible() && entity->chronology()->includesTime(t))
            {
                Vector3d position = entity->position(t);

                if (entity->geometry())
                {
                    Geometry* geometry = entity->geometry();
                    double intersectionDistance;
                    if (TestRaySphereIntersection(pickOrigin,
                                                  pickDirection,
                                                  position,
                                                  geometry->boundingSphereRadius(),
                                                  &intersectionDistance))
                    {
                        if (intersectionDistance < closest)
                        {
                            // Transform the pick ray into the local coordinate system of body
                            Matrix3d invRotation = entity->orientation(t).conjugate().toRotationMatrix();
                            Vector3d relativePickOrigin = invRotation * (pickOrigin - position);
                            Vector3d relativePickDirection = invRotation * pickDirection;

                            double distance = intersectionDistance;
                            if (geometry->rayPick(relativePickOrigin, relativePickDirection, t, &distance))
                            {
                                if (distance < closest)
                                {
                                    closest = distance;
                                    closestResult.setHit(entity, distance, pickOrigin + pickDirection * distance);
                                }
                            }
                        }
                    }
                }

                // Visualizers may act as 'pick proxies'
                if (entity->hasVisualizers())
                {
                    Vector3d relativePickOrigin = pickOrigin - position;

                    // Calculate the distance to the plane containing the center of the visualizer
                    // and perpendicular to the pick direction.
                    double distanceToPlane = -pickDirection.dot(relativePickOrigin);

                    if (distanceToPlane > 0.0 && distanceToPlane < closest)
                    {
                        for (Entity::VisualizerTable::const_iterator iter = entity->visualizers()->begin();
                             iter != entity->visualizers()->end(); ++iter)
                        {
                            const Visualizer* visualizer = iter->second.ptr();
                            if (visualizer->isVisible() &&
                                visualizer->rayPick(relativePickOrigin, pickDirection, pixelAngle))
                            {
                                closest = distanceToPlane;
                                closestResult.setHit(entity, distanceToPlane, pickOrigin + pickDirection * distanceToPlane);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    if (closest < numeric_limits<double>::infinity())
    {
        if (result)
        {
            *result = closestResult;
        }
        return true;
    }
    else
    {
        return false;
    }
}