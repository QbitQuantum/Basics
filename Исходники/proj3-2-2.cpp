/**
 * @function main
 */
int main( int argc, char* argv[] )
{
    if( argc < 3 )
    {
        printf("Error. Give me two files with 2D and 3D Points \n");
        return 1;
    }


    /** Normalize */
    normalizePoints2D( argv[1], T2a, points2Da, normPoints2Da );
    normalizePoints2D( argv[2], T2b, points2Db, normPoints2Db );

    /** SVD */
    calculateF_SVD( normPoints2Da, normPoints2Db, Fh );

    /** Print Fh */
    std::cout << Fh << std::endl;

    std::cout << Fh.inverse() << std::endl;
    return 0;
}