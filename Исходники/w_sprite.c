InitSprite(SimSprite *sprite, int x, int y)
{
  sprite->x = x; sprite->y = y;
  sprite->frame = 0;
  sprite->orig_x = sprite->orig_y = 0;
  sprite->dest_x = sprite->dest_y = 0;
  sprite->count = sprite->sound_count = 0;
  sprite->dir = sprite->new_dir = 0;
  sprite->step = sprite->flag = 0;
  sprite->control = -1;
  sprite->turn = 0;
  sprite->accel = 0;
  sprite->speed = 100;

  if (GlobalSprites[sprite->type] == NULL) {
    GlobalSprites[sprite->type] = sprite;
  }

  switch (sprite->type) {

  case TRA:
    sprite->width = sprite->height = 32;
    sprite->x_offset = 32; sprite->y_offset = -16;
    sprite->x_hot = 40; sprite->y_hot = -8;
    sprite->frame = 1;
    sprite->dir = 4;
    break;

  case SHI:
    sprite->width = sprite->height = 48;
    sprite->x_offset = 32; sprite->y_offset = -16;
    sprite->x_hot = 48; sprite->y_hot = 0;
    if (x < (4 <<4)) sprite->frame = 3;
    else if (x >= ((WORLD_X - 4) <<4)) sprite->frame = 7;
    else if (y < (4 <<4)) sprite->frame = 5;
    else if (y >= ((WORLD_Y - 4) <<4)) sprite->frame = 1;
    else sprite->frame = 3;
    sprite->new_dir = sprite->frame;
    sprite->dir = 10;
    sprite->count = 1;
    break;

  case GOD:
    sprite->width = sprite->height = 48;
    sprite->x_offset = 24; sprite->y_offset = 0;
    sprite->x_hot = 40; sprite->y_hot = 16;
    if (x > ((WORLD_X <<4) / 2)) {
      if (y > ((WORLD_Y <<4) / 2)) sprite->frame = 10;
      else sprite->frame = 7;
    } else if (y > ((WORLD_Y <<4) / 2)) sprite->frame = 1;
    else sprite->frame = 4;
    sprite->count = 1000;
    sprite->dest_x = PolMaxX <<4;
    sprite->dest_y = PolMaxY <<4;
    sprite->orig_x = sprite->x;
    sprite->orig_y = sprite->y;
    break;

  case COP:
    sprite->width = sprite->height = 32;
    sprite->x_offset = 32; sprite->y_offset = -16;
    sprite->x_hot = 40; sprite->y_hot = -8;
    sprite->frame = 5;
    sprite->count = 1500;
    sprite->dest_x = Rand((WORLD_X <<4) - 1);
    sprite->dest_y = Rand((WORLD_Y <<4) - 1);
    sprite->orig_x = x - 30;
    sprite->orig_y = y;
    break;

  case AIR:
    sprite->width = sprite->height = 48;
    sprite->x_offset = 24; sprite->y_offset = 0;
    sprite->x_hot = 48; sprite->y_hot = 16;
    if (x > ((WORLD_X - 20) <<4)) {
      sprite->x -= 100 + 48;
      sprite->dest_x = sprite->x - 200;
      sprite->frame = 7;
    } else {
      sprite->dest_x = sprite->x + 200;
      sprite->frame = 11;
    }
    sprite->dest_y = sprite->y;
    break;

  case TOR:
    sprite->width = sprite->height = 48;
    sprite->x_offset = 24; sprite->y_offset = 0;
    sprite->x_hot = 40; sprite->y_hot = 36;
    sprite->frame = 1;
    sprite->count = 200;
    break;

  case EXP:
    sprite->width = sprite->height = 48;
    sprite->x_offset = 24; sprite->y_offset = 0;
    sprite->x_hot = 40; sprite->y_hot = 16;
    sprite->frame = 1;
    break;

  case BUS:
    sprite->width = sprite->height = 32;
    sprite->x_offset = 30; sprite->y_offset = -18;
    sprite->x_hot = 40; sprite->y_hot = -8;
    sprite->frame = 1;
    sprite->dir = 1;
    break;

  }
}