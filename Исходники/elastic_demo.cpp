/* This function updates the forces that act on each vertex due to the elasticity
 * of the mesh. You DO NOT need to understand what is going on in this function
 * (though you are free to explore it for extra credit). Once this function is
 * called, each vertex in vertices will have their fx and fy fields with the
 * correct forces for the next time step. The potential energy variable, pe,
 * is also updated.
 */
void updateforces(int index)
{
    Triangle t = triangles[index];

    MatrixXd ds(2, 2);
    ds << vertices[t.p1].x - vertices[t.p3].x, vertices[t.p2].x - vertices[t.p3].x,
    vertices[t.p1].y - vertices[t.p3].y, vertices[t.p2].y - vertices[t.p3].y;

    MatrixXd dminverse = (restmats[index]).inverse();
    MatrixXd f = ds * dminverse;
    MatrixXd finvt = (f.inverse()).transpose();

    float i1 = (f.transpose() * f).trace();
    float j = f(0,0) * f(1,1) - f(1,0) * f(0,1);

    MatrixXd p = f - finvt + 1.0 / 2.0 * log(j * j) * finvt;
    MatrixXd h = -t.restarea * p * dminverse.transpose();

    vertices[t.p1].fx += h(0,0);
    vertices[t.p2].fx += h(0,1);
    vertices[t.p3].fx += -h(0,0) - h(0,1);

    vertices[t.p1].fy += h(1,0);
    vertices[t.p2].fy += h(1,1);
    vertices[t.p3].fy += -h(1,0) - h(1,1);

    pe += t.restarea * ( (i1 - 2) - log(j) + 1.0 / 2.0 * log(j) * log(j) );
}