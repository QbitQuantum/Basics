int SetOffsetFromVSB(TextEdition *te)
{
    int h = te->pos.h - HSBHeight(*te);
    double z = te->tab[te->lastLine][0].y + te->hSpace - h;

    if (!te->VScrollBar)
        return 0;

    if (te->posVSB.y < 0)
        te->posVSB.y = 0;
    if (te->posVSB.y > te->pos.h - HSBHeight(*te) - te->VScrollBar->h)
        te->posVSB.y = te->pos.h - HSBHeight(*te) - te->VScrollBar->h;

    te->offsetY = -(te->posVSB.y * (Ceil(z/te->hSpace)*te->hSpace)) / (h - te->VScrollBar->h);
    te->offsetY = Ceil(te->offsetY*1.0/te->hSpace) * te->hSpace;
    return 1;
}