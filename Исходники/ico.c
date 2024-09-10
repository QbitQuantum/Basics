void
apply(void (*f)(Icon*))
{
	Icon *icon;

	esetcursor(&sight);
	buttons(Down);
	if(mouse.buttons == 4)
		for(icon = h.first; icon; icon = icon->next)
			if(ptinrect(mouse.xy, icon->sr)){
				buttons(Up);
				f(icon);
				break;
			}
	buttons(Up);
	esetcursor(0);
}