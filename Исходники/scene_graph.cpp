void SceneGraph::link(TransformInstance child, TransformInstance parent)
{
	unlink(child);

	if (!is_valid(_data.first_child[parent.i]))
	{
		_data.first_child[parent.i] = child;
		_data.parent[child.i] = parent;
	}
	else
	{
		TransformInstance prev = { UINT32_MAX };
		TransformInstance node = _data.first_child[parent.i];
		while (is_valid(node))
		{
			prev = node;
			node = _data.next_sibling[node.i];
		}

		_data.next_sibling[prev.i] = child;

		_data.first_child[child.i].i = UINT32_MAX;
		_data.next_sibling[child.i].i = UINT32_MAX;
		_data.prev_sibling[child.i] = prev;
	}

	Matrix4x4 parent_tr = _data.world[parent.i];
	Matrix4x4 child_tr = _data.world[child.i];
	const Vector3 cs = scale(child_tr);

	Vector3 px = x(parent_tr);
	Vector3 py = y(parent_tr);
	Vector3 pz = z(parent_tr);
	Vector3 cx = x(child_tr);
	Vector3 cy = y(child_tr);
	Vector3 cz = z(child_tr);

	set_x(parent_tr, normalize(px));
	set_y(parent_tr, normalize(py));
	set_z(parent_tr, normalize(pz));
	set_x(child_tr, normalize(cx));
	set_y(child_tr, normalize(cy));
	set_z(child_tr, normalize(cz));

	const Matrix4x4 rel_tr = child_tr * get_inverted(parent_tr);

	_data.local[child.i].position = translation(rel_tr);
	_data.local[child.i].rotation = to_matrix3x3(rel_tr);
	_data.local[child.i].scale = cs;
	_data.parent[child.i] = parent;

	transform(parent_tr, child);
}