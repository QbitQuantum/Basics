void KisMaskGenerator::init()
{
    d->cs = cos(- 2 * M_PI / d->spikes);
    d->ss = sin(- 2 * M_PI / d->spikes);
    d->empty = (d->ratio == 0.0 || d->diameter == 0.0);
}