U0 PlaceMass(I64 x, I64 y)
{
  MyMass *tempm=CAlloc(sizeof(MyMass));
  tempm->mass=1.0;
  tempm->drag_profile_factor=100.0;
  tempm->x=x;
  tempm->y=y;
  tempm->radius=10*(Rand+0.25);
  QueIns(tempm,ode->last_mass);
}