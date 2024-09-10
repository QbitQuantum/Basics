CCircle CMinSquareRecognizing::getCircleByPoints( std::vector<cv::Point> points )
{
    Eigen::MatrixXd C( 4, 4 );
    C.fill( 0 );
    C( 0, 0 ) = 4.;

    Eigen::MatrixXd S = generateScatterMatrix( points );

    Eigen::MatrixXd InverseS = S.inverse();
    Eigen::MatrixXd engineM = InverseS * C;

    Eigen::EigenSolver<Eigen::MatrixXd> es( engineM, true );

    Eigen::MatrixXd vecs = es.eigenvectors().real();
    Eigen::MatrixXd vals = es.eigenvalues().real();

    for( int i = 0; i < vecs.rows(); ++i ) {
        Eigen::MatrixXd row = vecs.row( i );
        Eigen::MatrixXd rowTranspose = row.transpose();
        double tmp = ( row * S * rowTranspose )( 0, 0 );

        if( ( 1. / vals( i, 0 ) ) > 0
            && !isAbsInf( 1. / vals( i, 0 ) )
            && !isAbsInf( vals( i, 0 ) )
            && tmp > 0 ) {

            //нормируем коэффициент перед квадратами до 1
            double a = vecs( 0, i );
            double b = vecs( 1, i ) / a;
            double c = vecs( 2, i ) / a;
            double d = vecs( 3, i ) / a;


            double x = -b / 2.;
            double y = -c / 2.;
            double r = sqrt( b * b + c * c - 4 * d ) / 2.;

            double accuracy = countCircleAccuracy( x, y, r, points );
            return CCircle( cvRound( x ), cvRound( y ), cvRound( r ), accuracy );
        }
    }

    return CCircle( 0, 0, 0 );
}