void GLRender()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//清除的颜色和深度缓冲区
    glLoadIdentity();//把当前矩阵设置为单位矩阵，因为绝大多数变换把当前矩阵与指定的矩阵相乘

    //glTranslatef(0.0f,0.0f,-20.0f);

    gluLookAt(10.0f,10.0f,10.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);

    /*可以参考红宝书中1-3程序double.c，你需要调用一个设定颜色填充模式的函数glPolygonMode*/

    if(ok)
    {
        glPushMatrix();
        glScalef(cubeScale,cubeScale,cubeScale);
        glTranslatef(tx,ty,0);
        glRotatef(rot,vx,vy,vz);//向量(vx,vy.vz)旋转rot角
        //	glBegin();
        GLDrawQuads(cubeVerIndex[12],12);
        GLDrawQuads(cubeVerIndex[13],13);
        GLDrawQuads(cubeVerIndex[14],14);
        GLDrawQuads(cubeVerIndex[15],15);
        GLDrawQuads(cubeVerIndex[16],16);
        GLDrawQuads(cubeVerIndex[17],17);
        GLDrawQuads(cubeVerIndex[18],18);
        GLDrawQuads(cubeVerIndex[19],19);
        GLDrawQuads(cubeVerIndex[20],20);
        GLDrawQuads(cubeVerIndex[21],21);
        GLDrawQuads(cubeVerIndex[22],22);
        GLDrawQuads(cubeVerIndex[23],23);
        //glEnd();
        glPopMatrix();
    }


    vx=sin(theta)*cos(miu);
    vy=cos(theta);
    vz=sin(theta)*sin(miu);

    glPushMatrix();//存放当前的变换矩阵
    glBegin(GL_LINES);//开始画x、y、z三个坐标轴

    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(5.0f,0.0f,0.0f);

    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(0.0f,5.0f,0.0f);

    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(0.0f,0.0f,5.0f);
    glEnd();//把当前的矩阵从堆栈里清出去
    glPopMatrix();//恢复到开始的变换矩阵，避免连环变换的情况


    glColor3f(1.0f,1.0f,1.0f);//指定即将要画的图形的颜色（准确地说是顶点的颜色）

    glPushMatrix();
    glScalef(cubeScale,cubeScale,cubeScale);
    glBegin(GL_LINES);
    glVertex3f(-10.0f*vx,-10.0f*vy,-10.0f*vz);//方向为（vx,vy,vz）轴
    glVertex3f(10.0f*vx,10.0f*vy,10.0f*vz);
    glEnd();
    glPopMatrix();


    if(gWireMode)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    else
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


    glPushMatrix();
    glTranslatef(tx,ty,0);
    glRotatef(rot,vx,vy,vz);//向量(vx,vy.vz)旋转rot角
    glMultMatrixd(cubeMatrix);
    glScalef(cubeScale,cubeScale,cubeScale);
    GLDrawCube();
    glPopMatrix();


    static signed __int64 lastTickCount=GetTickCount();
    signed __int64 TickCount=GetTickCount();
    float dt=(TickCount-lastTickCount)/1000.0f;
    lastTickCount=TickCount;

    GLProcessKey(dt);
    GLProcessMouse(dt);
    if(rot>=360.0f)rot-=360.0f;
    /***************************************************************************GLRender中需要你们实现的部分至此结束********************************************************************/

    glFlush();															//强制刷新缓冲区的函数，如果去掉呢？
    glutSwapBuffers();													//交换使用另一个缓冲区，为什么要交换呢？原理在红宝书第一章动画那一节里有阐述
}