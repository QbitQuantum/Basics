void SunMoonStripWidget::display_moons(uint8 day, uint8 hour, uint8 minute)
{
    uint8 phase = 0;
    // trammel (starts 1 hour ahead of sun)
    phase = uint8(nearbyint((day-1)/TRAMMEL_PHASE)) % 8;
    Tile *tileA = tile_manager->get_tile((phase == 0) ? 584 : 584 + (8-phase)); // reverse order in tilelist
    uint8 posA = ((hour + 1) + 3*phase) % 24; // advance 3 positions each phase-change

    // felucca (starts 1 hour behind sun)
    // ...my FELUCCA_PHASE may be wrong but this method works with it...
    sint8 phaseb = (day-1) % uint8(nearbyint(FELUCCA_PHASE*8)) - 1;
    phase = (phaseb >= 0) ? phaseb : 0;
    Tile *tileB = tile_manager->get_tile((phase == 0) ? 584 : 584 + (8-phase)); // reverse order in tilelist
    uint8 posB = ((hour - 1) + 3*phase) % 24; // advance 3 positions per phase-change

    if(posA >= 5 && posA <= 19)
        display_sun_moon(tileA, posA - 5);
    if(posB >= 5 && posB <= 19)
        display_sun_moon(tileB, posB - 5);
}