static FLOAT pw91_nu, pw91_beta;
static const FLOAT
  pw91_C_c0  = 4.235e-3, 
  pw91_alpha = 0.09;

static void 
gga_c_pw91_init(XC(func_type) *p)
{
  p->n_func_aux  = 1;
  p->func_aux    = (XC(func_type) **) malloc(1*sizeof(XC(func_type) *));
  p->func_aux[0] = (XC(func_type) *)  malloc(  sizeof(XC(func_type)));

  XC(func_init)(p->func_aux[0], XC_LDA_C_PW, p->nspin);

  pw91_nu   = 16.0/M_PI * CBRT(3.0*M_PI*M_PI);
  pw91_beta = pw91_nu*pw91_C_c0;
}


static void
A_eq14(int order, FLOAT ec, FLOAT g, FLOAT *A, 
       FLOAT *dAec, FLOAT *dAg,
       FLOAT *d2Aec2, FLOAT *d2Ag2, FLOAT *d2Aecg)
{
  FLOAT xx, expxx, g2, g3;
  FLOAT dAdxx, dxxdec, dxxdg;
  FLOAT d2Adxx2, d2xxdecg, d2xxdg2;

  g2 = g*g;
  g3 = g*g2;