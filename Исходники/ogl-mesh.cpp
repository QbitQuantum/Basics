void ogl::mesh::cache_verts(const ogl::mesh *that, const mat4& M,
                                                   const mat4& I, int id)
{
    const size_t n = that->vv.size();

    // Cache that mesh's transformed vertices here.  Update bounding volume.

    vv.resize(n);
    nv.resize(n);
    tv.resize(n);
    uv.resize(n);

    bound = aabb();

    for (size_t i = 0; i < n; ++i)
    {
        transform_vertex(vv[i].v,           M,  that->vv[i].v);
        transform_normal(nv[i].v, transpose(I), that->nv[i].v);
        transform_normal(tv[i].v, transpose(I), that->tv[i].v);

        bound.merge(vec3(double(vv[i].v[0]),
                         double(vv[i].v[1]),
                         double(vv[i].v[2])));

        // Handy trick: Store the unit ID in the texture coordinate.

        uv[i].v[0] = that->uv[i].v[0];
        uv[i].v[1] = that->uv[i].v[1];
        uv[i].v[2] = GLfloat(id);
    }

    dirty_verts = true;
}