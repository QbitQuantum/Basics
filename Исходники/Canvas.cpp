Vertex
Canvas::project(const Vertex &v, const Matrix &transform) const {
    Vector p = transform.transform(v.position);
    
    p.x = p.x * _width + _width / 2;
    p.y = -p.y * _height + _height / 2;

    return Vertex(p, v.normal, v.u, v.v, v.color);
}