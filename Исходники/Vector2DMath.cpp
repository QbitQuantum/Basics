		Vector2D Nlerp(const Vector2D &a, const Vector2D &b, Float t) {
			Vector2D v;
			Lerp(a, b, t, &v);
			v.Normalize();
			return v;
		}