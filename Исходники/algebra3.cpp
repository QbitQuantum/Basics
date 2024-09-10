		mat4 rotation3Drad(vec3& Axis, const double angleRad) {
			double   c = cos(angleRad),
				s = sin(angleRad),
				t = 1.0 - c;

			Axis.normalize();
			return mat4(vec4(t * Axis[VX] * Axis[VX] + c,
					t * Axis[VX] * Axis[VY] - s * Axis[VZ],
					t * Axis[VX] * Axis[VZ] + s * Axis[VY],
					0.0),
				vec4(t * Axis[VX] * Axis[VY] + s * Axis[VZ],
					t * Axis[VY] * Axis[VY] + c,
					t * Axis[VY] * Axis[VZ] - s * Axis[VX],
					0.0),
				vec4(t * Axis[VX] * Axis[VZ] - s * Axis[VY],
					t * Axis[VY] * Axis[VZ] + s * Axis[VX],
					t * Axis[VZ] * Axis[VZ] + c,
					0.0),
				vec4(0.0, 0.0, 0.0, 1.0));
		}