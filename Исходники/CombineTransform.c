void Test_CombineTransform_Inval(float eInval, float eOut)
{
    XFORM xform1, xform2, xform3;

    /* zero matrix / M11 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, eInval, 0.0, 0.0, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, eOut, 0.0, 0.0, 0.0, 0.0, 0.0); // -> M21
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, eOut, 0.0, 0.0, 0.0, 0.0, 0.0); // -> M12

    /* zero matrix / M12 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, 0.0, eInval, 0.0, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, 0.0, eOut, 0.0, eOut, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, eOut, eOut, 0.0, 0.0, 0.0, 0.0);

    /* zero matrix / M21 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, 0.0, 0.0, eInval, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, eOut, 0.0, eOut, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, 0.0, 0.0, eOut, eOut, 0.0, 0.0);

    /* zero matrix / M22 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, 0.0, 0.0, 0.0, eInval, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, 0.0, 0.0, 0.0, eOut, 0.0, 0.0); // -> M12
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, 0.0, 0.0, 0.0, eOut, 0.0, 0.0); // -> M21

    /* zero matrix / M11,M12 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, eInval, eInval, 0.0, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, eOut, eOut, eOut, eOut, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, eOut, eOut, 0.0, 0.0, 0.0, 0.0);

    /* zero matrix / M11,M21 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, eInval, 0.0, eInval, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, eOut, 0.0, eOut, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, eOut, eOut, eOut, eOut, 0.0, 0.0);

    /* zero matrix / M11,M22 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, eInval, 0.0, 0.0, eInval, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, eOut, 0.0, 0.0, eOut, 0.0, 0.0); // -> M12, M21
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, eOut, 0.0, 0.0, eOut, 0.0, 0.0);

    /* zero matrix / M12,M21 invalid */
    set_xform(&xform1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    set_xform(&xform2, 0.0, eInval, eInval, 0.0, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform1, &xform2), 1);
    ok_xform(xform3, eOut, eOut, eOut, eOut, 0.0, 0.0);
    ok_int(CombineTransform(&xform3, &xform2, &xform1), 1);
    ok_xform(xform3, eOut, eOut, eOut, eOut, 0.0, 0.0);
}