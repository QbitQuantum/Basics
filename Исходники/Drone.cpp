void Drone::draw(SpriteBuffer& sprite_buffer, const Camera& camera) const {
	Sprite drone_spr;
	drone_spr.setImg(34, 1, 24, 24);
	drone_spr.setPos(camera.transform(rb.pos));

	SpriteMatrix matrix;
	matrix.loadIdentity().rotate(angle);

	sprite_buffer.append(drone_spr, matrix);

	if (anim_flags.test(AnimationFlags::YELLOW_STROBE)) {
		drone_spr.img_y = 1+1*25;
		sprite_buffer.append(drone_spr, matrix);
	}

	if (anim_flags.test(AnimationFlags::RED_STROBE)) {
		drone_spr.img_y = 1+2*25;
		sprite_buffer.append(drone_spr, matrix);
	}
}