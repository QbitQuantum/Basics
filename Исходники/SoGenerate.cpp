  static void generate_cone(const float radius,
                            const float height,
                            const int numslices,
                            const unsigned int flags,
                            SoShape * const shape,
                            SoAction * const action) {
    int i;
    int slices = numslices;
    if (slices > 128) slices = 128;
    if (slices < 4) slices = 4;

    float h2 = height * 0.5f;

    // put coordinates on the stack
    SbVec3f coords[129];
    SbVec3f normals[130];
    SbVec2f texcoords[129];

    sogenerate_generate_3d_circle(coords, slices, radius, -h2);
    coords[slices] = coords[0];

    double a = atan(height/radius);
    sogenerate_generate_3d_circle(normals, slices, (float) sin(a), (float) cos(a));
    normals[slices] = normals[0];
    normals[slices+1] = normals[1];

    int matnr = 0;

    SoPrimitiveVertex vertex;
    SoConeDetail sideDetail;
    SoConeDetail bottomDetail;
    sideDetail.setPart(SoCone::SIDES);
    bottomDetail.setPart(SoCone::BOTTOM);

    // FIXME: the texture coordinate generation for cone sides is of
    // sub-par quality. The textures comes out looking "skewed" and
    // "compressed". 20010926 mortene.

    if (flags & SOGEN_GENERATE_SIDE) {
      vertex.setDetail(&sideDetail);
      vertex.setMaterialIndex(matnr);

      shape->beginShape(action, SoShape::TRIANGLES);
      i = 0;

      float t = 1.0;
      float delta = 1.0f / slices;

      while (i < slices) {
        vertex.setTextureCoords(SbVec2f(t - delta*0.5f, 1.0f));
        vertex.setNormal((normals[i] + normals[i+1])*0.5f);
        vertex.setPoint(SbVec3f(0.0f, h2, 0.0f));
        shape->shapeVertex(&vertex);

        vertex.setTextureCoords(SbVec2f(t, 0.0f));
        vertex.setNormal(normals[i]);
        vertex.setPoint(coords[i]);
        shape->shapeVertex(&vertex);

        vertex.setTextureCoords(SbVec2f(t-delta, 0.0f));
        vertex.setNormal(normals[i+1]);
        vertex.setPoint(coords[i+1]);
        shape->shapeVertex(&vertex);

        i++;
        t -= delta;
      }
      if (flags & SOGEN_MATERIAL_PER_PART) matnr++;
      shape->endShape();
    }

    if (flags & SOGEN_GENERATE_BOTTOM) {
      vertex.setDetail(&bottomDetail);
      vertex.setMaterialIndex(matnr);

      sogenerate_generate_2d_circle(texcoords, slices, 0.5f);
      texcoords[slices] = texcoords[0];

      shape->beginShape(action, SoShape::TRIANGLE_FAN);
      vertex.setNormal(SbVec3f(0.0f, -1.0f, 0.0f));
      for (i = slices-1; i >= 0; i--) {
        vertex.setTextureCoords(texcoords[i]+SbVec2f(0.5f, 0.5f));
        vertex.setPoint(coords[i]);
        shape->shapeVertex(&vertex);
      }
      shape->endShape();
    }
  }