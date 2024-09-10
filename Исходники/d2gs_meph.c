void moveto(int x, int y) {
	point_t p = { x, y };

	plugin_print("meph", "moving to %i/%i\n", (word) p.x, (word) p.y);

	int t = DISTANCE(bot.location, p) * 80;

	d2gs_send(0x03, "%w %w", (word) p.x, (word) p.y);

	plugin_debug("pes", "sleeping for %ims\n", t);
	
	msleep(t > 3000 ? 3000 : t);
}