Bolt* LumosChitBag::NewBolt(	const Vector3F& pos,
								const Vector3F& _dir,
								int effectFlags,
								int chitID,
								float damage,
								float speed,
								bool trail )
{
	GLASSERT(pos.y > 0);
	GLASSERT(pos.y < 4);

	Bolt* bolt = ChitBag::NewBolt();

	Vector3F dir = _dir;
	dir.Normalize();
	GLASSERT(Equal(dir.Length(), 1.0f));

	bolt->head = pos + dir * 0.5f;
	bolt->len = 0.5f;
	bolt->dir = dir;

	const Game::Palette* palette = Game::GetMainPalette();

	switch( effectFlags & (GameItem::EFFECT_FIRE | GameItem::EFFECT_SHOCK) ) {
	case 0:													bolt->color = palette->Get4F( 1, PAL_GREEN );	break;
	case GameItem::EFFECT_FIRE:								bolt->color = palette->Get4F( 1, PAL_RED );		break;
	case GameItem::EFFECT_SHOCK:							bolt->color = palette->Get4F( 1, PAL_BLUE );	break;
	case GameItem::EFFECT_FIRE | GameItem::EFFECT_SHOCK:	bolt->color = palette->Get4F( 1, PAL_PURPLE );	break;
	default:
		GLASSERT( 0 );
		break;
	}

	bolt->chitID = chitID;
	bolt->damage = damage;
	bolt->effect = effectFlags;
	bolt->particle  = trail;
	bolt->speed = speed;
	bolt->frameCount = 0;

	return bolt;
}