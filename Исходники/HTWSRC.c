void give_parameter (HTStream * me, int p)
{
    PUTS(par_name[p]);
    if (me->par_value[p]) {
	PUTS(": ");
	PUTS(me->par_value[p]);
	PUTS("; ");
    } else {
        PUTS(" NOT GIVEN in source file; ");
    }
}