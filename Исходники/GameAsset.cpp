void GameAsset::draw() {
  glUseProgram(program);

  
  Vector4 tx = Camera::getInstance().getCameraM() * *(bbox->getCentre());
  float tx_unpacked[] = {tx.getX(), tx.getY(), tx.getZ(), tx.getW()};

  //  std::cout << "tx.x " << tx.getX() << "\ttx.y " << tx.getY() << "\t tx.z " << tx.getZ() << std::endl;
  
  glUniform4fv(tx_uniform, 1, tx_unpacked);

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glVertexAttribPointer(
			position_attrib,                  /* attribute */
			3,                                /* size */
			GL_FLOAT,                         /* type */
			GL_FALSE,                         /* normalized? */
			0,                                /* stride */
			(void*)0                          /* array buffer offset */
			);
  glEnableVertexAttribArray(position_attrib);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
  glDrawElements(
		 GL_TRIANGLES,
		 3 * this->num_triangles,
		 GL_UNSIGNED_SHORT,
		 (GLvoid*) 0
		 );
  
  glDisableVertexAttribArray(position_attrib);
}