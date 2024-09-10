void
sanguis::client::draw2d::scene::background::render(
	sge::renderer::context::core &_render_context,
	sanguis::client::draw2d::translation const _translation
)
{
	sprite_.texture_coordinates(
		sanguis::client::draw2d::scene::background_texture_coordinates(
			sanguis::client::draw2d::translation{
				(
					_translation.get()
					/
					fcppt::literal<
						sanguis::client::draw2d::unit
					>(
						2
					)
				).get_unsafe()
			},
			client_system_.renderer(),
			texture_
		)
	);

	client_system_.render(
		_render_context,
		sanguis::client::draw2d::sprite::client::category::background
	);
}