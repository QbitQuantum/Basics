	static CQuaternion CreateFromVectors(vec3 v0, vec3 v1)  {
		CQuaternion q;
		
		if (v0 == -v1) {//Create from Axis Angle
		  //int a = 1;
		}

		vec3 c = v0.Cross(v1);
		float d = v0.Dot(v1);
		
		float s = (float)  sqrt((1+d)*2);

		q.x = c.x /s;
		q.y = c.y/s;
		q.z = c.z/s;
		q.w = s / 2.0f;
		return q;
	}