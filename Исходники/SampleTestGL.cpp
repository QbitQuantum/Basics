static void testinvert() {
    SkMatrix matrix;

    const float vals[] = { 0,9,.000001,10000,0,0 };
    setmatrix6(&matrix, vals);

    const float vals2[] = { 0,100,71,9,0,7 };
    SkMatrix tmp;
    setmatrix6(&tmp, vals2);
    
    matrix.preConcat(tmp);
    matrix.dump();

    SkMatrix inverse;
    matrix.invert(&inverse);
    inverse.dump();
    
    matrix.preConcat(inverse);
    matrix.dump();

//    o2dContext.setTransform(0,9,.000001,10000,0,0);
//    o2dContext.transform(0,100,71,9,0,7);
//    o2dContext.setTransform(0,6,95,4,1,0);
}