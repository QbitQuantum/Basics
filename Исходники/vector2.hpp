 inline Vector2 project(const Vector2& other) const { return other * (dot(other) / other.dot(other)); }