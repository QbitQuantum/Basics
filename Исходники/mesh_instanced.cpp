void			neb::gfx::mesh::instanced::draw(
		neb::gfx::mesh::instanced::program_type*		program,
		std::shared_ptr<neb::gfx::glsl::buffer::instanced>	buf)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	assert(instances_);

	//auto buf_mesh = mesh_.getBuffer(program);
	auto bt = mesh_.getBufferTuple(program);

	buf->vertexAttribPointer();
	//buf_mesh->vertexAttribPointer();
	
	mesh_.vertexAttribPointer(bt);

	LOG(lg, neb::gfx::sl, debug) << "instances size = " << instances_->size();
	LOG(lg, neb::gfx::sl, debug) << "mesh size      = " << mesh_.getNbIndices();

	mesh_.bind(bt);

	auto s = instances_->size();

	glDrawElementsInstanced(
			GL_TRIANGLES,
			mesh_.getNbIndices(),
			GL_UNSIGNED_SHORT,
			0,
			s);

	checkerror("glDrawElementsInstanced");

	mesh_.unbind(bt);
}