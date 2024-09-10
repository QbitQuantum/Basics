void Road2::textureFit(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, int texfit, Vector2* texc, Vector3 pos, Vector3 lastpos, float width)
{
    int i;

    if (texfit == TEXFIT_BRICKWALL || texfit == TEXFIT_CONCRETEWALL || texfit == TEXFIT_CONCRETEWALLI)
    {
        Vector3 ps[4];
        ps[0] = p1;
        ps[1] = p2;
        ps[2] = p3;
        ps[3] = p4;
        Vector3 pref1 = pos;
        Vector3 pref2 = lastpos;
        //make matrix
        Vector3 bx = pref2 - pref1;
        bx.normalise();
        Vector3 by = Vector3::UNIT_Y;
        Vector3 bz = bx.crossProduct(by);
        //coordinates change matrix
        Matrix3 reverse;
        reverse.SetColumn(0, bx);
        reverse.SetColumn(1, by);
        reverse.SetColumn(2, bz);
        Matrix3 forward;
        forward = reverse.Inverse();
        //transpose
        for (i = 0; i < 4; i++)
        {
            Vector3 trv = forward * (ps[i] - pref1);
            if (texfit == TEXFIT_BRICKWALL)
            {
                float ty = 0.746 - trv.y * 0.25 / 4.5;
                // fix overlapping
                if (ty > 1)
                    ty = 1;
                texc[i] = Vector2(trv.x / 10.0, ty);
            }
            if (texfit == TEXFIT_CONCRETEWALL)
            {
                // fix overlapping
                float ty = 0.496 - (trv.y - 0.7) * 0.25 / 4.5;
                if (ty > 1)
                    ty = 1;
                texc[i] = Vector2(trv.x / 10.0, ty);
            }
            if (texfit == TEXFIT_CONCRETEWALLI)
            {
                float ty = 0.496 + trv.y * 0.25 / 4.5;
                // fix overlapping
                if (ty > 1)
                    ty = 1;
                texc[i] = Vector2(trv.x / 10.0, ty);
            }
        }
        return;
    }
    if (texfit == TEXFIT_ROAD || texfit == TEXFIT_ROADS1 || texfit == TEXFIT_ROADS2 || texfit == TEXFIT_ROADS3 || texfit == TEXFIT_ROADS4 || texfit == TEXFIT_CONCRETETOP || texfit == TEXFIT_CONCRETEUNDER)
    {
        Vector3 ps[4];
        ps[0] = p1;
        ps[1] = p2;
        ps[2] = p3;
        ps[3] = p4;
        Vector3 pref1 = pos;
        Vector3 pref2 = lastpos;
        //project
        for (i = 0; i < 4; i++)
            ps[i].y = 0;
        pref1.y = 0;
        pref2.y = 0;
        //make matrix
        Vector3 bx = pref2 - pref1;
        bx.normalise();
        Vector3 by = Vector3::UNIT_Y;
        Vector3 bz = bx.crossProduct(by);
        //coordinates change matrix
        Matrix3 reverse;
        reverse.SetColumn(0, bx);
        reverse.SetColumn(1, by);
        reverse.SetColumn(2, bz);
        Matrix3 forward;
        forward = reverse.Inverse();
        //transpose
        float trvrefz = 0.0;
        for (i = 0; i < 4; i++)
        {
            Vector3 trv = forward * (ps[i] - pref1);
            if (texfit == TEXFIT_CONCRETETOP)
            {
                if (i == 0)
                    trvrefz = trv.z;
                texc[i] = Vector2(trv.x / 10.0, 0.621 + (trv.z - trvrefz) * 0.25 / 4.5);
            }
            else
            {
                float v1 = 0.072;
                float v2 = 0.423;
                if (texfit == TEXFIT_ROADS1)
                {
                    v1 = 0.001;
                    v2 = 0.036;
                };
                if (texfit == TEXFIT_ROADS2)
                {
                    v1 = 0.036;
                    v2 = 0.072;
                };
                if (texfit == TEXFIT_ROADS3)
                {
                    v1 = 0.423;
                    v2 = 0.458;
                };
                if (texfit == TEXFIT_ROADS4)
                {
                    v1 = 0.458;
                    v2 = 0.493;
                };
                if (texfit == TEXFIT_CONCRETEUNDER)
                {
                    v1 = 0.496;
                    v2 = 0.745;
                };
                if (i < 2)
                    texc[i] = Vector2(trv.x / 10.0, v1);
                else
                    texc[i] = Vector2(trv.x / 10.0, v2);
            }
        }
        return;
    }
    //default
    for (i = 0; i < 4; i++)
        texc[i] = Vector2(0, 0);
}