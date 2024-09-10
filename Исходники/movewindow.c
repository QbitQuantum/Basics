static WINDOW *
create_my_subwin(WINDOW *parent)
{
    PAIR ul, lr;
    WINDOW *result = 0;

    if (getwindow(parent, &ul, &lr)) {
	result = subwin(parent,
			lines_of(ul, lr),
			cols_of(ul, lr),
			ul.y + getbegy(parent),
			ul.x + getbegx(parent));
	if (result != 0) {
	    fill_window(result, 's');
	    add_window(parent, result);
	}
    }
    if (result == 0)
	result = parent;
    return result;
}