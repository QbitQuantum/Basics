int main(int argc, char **argv)
{
    /* Set some default behaviors. */

    const char *i = "rect";
    const char *o = "rect";
    const char *p = "rgss";
    const char *f = "linear";

    float rot[3] = { 0.f, 0.f, 0.f };

    int n = 1024;
    int c;

    /* Parse the command line options. */

    while ((c = getopt(argc, argv, "i:o:p:n:f:x:y:z:")) != -1)
        switch (c)
        {
            case 'i': i      = optarg;               break;
            case 'o': o      = optarg;               break;
            case 'p': p      = optarg;               break;
            case 'f': f      = optarg;               break;
            case 'x': rot[0] = strtod(optarg, 0);    break;
            case 'y': rot[1] = strtod(optarg, 0);    break;
            case 'z': rot[2] = strtod(optarg, 0);    break;
            case 'n': n      = strtol(optarg, 0, 0); break;

            default: return usage(argv[0]);
        }

    int      num = 1;
    image   *src = 0;
    image   *dst = 0;
    image   *tmp = 0;
    to_img   img;
    to_env   env;
    filter   fil;

    /* Select the sampler. */

    if      (!strcmp(f, "linear"))  fil = filter_linear;
    else if (!strcmp(f, "nearest")) fil = filter_nearest;
    else return usage(argv[0]);

    /* Read the input image. */

    if (optind + 2 <= argc)
    {
        if      (!strcmp(i, "cube"))
        {
            tmp = image_reader(argv[optind], 6);
            src = image_border(tmp);
            img = cube_to_img;
        }
        else if (!strcmp(i, "dome"))
        {
            src = image_reader(argv[optind], 1);
            img = dome_to_img;
        }
        else if (!strcmp(i, "hemi"))
        {
            src = image_reader(argv[optind], 1);
            img = hemi_to_img;
        }
        else if (!strcmp(i, "ball"))
        {
            src = image_reader(argv[optind], 1);
            img = ball_to_img;
        }
        else if (!strcmp(i, "rect"))
        {
            src = image_reader(argv[optind], 1);
            img = rect_to_img;
        }
        else return usage(argv[0]);
    }
    else return usage(argv[0]);

    /* Prepare the output image. */

    if (src)
    {
        if      (!strcmp(o, "cube"))
        {
            dst = image_alloc((num = 6), n, n, src->c, src->b, src->s);
            env = cube_to_env;
        }
        else if (!strcmp(o, "dome"))
        {
            dst = image_alloc((num = 1), n, n, src->c, src->b, src->s);
            env = dome_to_env;
        }
        else if (!strcmp(o, "hemi"))
        {
            dst = image_alloc((num = 1), n, n, src->c, src->b, src->s);
            env = hemi_to_env;
        }
        else if (!strcmp(o, "ball"))
        {
            dst = image_alloc((num = 1), n, n, src->c, src->b, src->s);
            env = ball_to_env;
        }
        else if (!strcmp(o, "rect"))
        {
            dst = image_alloc((num = 1), n, 2 * n, src->c, src->b, src->s);
            env = rect_to_env;
        }
        else return usage(argv[0]);
    }

    /* Perform the remapping using the selected pattern. */

    if (src && dst)
    {
        if      (!strcmp(p, "cent"))
            process(src, dst, &cent_pattern, rot, fil, img, env, num);

        else if (!strcmp(p, "rgss"))
            process(src, dst, &rgss_pattern, rot, fil, img, env, num);

        else if (!strcmp(p, "box2"))
            process(src, dst, &box2_pattern, rot, fil, img, env, num);

        else if (!strcmp(p, "box3"))
            process(src, dst, &box3_pattern, rot, fil, img, env, num);

        else if (!strcmp(p, "box4"))
            process(src, dst, &box4_pattern, rot, fil, img, env, num);

        else return usage(argv[0]);

        /* Write the output. */

        image_writer(argv[optind + 1], dst, num);
    }

    return 0;
}