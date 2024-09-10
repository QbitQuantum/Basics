		primitive_properties& operator=(primitive_properties&& props) noexcept {
			points.swap(props.points);
			extent = props.extent;
			primitive_type = props.primitive_type;
			flags = props.flags;
			return *this;
		}