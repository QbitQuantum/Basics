// Function allocates and init a Game
static game_p gameNew(engine_p engine,
                      board_p board)
{
    game_p game = NULL;
    context_p screen = NULL;
    int hd = 0;

    ASSERT(NULL != board, "gameNew");

    game = (game_p)objectCreate(
        sizeof(game_t),
        (destructor_f)gameDestroy);

    game->board = boardRetain(board);

    screen = engineScreen(engine);

    game->width = contextWidth(screen);
    game->height = contextHeight(screen);
    game->padding = (game->width < game->height
                         ? game->width
                         : game->height) / 64;

    hd = engineHDSupported(engine);

    game->regular = fontRetain(
        fontLoad(hd ? fontNameRegularHD
                    : fontNameRegularSD));
    game->bold = fontRetain(fontLoad(
        hd ? fontNameBoldHD : fontNameBoldSD));

    game->status_line
        = MAX(fontLine(game->regular),
              fontLine(game->bold));

    game->images[0] = imageRetain(
        imageLoad(hd ? imageNameEmptyHD
                     : imageNameEmptySD));
    game->images[1] = imageRetain(imageLoad(
        hd ? imageName2HD : imageName2SD));
    game->images[2] = imageRetain(imageLoad(
        hd ? imageName4HD : imageName4SD));
    game->images[3] = imageRetain(imageLoad(
        hd ? imageName8HD : imageName8SD));
    game->images[4] = imageRetain(imageLoad(
        hd ? imageName16HD : imageName16SD));
    game->images[5] = imageRetain(imageLoad(
        hd ? imageName32HD : imageName32SD));
    game->images[6] = imageRetain(imageLoad(
        hd ? imageName64HD : imageName64SD));
    game->images[7] = imageRetain(imageLoad(
        hd ? imageName128HD : imageName128SD));
    game->images[8] = imageRetain(imageLoad(
        hd ? imageName256HD : imageName256SD));
    game->images[9] = imageRetain(imageLoad(
        hd ? imageName512HD : imageName512SD));
    game->images[10] = imageRetain(imageLoad(
        hd ? imageName1024HD : imageName1024SD));
    game->images[11] = imageRetain(imageLoad(
        hd ? imageName2048HD : imageName2048SD));
    game->images[12] = imageRetain(imageLoad(
        hd ? imageName4096HD : imageName4096SD));
    game->images[13] = imageRetain(imageLoad(
        hd ? imageName8192HD : imageName8192SD));
    game->images[14] = imageRetain(
        imageLoad(hd ? imageName16384HD
                     : imageName16384SD));
    game->images[15] = imageRetain(
        imageLoad(hd ? imageName32768HD
                     : imageName32768SD));
    game->images[16] = imageRetain(
        imageLoad(hd ? imageName65536HD
                     : imageName65536SD));
    game->images[17] = imageRetain(
        imageLoad(hd ? imageName131072HD
                     : imageName131072SD));

    game->cell
        = MIN(imageWidth(game->images[0]),
              imageHeight(game->images[0]));

    game->board_back = rgbColor(0xBB, 0xAD, 0xA0);

    return game;
};