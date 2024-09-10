void drawing_context::move_to(math::vector2f const& point)
{
    path_.moveTo(point.x(), point.y());
}