static void Exact(PetscReal t,
                  PetscReal omega,PetscReal xi,PetscReal u0,PetscReal v0,
                  PetscReal *ut,PetscReal *vt)
{
#define Sin  PetscSinReal
#define Cos  PetscCosReal
#define Exp  PetscExpReal
#define Sqrt PetscSqrtReal
  PetscReal u,v;
  if (xi < 1) {
    PetscReal a  = xi*omega;
    PetscReal w  = Sqrt(1-xi*xi)*omega;
    PetscReal C1 = (v0 + a*u0)/w;
    PetscReal C2 = u0;
    u = Exp(-a*t) * (C1*Sin(w*t) + C2*Cos(w*t));
    v = (- a * Exp(-a*t) * (C1*Sin(w*t) + C2*Cos(w*t))
         + w * Exp(-a*t) * (C1*Cos(w*t) - C2*Sin(w*t)));
  } else if (xi > 1) {
    PetscReal w  = Sqrt(xi*xi-1)*omega;
    PetscReal C1 = (w*u0 + xi*u0 + v0)/(2*w);
    PetscReal C2 = (w*u0 - xi*u0 - v0)/(2*w);
    u = C1*Exp((-xi+w)*t) + C2*Exp((-xi-w)*t);
    v = C1*(-xi+w)*Exp((-xi+w)*t) + C2*(-xi-w)*Exp((-xi-w)*t);
  } else {
    PetscReal a  = xi*omega;
    PetscReal C1 = v0 + a*u0;
    PetscReal C2 = u0;
    u = (C1*t + C2) * Exp(-a*t);
    v = (C1 - a*(C1*t + C2)) * Exp(-a*t);
  }
  if (ut) *ut = u;
  if (vt) *vt = v;
}