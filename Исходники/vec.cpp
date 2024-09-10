bool make_orthonormal_basis(Vec3CR x, Vec3& y, Vec3& z)
{
        if( (z = x.cross(y)).is_zero() ) return false;
        y = z.cross(x).normal();
        z.normalize();
        return true;
}