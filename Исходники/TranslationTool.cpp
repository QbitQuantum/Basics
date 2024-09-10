    void TranslationTool::ImpulseBegin(const Ray& ray) {
        UpdateScale();

        Vector3f position = transformable->GetPosition();
        Matrix transform = Matrix::CreateScale(Vector3f(scale)) * Matrix::CreateTranslation(position);
        BoundingBox xBox = BoundingBox::Transform(xAxisBBox, transform);    
        BoundingBox yBox = BoundingBox::Transform(yAxisBBox, transform);
        BoundingBox zBox = BoundingBox::Transform(zAxisBBox, transform);

        F32 distance;
        if (ray.Intersects(xBox, &distance)) {
            if (ray.Intersects(Plane(Vector3f::Up, -position.y), &distance)) {
                type = XAxis;
                prevPoint = ray.GetOrigin() + ray.GetDirection() * distance;
            }
        } else if (ray.Intersects(yBox, &distance)) {
            if (ray.Intersects(Plane(Vector3f::Backward, -position.z), &distance)) {
                type = YAxis;
                prevPoint = ray.GetOrigin() + ray.GetDirection() * distance;
            }
        } else if (ray.Intersects(zBox, &distance)) {
            if (ray.Intersects(Plane(Vector3f::Right, -position.x), &distance)) {
                type = ZAxis;
                prevPoint = ray.GetOrigin() + ray.GetDirection() * distance;
            }
        }
    }