static void sub_80CA8B4(struct Sprite* sprite)
{
    if (TranslateAnimSpriteByDeltas(sprite))
    {
        DestroySprite(sprite);
    }
    else
    {
        if (sprite->data[5] > 0x7F)
        {
            sprite->subpriority = sub_8079E90(gAnimBankTarget) + 1;
        }
        else
        {
            sprite->subpriority = sub_8079E90(gAnimBankTarget) + 6;
        }
        sprite->pos2.x += Sin(sprite->data[5], 5);
        sprite->pos2.y += Cos(sprite->data[5], 14);
        sprite->data[5] = (sprite->data[5] + 15) & 0xFF;
    }
}