void CubeObj::drawgl(GLWidget &gl, QMatrix4x4 & cameramat  ) {

    QMatrix4x4 mobj = cameramat;

    mobj *= getMatrix();
    mobj.scale(scale);

    static  QColor color ( 1.0f, 0, 0.5f, 1 );

    QGLShaderProgram * sp = gl.program;

    if ( pro.actualobject == this ) {
        sp = gl.program2;
    }

    for ( int i=0; i <6; i++) {

        sp->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
        sp->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
        sp->setAttributeArray   (PROGRAM_VERTEX_ATTRIBUTE, vertices.constData());
        sp->setAttributeArray   (PROGRAM_TEXCOORD_ATTRIBUTE, texCoords.constData());
        sp->bind();
        sp->setUniformValue("matrix", mobj);
        sp->setUniformValue("color", QVector4D (1,0,0,0.2f));
        gl.glBindTexture(GL_TEXTURE_2D, this->textureIDs[i] );
        gl.glDrawArrays(GL_QUADS, i*4, 4 );
    }


    if ( pro.getManger().edges ) {
        gl.glDisable(GL_CULL_FACE);
        sp = gl.solidcolorp;

        sp->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
        sp->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
        sp->setAttributeArray   (PROGRAM_VERTEX_ATTRIBUTE, vertices.constData());
        sp->setAttributeArray   (PROGRAM_TEXCOORD_ATTRIBUTE, texCoords.constData());
        sp->bind();
        sp->setUniformValue("matrix", mobj);
        sp->setUniformValue("color", QVector4D (0,1,0,0.8f));

        if ( pro.actualobject == this ) {
            sp->setUniformValue("color", QVector4D (1,0.8f,1,0.8f));
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        gl.glLineWidth(2);
        gl.glDrawArrays(GL_QUADS, 0, 24 );
        gl.glEnable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

}