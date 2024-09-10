bool Form::projectPoint(int x, int y, Vector3* point)
{
    Scene* scene = _node->getScene();
    GP_ASSERT(scene);
    Camera* camera = scene->getActiveCamera();

    if (camera)
    {
        // Get info about the form's position.
        Matrix m = _node->getMatrix();
        Vector3 min(0, 0, 0);
        m.transformPoint(&min);

        // Unproject point into world space.
        Ray ray;
        camera->pickRay(Game::getInstance()->getViewport(), x, y, &ray);

        // Find the quad's plane.  We know its normal is the quad's forward vector.
        Vector3 normal = _node->getForwardVectorWorld();

        // To get the plane's distance from the origin, we'll find the distance from the plane defined
        // by the quad's forward vector and one of its points to the plane defined by the same vector and the origin.
        const float& a = normal.x; const float& b = normal.y; const float& c = normal.z;
        const float d = -(a*min.x) - (b*min.y) - (c*min.z);
        const float distance = abs(d) /  sqrt(a*a + b*b + c*c);
        Plane plane(normal, -distance);

        // Check for collision with plane.
        float collisionDistance = ray.intersects(plane);
        if (collisionDistance != Ray::INTERSECTS_NONE)
        {
            // Multiply the ray's direction vector by collision distance and add that to the ray's origin.
            point->set(ray.getOrigin() + collisionDistance*ray.getDirection());

            // Project this point into the plane.
            m.invert();
            m.transformPoint(point);

            return true;
        }
    }
    return false;
}