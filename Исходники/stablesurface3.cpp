/**
 * Verifica si un plano corta a una nube en dos
 * @param  pc    nube de puntos a evaluar
 * @param  coefs Coeficientes del plano
 * @return       True si lo corta, false en caso contrario.
 */
bool isPointCloudCutByPlane(PointCloud<PointXYZ>::Ptr pc, ModelCoefficients::Ptr coefs, PointXYZ p_plane){
	/*
	Algoritmo:
		- Obtener vector normal a partir de coeficientes
		- Iterar sobre puntos de la nube
			- Calcular vector delta entre punto entregado (dentro del plano) y punto iterado
			- Calcular ángulo entre vector delta y normal
			- Angulos menores a PI/2 son de un lado, mayores son de otro
			- Si aparecen puntos de ambos lados, retornar True, else, false.
	*/
	const double PI = 3.1416;
	Eigen::Vector3f normal = Eigen::Vector3f(coefs->values[0], coefs->values[1], coefs->values[2]);
	normal.normalize();
	// cout << "Normal: " << normal << endl;
	bool side;
	// Iterar sobre los puntos
	for (int i=0; i<pc->points.size(); i++){
		// Calcular ángulo entre punto y normal
		Eigen::Vector3f delta = Eigen::Vector3f (p_plane.x, p_plane.y, p_plane.z) - Eigen::Vector3f(pc->points[i].x, pc->points[i].y, pc->points[i].z);
		delta.normalize();
		double alpha = acos(normal.dot(delta));
		// printf ("Alpha: %f°\n", (alpha*180/PI));
		if (i==0){
			side = (alpha < PI/2.0);
			// printf("Lado escogido: %s", side ? "true": "false");
			continue;
		}
		if (side != (alpha < PI/2.0)){
			// printf("Nube es cortada por plano\n");
			return true;
		}
	}
	// printf("Nube NO es cortada por plano\n");
	return false;
}