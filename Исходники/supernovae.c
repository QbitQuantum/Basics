int kineticFeedback_mixt(struct RUNPARAMS *param, struct CELL *cell,struct PART *curp, REAL aexp, int level, REAL E, REAL dt){
// ----------------------------------------------------------//
/// Inject an energy "E" in all cells of the oct contening
/// the cell "cell" on kinetic form, radially to the center
/// of the oct and uniformly in all cells
// ----------------------------------------------------------//

  //REAL mtot_feedback = curp->mass* param->sn->ejecta_proportion;
  //printf("injecting_old m=%e, e=%e\t",curp->mass* param->sn->ejecta_proportion,E);

  REAL mtot_feedback = get_mass(param,curp,aexp,dt);

  if (mtot_feedback==0){
    printf("WARNING null mass in kinetic feedback!\n");
    return 1;
  }

  printf("injecting_new m=%e, e=%e\n",mtot_feedback ,E);

  int i;
{
//#define LOAD_FACTOR
#ifdef LOAD_FACTOR

  REAL load_factor=10;
  REAL local_rho_min=FLT_MAX;

  for(i=0;i<8;i++){
    struct OCT* oct = cell2oct(cell);
    struct CELL* curcell = &oct->cell[i];
    local_rho_min = FMIN(curcell->field.d,local_rho_min);
  }

  REAL lf = FMIN(load_factor*curp->mass,local_rho_min);
  mtot_feedback += lf;

  for(i=0;i<8;i++){
    struct OCT* oct = cell2oct(cell);
    struct CELL* curcell = &oct->cell[i];
    curcell->field.d -= lf/8.;
  }
#endif // LOAD_FACTOR
}

  for(i=0;i<8;i++){
    struct OCT* oct = cell2oct(cell);
    struct CELL* curcell = &oct->cell[i];
    REAL dv = POW(0.5,3*level);// curent volume

    REAL dir_x[]={-1., 1.,-1., 1.,-1., 1.,-1., 1.};// diagonal projection
    REAL dir_y[]={-1.,-1., 1., 1.,-1.,-1., 1., 1.};
    REAL dir_z[]={-1.,-1.,-1.,-1., 1., 1., 1., 1.};

    REAL fact = 1.0;

    REAL m_e = mtot_feedback/8.;
    REAL d_e = m_e/dv; // ejecta density
//--------------------------------------------------------------------------//

    // kinetic energy injection
    REAL E_e = E/8. *fact;
    REAL v_e = SQRT(2.*E_e/curcell->field.d);

    //printf("field.d=%e\n",curcell->field.d);
    REAL sqrt3 = SQRT(3.);
    curcell->field.u += v_e*dir_x[i]/sqrt3;
    curcell->field.v += v_e*dir_y[i]/sqrt3;
    curcell->field.w += v_e*dir_z[i]/sqrt3;
//--------------------------------------------------------------------------//
/*
    // momentum injection
    E_e = E/8. *(1.-fact) ; // uniform distribution
    v_e = SQRT(2.*E_e/d_e);// ejecta velocity / particle

    REAL vxe = curp->vx + v_e*dir_x[i]/sqrt3; // ejecta velocity /grid
    REAL vye = curp->vy + v_e*dir_y[i]/sqrt3;
    REAL vze = curp->vz + v_e*dir_z[i]/sqrt3;

    REAL d_i = curcell->field.d; // initial density
    REAL vxi = curcell->field.u; // initial velocity
    REAL vyi = curcell->field.v;
    REAL vzi = curcell->field.w;

    curcell->field.u = (vxi*d_i + vxe*d_e)/(d_i+d_e); //new velocity
    curcell->field.v = (vyi*d_i + vye*d_e)/(d_i+d_e);
    curcell->field.w = (vzi*d_i + vze*d_e)/(d_i+d_e);
*/
//--------------------------------------------------------------------------//

    // mass conservation
    curp->mass       -= m_e;
    curcell->field.d += d_e; //new density

    //Energy conservation
#ifdef DUAL_E
    struct Utype U; // conservative field structure
    W2U(&curcell->field, &U); // primitive to conservative
    U.eint*=1.+d_e/curcell->field.d; // compute new internal energy
    U2W(&U, &curcell->field); // back to primitive
#else
    curcell->field.p*=1.+d_e/curcell->field.d; // compute new internal energy
#endif

    getE(&curcell->field); //compute new total energy
    curcell->field.p=FMAX(curcell->field.p,PMIN);
    curcell->field.a=SQRT(GAMMA*curcell->field.p/curcell->field.d); // compute new sound speed
  }
  return 0;
}