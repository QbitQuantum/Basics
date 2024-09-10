Vector FlipPath::get_normal(){
    Vector norm =prod * Matrix::rotateXYZ(cur_rotate)* Vector(0,1,0);
    norm.normalize();
    return norm;
}