/*-----------------------------------------------------------------------------*\
 * 从四元数转换为欧拉角表示 done
 *
 * out q的欧拉角表示
 * q 源四元数
 *-----------------------------------------------------------------------------*/
void magicalEulerAnglesFromQuaternion( cEulerAngles* out, const cQuaternion* q )
{
	float sp = -2.0f * ( q->y * q->z + q->w * q->x );

	if( fabsf( sp ) > 0.9999f )
	{
		out->pitch = kPIOver2 * sp;
		out->yaw = atan2f( -q->x * q->z - q->w * q->y, 0.5f - q->y * q->y - q->z * q->z );
		out->roll = 0.0f;
	}
	else
	{
		out->pitch = asinf( sp );
		out->yaw = atan2f( q->x * q->z - q->w * q->y, 0.5f - q->x * q->x - q->y * q->y );
		out->roll = atan2f( q->x * q->y - q->w * q->z, 0.5f - q->x * q->x - q->z * q->z );
	}
}