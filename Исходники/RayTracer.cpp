Ray Raytracer::GetRay(int _x, int _y) const
{
	float fovx =  M_PI * m_FOV / 180; //Horizontal FOV
	float fovy =  M_PI * 55 / 180; //Vertical FOV (hard coded to 55)

	float halfWidth = m_Width/2;
	float halfHeight = m_Height/2;

	float alpha = tanf(fovx / 2)*((_x - halfWidth) / halfWidth) + ((float)rand() / RAND_MAX - 0.5f) * 0.01f; //horizontal offset
	float beta = tanf(fovy / 2)*((halfHeight - _y) / halfHeight) + ((float)rand() / RAND_MAX - 0.5f) * 0.01f; //vertical offset

	Matrix viewMatrix = m_pCamera->GetViewMatrix();
	Vector3 pos = viewMatrix.Translation();
	Vector3 dir = alpha * viewMatrix.Right() + beta * viewMatrix.Up() + viewMatrix.Forward();
	dir.Normalize();
	
	return Ray(pos, dir);
}