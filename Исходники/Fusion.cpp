double Xsec_Fusion_NRL(double& Energy)// Energy in in Joules, and energy is collision energy
{
    if(Energy==0)
    {
        return 0;
    }
    else
    {
        int id_p = 1; // 'Incident' deuteron
        int id_b = 2; // 'Target' triton
        double E_in = (Energy/(1.0E3*e_ch))*(mass[id_p]+mass[id_b])/mass[id_b]; // Convert from J to keV, and to energy of a deuteron incident on a triton
        double xsec = (Fuse_coefs_NRL[5]+Fuse_coefs_NRL[2]/(pow(Fuse_coefs_NRL[4]-Fuse_coefs_NRL[3]*E_in,2)+1.0E0))/(E_in*(exp(Fuse_coefs_NRL[1]/sqrt(E_in))-1.0E0));
        return xsec*1.0E-28; // Convert from barns to m^-2
    }
}