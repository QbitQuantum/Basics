void OpenGLVideoPrivate::bindAttributes(VideoShader* shader, const QRectF &t, const QRectF &r)
{
    const bool tex_rect = shader->textureTarget() == GL_TEXTURE_RECTANGLE;
    // also check size change for normalizedROI computation if roi is not normalized
    const bool roi_changed = valiad_tex_width != material->validTextureWidth() || roi != r || video_size != material->frameSize();
    const int tc = shader->textureLocationCount();
    if (roi_changed) {
        roi = r;
        valiad_tex_width = material->validTextureWidth();
        video_size = material->frameSize();
    }
    if (tex_target != shader->textureTarget()) {
        tex_target = shader->textureTarget();
        update_geo = true;
    }
    QRectF& target_rect = rect;
    if (target.isValid()) {
        if (roi_changed || target != t) {
            target = t;
            update_geo = true;
        }
    } else {
        if (roi_changed) {
            update_geo = true;
        }
    }
    if (!update_geo)
        goto end;
    //qDebug("updating geometry...");
    geometry.setRect(target_rect, material->mapToTexture(0, roi));
    if (tex_rect) {
        geometry.setTextureCount(tc);
        for (int i = 1; i < tc; ++i) {
            // tc can > planes, but that will compute chroma plane
            geometry.setTextureRect(material->mapToTexture(i, roi), i);
        }
    }
    update_geo = false;
    if (!try_vbo)
        goto end;
    { //VAO scope BEGIN
#if QT_VAO
    if (try_vao) {
        //qDebug("updating vao...");
        if (!vao.isCreated()) {
            if (!vao.create()) {
                try_vao = false;
                qDebug("VAO is not supported");
            }
        }
    }
    QOpenGLVertexArrayObject::Binder vao_bind(&vao);
    Q_UNUSED(vao_bind);
#endif
    if (!vbo.isCreated()) {
        if (!vbo.create()) {
            try_vbo = false; // not supported by OpenGL
            try_vao = false; // also disable VAO. destroy?
            qWarning("VBO is not supported");
            goto end;
        }
    }
    //qDebug("updating vbo...");
    vbo.bind(); //check here
    vbo.allocate(geometry.data(), geometry.size());
#if QT_VAO
    if (try_vao) {
        shader->program()->setAttributeBuffer(0, GL_FLOAT, 0, geometry.tupleSize(), geometry.stride());
        shader->program()->setAttributeBuffer(1, GL_FLOAT, geometry.tupleSize()*sizeof(float), geometry.tupleSize(), geometry.stride());
        if (tex_rect) {
            for (int i = 1; i < tc; ++i) {
                shader->program()->setAttributeBuffer(i + 1, GL_FLOAT, i*geometry.textureSize() + geometry.tupleSize()*sizeof(float), geometry.tupleSize(), geometry.stride());
            }
        }
        char const *const *attr = shader->attributeNames();
        for (int i = 0; attr[i]; ++i) {
            shader->program()->enableAttributeArray(i); //TODO: in setActiveShader
        }
    }
#endif
    vbo.release();
    } //VAO scope END
end:
#if QT_VAO
    if (try_vao && vao.isCreated()) {
        vao.bind();
        return;
    }
#endif
    if (try_vbo && vbo.isCreated()) {
        vbo.bind();
        shader->program()->setAttributeBuffer(0, GL_FLOAT, 0, geometry.tupleSize(), geometry.stride());
        shader->program()->setAttributeBuffer(1, GL_FLOAT, geometry.tupleSize()*sizeof(float), geometry.tupleSize(), geometry.stride());
        if (tex_rect) {
            for (int i = 1; i < tc; ++i) {
                shader->program()->setAttributeBuffer(i + 1, GL_FLOAT, i*geometry.textureSize() + geometry.tupleSize()*sizeof(float), geometry.tupleSize(), geometry.stride());
            }
        }
    } else {
        shader->program()->setAttributeArray(0, GL_FLOAT, geometry.data(0), geometry.tupleSize(), geometry.stride());
        shader->program()->setAttributeArray(1, GL_FLOAT, geometry.data(1), geometry.tupleSize(), geometry.stride());
        if (tex_rect) {
            for (int i = 1; i < tc; ++i) {
                shader->program()->setAttributeArray(i + 1, GL_FLOAT, geometry.data(1), i*geometry.textureSize() + geometry.tupleSize(), geometry.stride());
            }
        }
    }
    char const *const *attr = shader->attributeNames();
    for (int i = 0; attr[i]; ++i) {
        shader->program()->enableAttributeArray(i); //TODO: in setActiveShader
    }
}