inline void vertex_buffer_object<Ta, Te>::update()
{
    updateVertices();
    updateNormals();
    updateColors();
    updateTexCoords();
    updateElements();
}