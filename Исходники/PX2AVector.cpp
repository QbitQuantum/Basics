//----------------------------------------------------------------------------
void AVector::Orthonormalize (AVector& vec0, AVector& vec1, AVector& vec2)
{
	// 输入的向量为v0，v1，v2，按照下面的方式进行Gram-Schmidt正交化
	//
	//   u0 = v0/|v0|
	//   u1 = (v1-(u0*v1)u0)/|v1-(u0*v1)u0|
	//   u2 = (v2-(u0*v2)u0-(u1*v2)u1)/|v2-(u0*v2)u0-(u1*v2)u1|
	//
	// |A|代表向量A的长度；A*B代表两个向量“点乘”

	// 单位化
	vec0.Normalize();

	// 计算 u1
	float dot0 = vec0.Dot(vec1); 
	vec1 -= dot0*vec0;
	vec1.Normalize();

	// 计算 u2
	float dot1 = vec1.Dot(vec2);
	dot0 = vec0.Dot(vec2);
	vec2 -= dot0*vec0 + dot1*vec1;
	vec2.Normalize();
}