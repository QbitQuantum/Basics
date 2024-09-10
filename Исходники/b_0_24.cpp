void bench_r2d_proj()
{
    Pt2di sz(120,50);

    Im2D_REAL8       MNT(sz.x,sz.y,0.0);
    Im2D_REAL8       X1(sz.x,sz.y,0.0);
    Im2D_REAL8       Y1(sz.x,sz.y,0.0);
    Im2D_REAL8       X2(sz.x,sz.y,0.0);
    Im2D_REAL8       Y2(sz.x,sz.y,0.0);


    ELISE_COPY(MNT.all_pts(),frandr(),MNT.out());

    ELISE_COPY
    (
        MNT.all_pts(),
        proj_cav(MNT.in(),0.5,2.0),
        Virgule(X1.out(),Y1.out())
    );

    ELISE_COPY
    (
        MNT.lmr_all_pts(Pt2di(1,0)),
        proj_cav(MNT.in(),0.5,2.0),
        Virgule(X2.out(),Y2.out())
    );

    REAL dif;

    ELISE_COPY 
    (
         MNT.all_pts(),
         Max(Abs(X1.in()-X2.in()),Abs(Y1.in()-Y2.in())),
         VMax(dif)
    );
    BENCH_ASSERT(dif<epsilon);


    ELISE_COPY
    (
        MNT.all_pts(),
        (2*PI)*phasis_auto_stereogramme(MNT.in(),10.5,2.0),
        X1.out()
    );

    ELISE_COPY
    (
        MNT.lmr_all_pts(Pt2di(1,0)),
        (2*PI)*phasis_auto_stereogramme(MNT.in(),10.5,2.0),
        X2.out()
    );

    ELISE_COPY 
    (
         MNT.all_pts(),
         Max
         (
              Abs(cos(X1.in())-cos(X2.in())),
              Abs(sin(X1.in())-sin(X2.in()))
         ),
         VMax(dif)
    );

    BENCH_ASSERT(dif<epsilon);
}