int Trace(float *p, float *v, int k)
{

    if( k > MAX_STEPS )
    {
        return -1;
    }

    int con = Intersect(p, v);

    if(con == -1) {
        return con; //nothing
    }
    else if(con < -1) {
        return con;  //light source
    }
    else if (con >=0 ) // is object
    {
        Normal(con);
        Reflect(v);
        Phong(v, con);
        for(int i=0; i<3; i++)
        {
            color[i] += inters_c[i];;
        }
        Trace (inter, ref, k+1);
    }

    return 0;
}