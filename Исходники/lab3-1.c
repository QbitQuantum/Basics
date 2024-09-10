void render_windmill(struct Windmill* windmill, GLuint program, float time)
{
	mat4 rot, trans, scale, total;

	scale = S(1, 1, 1);
	rot = Rx(-time * 4);
	rot = IdentityMatrix();
	trans = T(windmill->position.x, windmill->position.y, windmill->position.z);
	total = Mult(scale, rot);
	total = Mult(trans, total);
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);	// Upload matrix

	// Draw the windmill
	DrawModel(windmill->balcony, program, "in_Position", "in_Normal", "inTexCoord");
	DrawModel(windmill->walls, program, "in_Position", "in_Normal", "inTexCoord");
	DrawModel(windmill->roof, program, "in_Position", "in_Normal", "inTexCoord");

	// Draw the blades
	trans = T(windmill->position.x+5, windmill->position.y+10, windmill->position.z);

	// 1
	rot = Rx(0 + time);
	total = Mult(trans, rot);
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);	// Upload matrix
	DrawModel(windmill->blade, program, "in_Position", "in_Normal", "inTexCoord");

	// 2
	rot = Rx(3.14f/2.0f + time);
	total = Mult(trans, rot);
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);	// Upload matrix
	DrawModel(windmill->blade, program, "in_Position", "in_Normal", "inTexCoord");

	// 3
	rot = Rx(3.14f + time);
	total = Mult(trans, rot);
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);	// Upload matrix
	DrawModel(windmill->blade, program, "in_Position", "in_Normal", "inTexCoord");

	// 3
	rot = Rx(-3.14f/2.0f + time);
	total = Mult(trans, rot);
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);	// Upload matrix
	DrawModel(windmill->blade, program, "in_Position", "in_Normal", "inTexCoord");

}