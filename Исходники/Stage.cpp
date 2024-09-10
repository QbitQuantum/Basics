void StageMenu::render() 
{
	game = Game::instance;

	if (!to_select_plane) {
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		Camera cam2D;

		cam2D.setOrthographic(0, game->window_width, game->window_height, 0, -1, 1);
		cam2D.set();

		Mesh quad;
		quad.createQuad(game->window_width * 0.5, game->window_height * 0.5, game->window_width, game->window_height, true);

		Texture* menu = Texture::get("data/stage/Menu2.tga");

		menu->bind();
		quad.render(GL_TRIANGLES);
		menu->unbind();
	}
	else {
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera->set();

		plane_to_select->render(camera);

		drawGrid(500); //background grid

		drawText(180,225, plane_to_select->name, Vector3(1, 1, 1), 2);

		glDisable(GL_BLEND);

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		Camera cam2D;
		cam2D.setOrthographic(0, game->window_width, game->window_height, 0, -1, 1);
		cam2D.set();

		Mesh quad;
		quad.createQuad(game->window_width*0.5, game->window_height*0.5, game->window_width, game->window_height, true);

		Texture* menuSelection = Texture::get("data/stage/MenuSelection.tga");

		//ACtivar la transparencia
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		menuSelection->bind();
		quad.render(GL_TRIANGLES);
		menuSelection->unbind();
		glDisable(GL_BLEND);

	}
}