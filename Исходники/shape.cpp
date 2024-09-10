	Shape::Shape(const Transform o2w, Material *m) : m_objToWorld(o2w), m_worldToObj(o2w.inverse()), m_material(m)
	{

	}