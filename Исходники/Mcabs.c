int main(int argc, char* argv[])
{
    int i, id, dim, n[SF_MAX_DIM], nd;
    kiss_fft_cpx *din;
    float *dout;
    sf_file fin, fout;

    sf_init(argc,argv);
    fin = sf_input("in");
    fout = sf_output("out");

    if (SF_COMPLEX != sf_gettype(fin)) sf_error("Need complex input");

    dim = sf_filedims (fin,n);
    nd = 1;

    for (i=0; i < dim; i++) nd *= n[i];

    din = (kiss_fft_cpx*) sf_complexalloc(nd);
    dout = sf_floatalloc(nd);

    sf_floatread((float*)din,nd*2,fin);

    for (id=0; id < nd; id++) {
	dout[id] = hypotf(din[id].r,din[id].i);
    }

    sf_settype(fout, SF_FLOAT);
    sf_setform(fout, SF_NATIVE);

    sf_floatwrite(dout,nd,fout);

    exit(0);
}