//----------------------------------------------------------------------------
void SEIntrTriangle3Triangle3f::ProjectOntoAxis(const SETriangle3f& rTri, 
    const SEVector3f& rAxis, SEConfiguration& rCfg)
{
    // find projections of vertices onto potential separating axis
    float fD0 = rAxis.Dot(rTri.V[0]);
    float fD1 = rAxis.Dot(rTri.V[1]);
    float fD2 = rAxis.Dot(rTri.V[2]);

    // explicit sort of vertices to construct a SEConfiguration object
    if( fD0 <= fD1 )
    {
        if( fD1 <= fD2 ) // D0 <= D1 <= D2
        {
            if( fD0 != fD1 )
            {
                if( fD1 != fD2 )
                {
                    rCfg.Map = M111;
                }
                else
                {
                    rCfg.Map = M12;
                }
            }
            else // ( D0 == D1 )
            {
                if( fD1 != fD2 )
                {
                    rCfg.Map = M21;
                }
                else
                {
                    rCfg.Map = M3;
                }
            }
            rCfg.Index[0] = 0;
            rCfg.Index[1] = 1;
            rCfg.Index[2] = 2;
            rCfg.Min = fD0;
            rCfg.Max = fD2;
        }
        else if( fD0 <= fD2 ) // D0 <= D2 < D1
        {
            if( fD0 != fD2 )
            {
                rCfg.Map = M111;
                rCfg.Index[0] = 0;
                rCfg.Index[1] = 2;
                rCfg.Index[2] = 1;
            }
            else
            {
                rCfg.Map = M21;
                rCfg.Index[0] = 2;
                rCfg.Index[1] = 0;
                rCfg.Index[2] = 1;
            }
            rCfg.Min = fD0;
            rCfg.Max = fD1;
        }
        else // D2 < D0 <= D1
        {
            if( fD0 != fD1 )
            {
                rCfg.Map = M111;
            }
            else
            {
                rCfg.Map = M12;
            }

            rCfg.Index[0] = 2;
            rCfg.Index[1] = 0;
            rCfg.Index[2] = 1;
            rCfg.Min = fD2;
            rCfg.Max = fD1;
        }
    }
    else if( fD2 <= fD1 ) // D2 <= D1 < D0
    {
        if( fD2 != fD1 )
        {
            rCfg.Map = M111;
            rCfg.Index[0] = 2;
            rCfg.Index[1] = 1;
            rCfg.Index[2] = 0;
        }
        else
        {
            rCfg.Map = M21;
            rCfg.Index[0] = 1;
            rCfg.Index[1] = 2;
            rCfg.Index[2] = 0;

        }
        rCfg.Min = fD2;
        rCfg.Max = fD0;
    }
    else if( fD2 <= fD0 ) // D1 < D2 <= D0
    {
        if( fD2 != fD0 ) 
        {
            rCfg.Map = M111;
        }
        else
        {
            rCfg.Map = M12;
        }

        rCfg.Index[0] = 1;
        rCfg.Index[1] = 2;
        rCfg.Index[2] = 0;
        rCfg.Min = fD1;
        rCfg.Max = fD0;
    }
    else // D1 < D0 < D2
    {
        rCfg.Map = M111;
        rCfg.Index[0] = 1;
        rCfg.Index[1] = 0;
        rCfg.Index[2] = 2;
        rCfg.Min = fD1;
        rCfg.Max = fD2;
    }
}