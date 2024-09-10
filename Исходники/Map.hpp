			int real_to_pixel(float x) const {
				return (unsigned) roundf(x * _fx);
			}