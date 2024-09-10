int main()
{
    Mercator::Terrain t;

    // Add a null test shader to the terrain
    Mercator::Shader * shader = new TestShader;
    t.addShader(shader, 0);

    // Create a test area with a shape which intersects
    // the Segment at 0,0
    Mercator::Area* a1 = new Mercator::Area(0, false);
    
    WFMath::Polygon<2> p;
    p.addCorner(p.numCorners(), WFMath::Point<2>(3, 4));
    p.addCorner(p.numCorners(), WFMath::Point<2>(10, 10));
    p.addCorner(p.numCorners(), WFMath::Point<2>(14, 6));
    p.addCorner(p.numCorners(), WFMath::Point<2>(18, 4));
    p.addCorner(p.numCorners(), WFMath::Point<2>(17, 19));
    p.addCorner(p.numCorners(), WFMath::Point<2>(6, 20));
    p.addCorner(p.numCorners(), WFMath::Point<2>(-1, 18));
    p.addCorner(p.numCorners(), WFMath::Point<2>(-8, 11));
    
    a1->setShape(p);

    // Add enough base points to force the creation of the Segment at 0,0
    t.setBasePoint(0, 0, -1);
    t.setBasePoint(0, 1, 8);
    t.setBasePoint(1, 0, 2);
    t.setBasePoint(1, 1, 11);

    // Get the Segment at 0,0
    Mercator::Segment * seg = t.getSegmentAtIndex(0,0);

    assert(seg != 0);

    // Get the surfaces, and add one corresponding to the shader we added.
    // We need to do this as the functions that would normally make it happen
    // have been stubbed out.
    Mercator::Segment::Surfacestore & sss = seg->getSurfaces();

    Mercator::Surface * sfce = new Mercator::Surface(*seg, *shader);

    // Force allocation of the surface buffer so we can check later that it
    // gets destroyed when the area is added to the terrain.
    sfce->allocate();
    assert(sfce->isValid());

    // Add the surface to the store for this segment
    sss[0] = sfce;

    // Add the area which should cause relevant surface date to be invalidated
    t.addArea(a1);

    // We assert this to ensure that the buffer has been de-allocated
    // by a call to Surface::invalidate caused by adding the Area.
    assert(!sfce->isValid());

    // force the surface to re-allocate
    sfce->allocate();
    assert(sfce->isValid());

    // Modify the areas shape
    p.addCorner(p.numCorners(), WFMath::Point<2>(-9, 12));
    a1->setShape(p);

    // and cause an area update
    t.updateArea(a1);

    // Check the surface has been invalidated again
    assert(!sfce->isValid());

    // force the surface to re-allocate
    sfce->allocate();
    assert(sfce->isValid());

    t.removeArea(a1);

    // Check the surface has been invalidated again
    assert(!sfce->isValid());
}