int main( void ) {
    // init
    time_t seed = time(NULL);
    printf("seed: %ld\n", seed);
    srand((unsigned int)seed); // might break in 2038
    aa_test_ulimit();

    for( size_t i = 0; i < 1000; i++ ) {
        /* Random Data */
        static const size_t k=2;
        double E[2][7], S[2][8], T[2][12], dx[2][6];
        for( size_t j = 0; j < k; j ++ ) {
            rand_tf(E[j], S[j], T[j]);
            aa_vrand(6,dx[j]);
        }
        //printf("%d\n",i);
        /* Run Tests */
        rotvec(E[0]);
        euler(dx[0]);
        euler1(dx[0]);
        eulerzyx(E[0]);
        chain(E,S,T);
        quat(E);
        duqu();
        rel_q();
        rel_d();
        slerp();
        theta2quat();
        rotmat(E[0]);
        tfmat();
        tfmat_inv(T[0]);
        mzlook(dx[0]+0, dx[0]+3, dx[1]+0);
        integrate(E[0], S[0], T[0], dx[0]);
        tf_conj(E, S);
        qdiff(E,dx);
    }


    return 0;
}