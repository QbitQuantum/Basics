/**
 * Santiago Akle 
 * ICME Stanford University 2014
 *
 * Exemplifies the use of wrightOmega 
 *
 * */
int main(void)
{   
    pfloat r = 0.0;
    pfloat z = 1.0;
    pfloat w = 0.0;
    pfloat maxerr = 0.0;
    pfloat maxeval = 0.0;
    pfloat smallest = z;
    int i    = 0;
    
    //Caculate the factor that will skip 2^25 floating points
    pfloat scaling = nextafter(1.0,2.0); //1+eps
    for(;i<27;i++)
        scaling        = scaling*scaling;
 
    for(i=0;i<1E9;i++)
    {
        z *= scaling;
        w = wrightOmega(z);
        r = w+log(w)-z;
        r = fabs(r); //abs r
        r = r/fabs(z);
        if(r>maxerr)
        {
            maxerr = r;
            maxeval = w;
        }
    }
    pfloat largest = z;
    printf("Largerst relative error %e achieved at %e\n",maxerr,maxeval);
    printf("Smallest number evaluated %e largest %e range %e\n",smallest,largest,largest-smallest);
}