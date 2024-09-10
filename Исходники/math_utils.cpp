matrix_3f inverse ( const matrix_3f & A ) {
    Matrix3frm B;
    matrix_3f A_inverse;

    B = matrix_3f_to_Eigen ( A );

    A_inverse = Eigen_to_matrix_3f ( B.inverse() );

    return A_inverse;
}