int
o_instance(			/* determine if instance intersects */
	OBJREC  *o,
	CUBE  *cu
)
{
	INSTANCE  *ins;
					/* get octree bounds */
	ins = getinstance(o, IO_BOUNDS);
					/* call o_cube to do the work */
	return(o_cube(&ins->obj->scube, &ins->x, cu));
}