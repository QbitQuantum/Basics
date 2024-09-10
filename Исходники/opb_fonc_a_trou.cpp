         Simple_OPBuf1<INT,INT> *
         FoncATrou_OPB_Comp<Type>::dup_comp()
{

    return new
           FoncATrou_OPB_Comp<Type>
           (
                _l,
                x0(),
                x1(),
                y0(),
                y1()
           );
}