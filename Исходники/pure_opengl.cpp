void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT);

	static sf::Clock a_timer;
	static bool a_first_time = true;
	if (a_first_time) {
		a_first_time = false;
		a_timer.restart ();
	}
	float dt = a_timer.getElapsedTime ().asSeconds ();
	a_timer.restart ();
	// ֲ�גמה ג פאיכ פןס ט הוכ�עא ׂ
	//static FILE *out = fopen ((prefix_path + "inf/out.txt").c_str (), "w");
	//fprintf (out, "%4d %10g\n", int(1/dt), dt);
	if (in.kb.escape.pressed_now) {
		exit (0);
	}
	core.update (dt);
	core.render ();

	core.m_renderer.draw_everything ();

    glutSwapBuffers();
}