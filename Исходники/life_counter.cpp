void LifeCounter::Draw(mat4 view, mat4 projection) {
	projection = ortho(0.0f, 20.0f * (scene->width / (float)scene->height), 0.0f, 20.0f, -20.0f, 20.0f);
	for(int i=0; i<lives; i++) {
		Content::shader(basic).Begin();
			mat4 model = translation(position + vec3(i * icon.size.x, 0, 0))  * mat4_cast(orientation) * scale(size);
			model = model;
			glUniformMatrix4fv(Content::shader(basic)("inv_view"), 1, GL_FALSE, &(model[0][0]));
			icon.Draw(model, projection);
		Content::shader(basic).End();
	}
}