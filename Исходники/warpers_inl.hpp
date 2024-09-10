inline
void TransverseMercatorProjector::mapBackward(float u, float v, float &x, float &y)
{
	u /= scale;
    v /= scale;

	float v_ = asinf( sinf(v) / coshf(u) );
	float u_ = atan2f( sinhf(u), cos(v) );

    float cosv = cosf(v_);
    float x_ = cosv * sinf(u_);
    float y_ = sinf(v_);
    float z_ = cosv * cosf(u_);

    float z;
    x = k_rinv[0] * x_ + k_rinv[1] * y_ + k_rinv[2] * z_;
    y = k_rinv[3] * x_ + k_rinv[4] * y_ + k_rinv[5] * z_;
    z = k_rinv[6] * x_ + k_rinv[7] * y_ + k_rinv[8] * z_;

    if (z > 0) { x /= z; y /= z; }
    else x = y = -1;
}