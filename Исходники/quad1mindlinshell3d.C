void
Quad1MindlinShell3D :: computeBmatrixAt(GaussPoint *gp, FloatMatrix &answer, int li, int ui)
{
    FloatArray n, ns;
    FloatMatrix dn, dns;
    const FloatArray &localCoords = gp->giveNaturalCoordinates();

    this->interp.evaldNdx( dn, localCoords, FEIVertexListGeometryWrapper(lnodes) );
    this->interp.evalN( n, localCoords,  FEIVoidCellGeometry() );

    answer.resize(8, 4 * 5);
    answer.zero();

    // enforce one-point reduced integration if requested
    if ( this->reducedIntegrationFlag ) {
        FloatArray lc(2);
        lc.zero(); // set to element center coordinates

        this->interp.evaldNdx( dns, lc, FEIVertexListGeometryWrapper(lnodes) );
        this->interp.evalN( ns, lc,  FEIVoidCellGeometry() );
    } else {
        dns = dn;
        ns = n;
    }


    // Note: This is just 5 dofs (sixth column is all zero, torsional stiffness handled separately.)
    for ( int i = 0; i < 4; ++i ) {
        ///@todo Check the rows for both parts here, to be consistent with _3dShell material definition
        // Part related to the membrane (columns represent coefficients for D_u, D_v)
        answer(0, 0 + i * 5) = dn(i, 0);//eps_x = du/dx
        answer(1, 1 + i * 5) = dn(i, 1);//eps_y = dv/dy
        answer(2, 0 + i * 5) = dn(i, 1);//gamma_xy = du/dy+dv/dx
        answer(2, 1 + i * 5) = dn(i, 0);

        // Part related to the plate (columns represent the dofs D_w, R_u, R_v)
        ///@todo Check sign here
        answer(3 + 0, 2 + 2 + i * 5) = dn(i, 0);// kappa_x = d(fi_y)/dx
        answer(3 + 1, 2 + 1 + i * 5) =-dn(i, 1);// kappa_y = -d(fi_x)/dy
        answer(3 + 2, 2 + 2 + i * 5) = dn(i, 1);// kappa_xy=d(fi_y)/dy-d(fi_x)/dx
        answer(3 + 2, 2 + 1 + i * 5) =-dn(i, 0);

        // shear strains
        answer(3 + 3, 2 + 0 + i * 5) = dns(i, 0);// gamma_xz = fi_y+dw/dx
        answer(3 + 3, 2 + 2 + i * 5) = ns(i);
        answer(3 + 4, 2 + 0 + i * 5) = dns(i, 1);// gamma_yz = -fi_x+dw/dy
        answer(3 + 4, 2 + 1 + i * 5) = -ns(i);
    }


#if 0
    // Experimental MITC4 support.
    // Based on "Short communication A four-node plate bending element based on mindling/reissner plate theory and a mixed interpolation"
    // KJ Bathe, E Dvorkin

    double x1, x2, x3, x4;
    double y1, y2, y3, y4;
    double Ax, Bx, Cx, Ay, By, Cy;

    double r = localCoords[0];
    double s = localCoords[1];

    x1 = lnodes[0][0];
    x2 = lnodes[1][0];
    x3 = lnodes[2][0];
    x4 = lnodes[3][0];

    y1 = lnodes[0][1];
    y2 = lnodes[1][1];
    y3 = lnodes[2][1];
    y4 = lnodes[3][1];

    Ax = x1 - x2 - x3 + x4;
    Bx = x1 - x2 + x3 - x4;
    Cx = x1 + x2 - x3 - x4;

    Ay = y1 - y2 - y3 + y4;
    By = y1 - y2 + y3 - y4;
    Cy = y1 + y2 - y3 - y4;

    FloatMatrix jac;
    this->interp.giveJacobianMatrixAt(jac, localCoords, FEIVertexListGeometryWrapper(lnodes) );
    double detJ = jac.giveDeterminant();

    double rz = sqrt( sqr(Cx + r*Bx) + sqr(Cy + r*By)) / ( 16 * detJ );
    double sz = sqrt( sqr(Ax + s*Bx) + sqr(Ay + s*By)) / ( 16 * detJ );

    // TODO: Not sure about this part (the reference is not explicit about these angles. / Mikael
    // Not sure about the transpose either.
    OOFEM_WARNING("The MITC4 implementation isn't verified yet. Highly experimental");
    FloatArray dxdr = {jac(0,0), jac(0,1)};
    dxdr.normalize();
    FloatArray dxds = {jac(1,0), jac(1,1)};
    dxds.normalize();

    double c_b = dxdr(0); //cos(beta);
    double s_b = dxdr(1); //sin(beta);
    double c_a = dxds(0); //cos(alpha);
    double s_a = dxds(1); //sin(alpha);

    // gamma_xz = "fi_y+dw/dx" in standard formulation
    answer(6, 2 + 5*0) = rz * s_b * ( (1+s)) - sz * s_a * ( (1+r));
    answer(6, 2 + 5*1) = rz * s_b * (-(1+s)) - sz * s_a * ( (1-r));
    answer(6, 2 + 5*2) = rz * s_b * (-(1-s)) - sz * s_a * (-(1-r));
    answer(6, 2 + 5*3) = rz * s_b * ( (1-s)) - sz * s_a * (-(1+r));

    answer(6, 3 + 5*0) = rz * s_b * (y2-y1) * 0.5 * (1+s) - sz * s_a * (y4-y1) * 0.5 * (1+r); // tx1
    answer(6, 4 + 5*0) = rz * s_b * (x1-x2) * 0.5 * (1+s) - sz * s_a * (x1-x4) * 0.5 * (1+r); // ty1

    answer(6, 3 + 5*1) = rz * s_b * (y2-y1) * 0.5 * (1+s) - sz * s_a * (y3-x2) * 0.5 * (1+r); // tx2
    answer(6, 4 + 5*1) = rz * s_b * (x1-x2) * 0.5 * (1+s) - sz * s_a * (x2-x3) * 0.5 * (1+r); // ty2

    answer(6, 3 + 5*2) = rz * s_b * (y3-y4) * 0.5 * (1-s) - sz * s_a * (y3-y2) * 0.5 * (1-r); // tx3
    answer(6, 4 + 5*2) = rz * s_b * (x4-x3) * 0.5 * (1-s) - sz * s_a * (x2-x3) * 0.5 * (1-r); // ty3

    answer(6, 3 + 5*3) = rz * s_b * (y3-y4) * 0.5 * (1-s) - sz * s_a * (y4-y1) * 0.5 * (1-r); // tx4
    answer(6, 4 + 5*3) = rz * s_b * (x4-x3) * 0.5 * (1-s) - sz * s_a * (x1-x4) * 0.5 * (1-r); // ty4

    // gamma_yz = -fi_x+dw/dy in standard formulation
    answer(7, 2 + 5*0) = - rz * c_b * ( (1+s)) + sz * c_a * ( (1+r));
    answer(7, 2 + 5*1) = - rz * c_b * (-(1+s)) + sz * c_a * ( (1-r));
    answer(7, 2 + 5*2) = - rz * c_b * (-(1-s)) + sz * c_a * (-(1-r));
    answer(7, 2 + 5*3) = - rz * c_b * ( (1-s)) + sz * c_a * (-(1+r));

    answer(7, 3 + 5*0) = - rz * c_b * (y2-y1) * 0.5 * (1+s) + sz * c_a * (y4-y1) * 0.5 * (1+r); // tx1
    answer(7, 4 + 5*0) = - rz * c_b * (x1-x2) * 0.5 * (1+s) + sz * c_a * (x1-x4) * 0.5 * (1+r); // ty1

    answer(7, 3 + 5*1) = - rz * c_b * (y2-y1) * 0.5 * (1+s) + sz * c_a * (y3-x2) * 0.5 * (1+r); // tx2
    answer(7, 4 + 5*1) = - rz * c_b * (x1-x2) * 0.5 * (1+s) + sz * c_a * (x2-x3) * 0.5 * (1+r); // ty2

    answer(7, 3 + 5*2) = - rz * c_b * (y3-y4) * 0.5 * (1-s) + sz * c_a * (y3-y2) * 0.5 * (1-r); // tx3
    answer(7, 4 + 5*2) = - rz * c_b * (x4-x3) * 0.5 * (1-s) + sz * c_a * (x2-x3) * 0.5 * (1-r); // ty3

    answer(7, 3 + 5*3) = - rz * c_b * (y3-y4) * 0.5 * (1-s) + sz * c_a * (y4-y1) * 0.5 * (1-r); // tx4
    answer(7, 4 + 5*3) = - rz * c_b * (x4-x3) * 0.5 * (1-s) + sz * c_a * (x1-x4) * 0.5 * (1-r); // ty4
#endif
}