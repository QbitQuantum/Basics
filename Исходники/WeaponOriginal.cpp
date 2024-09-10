void *Weapon::operator new(size_t aSize)
{
	return pool.malloc();
}