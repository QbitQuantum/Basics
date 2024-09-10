PyObject *KX_MouseFocusSensor::pyattr_get_ray_direction(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef)
{
	KX_MouseFocusSensor* self = static_cast<KX_MouseFocusSensor*>(self_v);
	MT_Vector3 dir = self->RayTarget() - self->RaySource();
	if (MT_fuzzyZero(dir))	dir.setValue(0,0,0);
	else					dir.normalize();
	return PyObjectFrom(dir);
}