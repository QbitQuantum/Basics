void TileMapLayer2D::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (!debug)
        return;

    if (objectGroup_)
    {
        const Matrix3x4 transform = GetTileMap()->GetNode()->GetTransform();
        for (unsigned i = 0; i < objectGroup_->GetNumObjects(); ++i)
        {
            TileMapObject2D* object = objectGroup_->GetObject(i);
            const Color& color = Color::YELLOW;
            const Vector2& size = object->GetSize();
            const TileMapInfo2D& info = tileMap_->GetInfo();


            switch (object->GetObjectType())
            {
            case OT_RECTANGLE:
                {
                    Vector<Vector2> points;

                    switch (info.orientation_)
                    {
                    case O_ORTHOGONAL:
                    case O_HEXAGONAL:
                    case O_STAGGERED:
                        {
                            points.Push(Vector2::ZERO);
                            points.Push(Vector2(size.x_, 0.0f));
                            points.Push(Vector2(size.x_, -size.y_));
                            points.Push(Vector2(0.0f, -size.y_));
                            break;
                        }
                    case O_ISOMETRIC:
                        {
                            float ratio = (info.tileWidth_ / info.tileHeight_) * 0.5f;
                            points.Push(Vector2::ZERO);
                            points.Push(Vector2(size.y_ * ratio, size.y_ * 0.5f));
                            points.Push(Vector2((size.x_ + size.y_) * ratio, (-size.x_ + size.y_) * 0.5f));
                            points.Push(Vector2(size.x_ * ratio, -size.x_ * 0.5f));
                            break;
                        }
                    }

                    for (unsigned j = 0; j < points.Size(); ++j)
                        debug->AddLine(Vector3(TransformNode2D(transform, points[j] + object->GetPosition())),
                            Vector3(TransformNode2D(transform, points[(j + 1) % points.Size()] + object->GetPosition())), color,
                            depthTest);
                }
                break;

            case OT_ELLIPSE:
                {
                    const Vector2 halfSize = object->GetSize() * 0.5f;
                    float ratio = (info.tileWidth_ / info.tileHeight_) * 0.5f; // For isometric only

                    Vector2 pivot = object->GetPosition();
                    if (info.orientation_ == O_ISOMETRIC)
                    {
                        pivot += Vector2((halfSize.x_ + halfSize.y_) * ratio, (-halfSize.x_ + halfSize.y_) * 0.5f);
                    }
                    else
                    {
                        pivot += halfSize;
                    }

                    for (unsigned i = 0; i < 360; i += 30)
                    {
                        unsigned j = i + 30;
                        float x1 = halfSize.x_ * Cos((float)i);
                        float y1 = halfSize.y_ * Sin((float)i);
                        float x2 = halfSize.x_ * Cos((float)j);
                        float y2 = halfSize.y_ * Sin((float)j);
                        Vector2 point1 = Vector2(x1, - y1);
                        Vector2 point2 = Vector2(x2, - y2);

                        if (info.orientation_ == O_ISOMETRIC)
                        {
                            point1 = Vector2((point1.x_ + point1.y_) * ratio, (point1.y_ - point1.x_) * 0.5f);
                            point2 = Vector2((point2.x_ + point2.y_) * ratio, (point2.y_ - point2.x_) * 0.5f);
                        }

                        debug->AddLine(Vector3(TransformNode2D(transform, pivot + point1)),
                            Vector3(TransformNode2D(transform, pivot + point2)), color, depthTest);
                    }
                }
                break;

            case OT_POLYGON:
            case OT_POLYLINE:
                {
                    for (unsigned j = 0; j < object->GetNumPoints() - 1; ++j)
                        debug->AddLine(Vector3(TransformNode2D(transform, object->GetPoint(j))),
                            Vector3(TransformNode2D(transform, object->GetPoint(j + 1))), color, depthTest);

                    if (object->GetObjectType() == OT_POLYGON)
                        debug->AddLine(Vector3(TransformNode2D(transform, object->GetPoint(0))),
                            Vector3(TransformNode2D(transform, object->GetPoint(object->GetNumPoints() - 1))), color, depthTest);
                    // Also draw a circle at origin to indicate direction
                    else
                        debug->AddCircle(Vector3(TransformNode2D(transform, object->GetPoint(0))), Vector3::FORWARD, 0.05f, color,
                            64, depthTest);
                }
                break;

            default: break;
            }
        }
    }
}