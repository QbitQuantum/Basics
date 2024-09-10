const Transform2 slerp(const Transform2& a, const Transform2& b, const float t)
{
    GEOMETRY_RUNTIME_ASSERT(a.scaling > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.scaling > 0.0f);

    return Transform2(
        mix(a.translation, b.translation, t),
        slerp(a.rotation, b.rotation, t),
        Math::mix(a.scaling, b.scaling, t)
    );
}