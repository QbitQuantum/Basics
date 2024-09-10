MatrixXf Arm::pseudo_inverse() {
    MatrixXf Jacovian = compute_Jacobian();
    MatrixXf jjtInv = (Jacovian * Jacovian.transpose());
    jjtInv = jjtInv.inverse();
    
    return (Jacovian.transpose() * jjtInv);
}