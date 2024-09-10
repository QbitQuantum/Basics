Track_Scholz2000::Track_Scholz2000(const Particle &particle,
                                   const double density,
                                   double t)
{
    particleType = particle.type;

    const double AMU2MEV = 931.494027;  //MeV/amu
    particleEnergy = particle.e_c / particle.restEnergy * AMU2MEV;
    r_max = GAMMA * pow(particle.e_c / particle.restEnergy * AMU2MEV, DELTA);  //um

    if( r_max < R_MIN )
        r_max = R_MIN;

    let = particle.let;
    e_c = particle.e_c;

    const double CONV = 160.2177;  //(J*um^3)/(MeV*dm^3) : Constant of conversion (MeV*dm^3)/(Kg*um^3) -> Gy
    lambda = CONV / (2 * M_PI * density * (0.5 + log(r_max/R_MIN))); //Gy * um^3/MeV

    x_track = particle.x;  // mm
    y_track = particle.y;  // mm
    weight = particle.weight;
    
    time = t;
}