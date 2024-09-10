int main() {

    // read in the file
    Coords posvel("dm_1.0000.bin");
    cout << "Read in " << posvel.npart << " particles\n";

    // Exercise the interface and code
    {
           Vector3f av;
           Map< MatrixXf > epos = posvel.pos.matrix();
           av = epos.rowwise().sum()/ posvel.npart;
           cout << "Average position : " << av.transpose() << endl;

           Map< MatrixXf > evel = posvel.vel.matrix();
           av = evel.rowwise().sum()/ posvel.npart;
           cout << "Average velocity : " << av.transpose() << endl;
    }


    // Define the grid
    MA<array4d> grid(extents[4][Ngrid][Ngrid][Ngrid+2]); // Pad for FFT, 1 component for overdensity, 3 for velocity
    // Define views on this grid
    MA<view4_4d> rgrid = grid.view<view4_4d>(indices[r_()][r_()][r_()][r_(0, Ngrid)]);
    MA<ref4c> cgrid ( new ref4c(reinterpret_cast< complex<double>* >(grid.ref()), extents[4][Ngrid][Ngrid][Ngrid/2 + 1]));
    MA<array4d::reference> dense = rgrid.sub(0);


    // CIC grid
    cout << "Integrated density, density-weighted velocity -->\n";
    for (int ii = 0; ii < 4; ++ii) {
        cic(rgrid.sub(ii), posvel, ii-1);
        cout << boost::format("%1$6i %2$20.10f\n") % ii % (rgrid.sub(ii).sum());
    }



    // Normalize by density
    int nzeros;
    cout << "Integrated velocity field -->\n";
    for (int ii=1; ii < 4; ++ii) {
        nzeros = 0;
        boost::function < void(double&, double&) > ff = if_(_2 > 0)[_1 /= _2].else_[var(nzeros)++];
        multi_for(rgrid.sub(ii), dense,ff);
        cout << boost::format("%1$6i %2$20.10f %3$10i\n") % ii % (rgrid.sub(ii).sum()*Lbox) % nzeros;
       }
    // Normalize the density by rho_mean
    cout << dense.sum() << endl;
    dense /= static_cast<double>(posvel.npart)/pow( static_cast<double>(Ngrid), 3);
    cout << dense.sum() << endl;


    // FFT
    fftw_forward(grid);


    // Compute k_i v_i for each grid separately
    kdot_impl kdot;
    for (int ii=1; ii < 4; ++ii) {
        kdot.idim = ii-1;
        multi_for_native_indices(cgrid.sub(ii), kdot);
    }

    // Now add the vectors together --- things are contiguous, so go ahead and use the
    // easy route
    cgrid.sub(1)() += cgrid.sub(2)() + cgrid.sub(3)();
    // This should be what we need modulo normalization factors

    // Compute P(k)
    PkStruct pk;
    double lkmin = log(0.008); double lkmax = log(0.3);
    pk.setbins(lkmin, lkmax, 20);

    // We want to compute delta* delta, delta* theta, and theta* theta
    complex_mult_impl cmult;
    // First do delta* theta -- and store this in cgrid.sub(2)
    multi_for(cgrid.sub(0), cgrid.sub(1), cgrid.sub(2), cmult);
    // delta* delta and theta* theta -- store in place
    multi_for(cgrid.sub(0), cgrid.sub(0), cgrid.sub(0), cmult); // We do it this way to make the connection clear with delta* theta
    multi_for(cgrid.sub(1), cgrid.sub(1), cgrid.sub(1), cmult); // We do it this way to make the connection clear with delta* theta


    // Do the matter power spectrum
    multi_for_native_indices(cgrid.sub(0), pk);
    cout << pk.pk() << endl;
    writeMatrix("pk_matter.dat", "%1$10.4e ", pk.pk());

    // Do the velocity power spectrum
    pk.reset();
    multi_for_native_indices(cgrid.sub(1), pk);
    double fac; fac = pow(Lbox, 2);
    cout << pk.pk(fac) << endl; // The true adds in the correct velocity normalization
    writeMatrix("pk_theta.dat", "%1$10.4e ", pk.pk(fac));


    // Do the cross power spectrum
    pk.reset();
    multi_for_native_indices(cgrid.sub(2), pk);
    fac = Lbox;
    cout << pk.pk(fac) << endl; // The true adds in the correct velocity normalization
    writeMatrix("pk_delta_theta.dat", "%1$10.4e ", pk.pk(fac));

}