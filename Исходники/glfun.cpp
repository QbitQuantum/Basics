void TGLFunWidget::drawPredicate(void)
{
    Float x0 = (maxX + minX)*0.5,
          y0 = (maxY + minY)*0.5,
          z0 = (maxZ + minZ)*0.5;

    glPointSize(4);
    glBegin(GL_POINTS);
    for (unsigned i = 0; i < mesh->getX().size(); i++)
        if (fabsl((*results)[funIndex].getResults(i) > predicate.toFloat()))
        {
            if ((*results)[funIndex].getResults(i) > 0)
                glColor3b(1,0,0);
            else
                glColor3b(0,0,1);
            glVertex3f(cX(i) - x0, (mesh->getY().size()) ? cY(i) - y0 : 0, (mesh->getZ().size()) ? cZ(i) - z0 : 0);
        }
    glEnd();

}