// \en Calculates intersections. Stores intersection info to intersections and returns the number of intersections.\enden \ja 交点計算を行う。交点の情報はintersectionsに格納し、交点の数を返す。 \endja 
// \en The ray is defined as the starting point o and the normalized direction vector d as in o + td, 0.0 <= t.\enden \ja レイは始点位置ベクトルo、単位方向ベクトルdから成る、o + td, 0.0 <= t として指定される。 \endja 
int attribute_component::ray_intersection (const sxsdk::custom_element_info_base_class *info, sxsdk::shape_class &shape, const sxsdk::mat4 &lw, const sxsdk::mat4 &wl, int i, const sx::vec<float,3> &o, const sx::vec<float,3> &d, sxsdk::intersection_class intersections[], sxsdk::custom_element_info_base_class *per_thread, void *) {
	{	custom_element_info__class *info = dynamic_cast<custom_element_info__class *>(per_thread);
		if (info) {
			for (int i = 0; i < 100; i++) info->data[i] = i;
		}
	}
	int n = 0;
	sxsdk::sphere_class &sphere = shape.get_sphere();
	if (info) {

		// \en Fetch the data created in the new_custom_element_info function.\enden \ja new_custom_element_infoで作成したデータを取得する。 \endja 
		const float size = dynamic_cast<const custom_size_class &>(*info).size;

		sxsdk::mat4 t = sphere.get_matrix();
		for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) t[i][j] *= size;
		t *= lw;
		sxsdk::mat4 itrans = inv(t);
		sx::vec<float,3> p2 = o * itrans; // \en Transform the starting point of the ray to the sphere primitive coordinates.\enden \ja レイの始点位置ベクトルを球プリミティブ座標系に変換する。 \endja 
		sx::vec<float,3> d2 = transform_direction(d, itrans); // \en Transform the normalized direction vector of the ray to the sphere primitive coordinates.\enden \ja レイの単位方向ベクトルを球プリミティブ座標系に変換する。 \endja 
		
		// \en Calculate the intersections between the sphere and the ray.\enden \ja 球とレイの交点計算。 \endja 
		float a = d2.x * d2.x + d2.y * d2.y + d2.z * d2.z;
		float b = p2.x * d2.x + p2.y * d2.y + p2.z * d2.z;
		float c = p2.x * p2.x + p2.y * p2.y + p2.z * p2.z - 1.0f;
		float k = b*b - a*c;
		if (k <= 0.0f) ;
		else {
			k = sqrt(k);
			float t1 = (-b + k) / a;
			float t0 = (-b - k) / a;
			//sxassert(t0 <= t1);
			if (0.0f <= t0) {
				intersections[n].t = t0;
				sx::vec<float,3> normal = p2 + d2 * t0;
				intersections[n].normal = normalize(transform_normal(itrans, normal));
				intersections[n].point = o + d * t0;
				
				// \en Merge Info.\enden \ja 融合情報 \endja 
				if (shape.has_sis()) {
					intersections[n].number_of_shapes = 2;
					//sxassert(intersections[n].shape_mixes);
					intersections[n].shape_mixes[1] = sxsdk::shape_mix_class(0.5f, shape.get_sis());
					intersections[n].shape_mixes[0] = sxsdk::shape_mix_class(0.5f, &shape);
				}
				n++;
			}
			if (0.0f <= t1) {
				intersections[n].t = t1;
				sx::vec<float,3> normal = p2 + d2 * t1;
				intersections[n].normal = normalize(transform_normal(itrans, normal));
				intersections[n].point = o + d * t1;
				
				// \en Merge Info.\enden \ja 融合情報 \endja 
				if (shape.has_sis()) {
					intersections[n].number_of_shapes = 2;
					//sxassert(intersections[n].shape_mixes);
					intersections[n].shape_mixes[1] = sxsdk::shape_mix_class(0.5f, shape.get_sis());
					intersections[n].shape_mixes[0] = sxsdk::shape_mix_class(0.5f, &shape);
				}
				n++;
			}
		}
	}
	return n;
}