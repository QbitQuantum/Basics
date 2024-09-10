static void getArrowVertices(Vector2x position, Vector3x normal, struct vertex_p2f_c4f * outVertices, GLuint * outIndexes, unsigned int * ioVertexCount, unsigned int * ioIndexCount) {
    if (outVertices != NULL) {
        struct vertex_p2f_c4f vertex;
        Vector2f positionf = VECTOR2f(xtof(position.x), xtof(position.y));
        Vector2f normalf = VECTOR2f(xtof(normal.x), xtof(normal.y));

        vertex.color[0] = 1.0f;
        vertex.color[1] = 0.0f;
        vertex.color[2] = 0.0f;
        vertex.color[3] = 1.0f;
        vertex.position[0] = positionf.x - normalf.x * ARROW_RADIUS;
        vertex.position[1] = positionf.y - normalf.y * ARROW_RADIUS;
        outVertices[*ioVertexCount + 0] = vertex;
        vertex.position[0] = positionf.x + normalf.x * ARROW_RADIUS;
        vertex.position[1] = positionf.y + normalf.y * ARROW_RADIUS;
        outVertices[*ioVertexCount + 1] = vertex;
        vertex.position[0] = positionf.x + normalf.y * ARROW_RADIUS * 0.5f;
        vertex.position[1] = positionf.y - normalf.x * ARROW_RADIUS * 0.5f;
        outVertices[*ioVertexCount + 2] = vertex;
        vertex.position[0] = positionf.x - normalf.y * ARROW_RADIUS * 0.5f;
        vertex.position[1] = positionf.y + normalf.x * ARROW_RADIUS * 0.5f;
        outVertices[*ioVertexCount + 3] = vertex;
    }

    if (outIndexes != NULL) {
        outIndexes[*ioIndexCount + 0] = *ioVertexCount + 0;
        outIndexes[*ioIndexCount + 1] = *ioVertexCount + 1;
        outIndexes[*ioIndexCount + 2] = *ioVertexCount + 1;
        outIndexes[*ioIndexCount + 3] = *ioVertexCount + 2;
        outIndexes[*ioIndexCount + 4] = *ioVertexCount + 1;
        outIndexes[*ioIndexCount + 5] = *ioVertexCount + 3;
    }

    *ioVertexCount += 4;
    *ioIndexCount += 6;
}