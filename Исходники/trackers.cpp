/// Kinetic energy relative to center of mass
// K = ½Σmᵢvᵢ² - ½(Σmᵢvᵢ)² / (Σmᵢ)
flt kinetic_energy_com(AtomGroup &atoms) {
    flt Ksum = 0;
    Vec mvsum = Vec::Zero();
    flt msum = 0;
    for (uint i = 0; i < atoms.size(); i++) {
        Atom &a = atoms[i];
        Vec mv = a.m * a.v;
        Ksum += mv.dot(a.v);
        mvsum += mv;
        msum += a.m;
    }
    return (Ksum - mvsum.squaredNorm() / msum) / 2;
};