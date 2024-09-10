RadioView::RadioView(Window* c)
: View(c), sim(0), ship(0), font(0), dst_elem(0)
{
	radio_view  = this;
	sim         = Sim::GetSim();

	width       = window->Width();
	height      = window->Height();
	xcenter     = (width  / 2.0) - 0.5;
	ycenter     = (height / 2.0) + 0.5;
	font        = FontMgr::Find("HUD");

	HUDView* hud = HUDView::GetInstance();
	if (hud)
	SetColor(hud->GetTextColor());

	for (int i = 0; i < MAX_MSG; i++)
	msg_time[i] = 0;
}