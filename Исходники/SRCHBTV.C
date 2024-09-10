void _draw_link(node *p,int x1, int x2, int y)
    {
    if (p != NULL)
	{
	lineto((x1+x2)/2, y);
	_draw_link(p->left, x1, (x1+x2)/2, y+DY);
	moveto((x1+x2)/2, y);
	_draw_link(p->right, (x1+x2)/2, x2, y+DY);
	lineto((x1+x2)/2, y);
	}
    else
	{
	lineto((x1+x2)/2, y);
	moveto((x1+x2)/2, y);
	}
    }