void AxisRenderer::drawGrid(int gridSize, QGLShaderProgram &program,const AxisCamera &camera)
{
    qDebug()<< "[AxisRender] Drawing Grid";

    int gridNumber = camera.getGridFactor() * 2; //double size of grid to ensure it covers entire view
    float lineLimit = gridNumber * gridSize; //bounds of grid for this size and number

    qDebug()<< "[AxisRender] lineLimit = " << lineLimit;

    //general xline for grid
    float lineX[] = {lineLimit, 0.0f, 0.0f, 1.0f,
                     -lineLimit, 0.0f, 0.0f, 1.0f};

    //general yline for grid
    float lineY[] = { 0.0f, lineLimit, 0.0f, 1.0f,
                    0.0f, -lineLimit, 0.0f, 1.0f};

    //general zline for grid
    float lineZ[] = {0.0f, 0.0f, lineLimit, 1.0f,
                    0.0f, 0.0f, -lineLimit, 1.0f};

    //bind and fill xline buffer
    program.bind();
    QGLBuffer bufferX(QGLBuffer::VertexBuffer);
    bufferX.setUsagePattern(QGLBuffer::StaticDraw);
    bufferX.create();
    bufferX.bind();
    bufferX.allocate(lineX,sizeof(lineX));

    //bind and fill yline buffer
    QGLBuffer bufferY(QGLBuffer::VertexBuffer);
    bufferY.setUsagePattern(QGLBuffer::StaticDraw);
    bufferY.create();
    bufferY.bind();
    bufferY.allocate(lineY, sizeof(lineY));

    //bind and fill zline buffer
    QGLBuffer bufferZ(QGLBuffer::VertexBuffer);
    bufferZ.setUsagePattern(QGLBuffer::StaticDraw);
    bufferZ.create();
    bufferZ.bind();
    bufferZ.allocate(lineZ, sizeof(lineZ));

    QMatrix4x4 mvp;
    QMatrix4x4 vp = camera.getProjMatrix();
    QMatrix4x4 m;

    //find the offest based on camera position
    QVector3D pos = camera.getPosistion();
    int xoff = pos.x() / gridSize;
    int yoff = pos.y() / gridSize;
    int zoff = pos.z() / gridSize;

    //set color uniform to grey
    QVector4D color(0.3f, 0.3f, 0.3f, 1.0f);
    program.setUniformValueArray("color", &color, 1);

    //draw each line
    program.enableAttributeArray("vertex");
    for(int i = -gridNumber; i <= gridNumber; ++i){
        //x lines only for XY and XZ Axis
        if(camera.getLock() == XY || camera.getLock() == XZ)
        {
            bufferX.bind();
            program.setAttributeBuffer("vertex", GL_FLOAT, 0, 4);

            //use model matrix to translate each line with offset
            m.setToIdentity();
            m.translate(0.0f + (xoff * gridSize), (i + yoff) * gridSize, (i + zoff) * gridSize);

            mvp = vp * m ;//set mvp up

            //set mvp uniform then draw
            program.setUniformValueArray("modelToCamera", &mvp, 1);
            glDrawArrays(GL_LINES, 0, 2);
        }

        //y lines for XY and YZ axis only
        if(camera.getLock() == XY || camera.getLock() == YZ)
        {
            bufferY.bind();
            program.setAttributeBuffer("vertex", GL_FLOAT, 0, 4);

            //use model matrix to translate each line with offset
            m.setToIdentity();
            m.translate((i + xoff) * gridSize, 0.0f + (yoff * gridSize) ,(i + zoff) * gridSize);
            mvp = vp * m;

            //set mvp uniform and draw
            program.setUniformValueArray("modelToCamera", &mvp, 1);
            glDrawArrays(GL_LINES, 0, 2);
        }

        //z lines
        if(camera.getLock() == XZ || camera.getLock() == YZ)
        {
            bufferZ.bind();
            program.setAttributeBuffer("vertex", GL_FLOAT, 0, 4);

            //use model matrix to translate each line with offset
            m.setToIdentity();
            m.translate((i + xoff) * gridSize, (i + yoff) * gridSize ,0.0f + (zoff * gridSize));
            mvp = vp * m;

            //set mvp uniform then draw
            program.setUniformValueArray("modelToCamera", &mvp, 1);
            glDrawArrays(GL_LINES, 0, 2);
        }
    }
}