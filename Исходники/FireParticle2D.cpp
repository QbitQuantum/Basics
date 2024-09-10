// draw
//---------------------------------------------------------------------------
// Purpose: Draws a single particle, no simulation.
//---------------------------------------------------------------------------
void FireParticle2D::draw(Surface &dest, SpriteSorter &sorter)
{
    //if (!isAlive) return;
    dest.fillRect(100, 100, 110, 110, Color::red);

    //int x = (int) pos.x;
    //int y = pos.y;
    //int z = (int) pos.z;

    //color = uint8_t(totalTime * 44); // This 44 is based on the life of 0.25 secs and 12 colors possible.
    color = uint8_t(totalTime * 22); // This 22 is based on the life of 0.50 secs and 12 colors possible.

    //if (color >= 12) throw Exception("ERROR: Invalid color reached for fire.");
    assert(color < 12);

    // const unsigned halfSize = 1;

    //dest.fillRect(iRect(x - halfSize, z - halfSize, x + halfSize, z + halfSize), cFireParticleSystem2D::fireColor[color]);

} // end FireParticle2D::draw