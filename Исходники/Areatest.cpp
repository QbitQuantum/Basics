int main(int argc, char* argv[])
{
    Mercator::Area* a1 = new Mercator::Area(1, false);
    
    WFMath::Polygon<2> p;
    p.addCorner(p.numCorners(), Point2(3, 4));
    p.addCorner(p.numCorners(), Point2(10, 10));
    p.addCorner(p.numCorners(), Point2(-1, 18));
    p.addCorner(p.numCorners(), Point2(-8, 11));
    
    a1->setShape(p);
    
    Mercator::Terrain terrain(Mercator::Terrain::SHADED, seg_size);

    Mercator::AreaShader* ashade = new Mercator::AreaShader(1);
    terrain.addShader(ashade, 0);
    
    terrain.setBasePoint(-2, -1, 5);
    terrain.setBasePoint(-2, 0, 2);
    terrain.setBasePoint(-2, 1, 19);
    
    terrain.setBasePoint(-1, -1, 4);
    terrain.setBasePoint(-1, 0, 6);
    terrain.setBasePoint(-1, 1, 10);
    
    terrain.setBasePoint(0, -1, 2);
    terrain.setBasePoint(0, 0, -1);
    terrain.setBasePoint(0, 1, 8);
    terrain.setBasePoint(0, 2, 11);
    
    terrain.setBasePoint(1, -1, 7);
    terrain.setBasePoint(1, 0, 2);
    terrain.setBasePoint(1, 1, 11);
    terrain.setBasePoint(1, 2, 9);
    
    terrain.setBasePoint(2, -1, 3);
    terrain.setBasePoint(2, 0, 8);
    terrain.setBasePoint(2, 1, 2);

    terrain.setBasePoint(3, -1, 6);
    terrain.setBasePoint(3, 0, 7);
    terrain.setBasePoint(3, 1, 9);
    
    terrain.addArea(a1);
    
    Mercator::Segment* seg = terrain.getSegment(0,0);
    assert(seg->getAreas().size() == 1);
    assert(seg->getAreas().count(1) == 1);
    assert(a1->checkIntersects(*seg));
    
    seg = terrain.getSegment(1,0);
    assert(seg->getAreas().size() == 0);
    assert(seg->getAreas().count(1) == 0);
    assert(a1->checkIntersects(*seg) == false);

    WFMath::Polygon<2> clipped = a1->clipToSegment(*seg);
    assert(clipped.isValid());
    
    seg = terrain.getSegment(-1,0);
    assert(seg->getAreas().size() == 1);
    assert(seg->getAreas().count(1) == 1);
    assert(a1->checkIntersects(*seg));
    
    clipped = a1->clipToSegment(*seg);
    assert(clipped.isValid());
    
    seg = terrain.getSegment(0,1);
    assert(seg->getAreas().size() == 1);
    assert(seg->getAreas().count(1) == 1);
    assert(a1->checkIntersects(*seg));
    
    clipped = a1->clipToSegment(*seg);
    assert(clipped.isValid());

    seg = terrain.getSegment(2,0);
    assert(seg->getAreas().size() == 0);
    assert(seg->getAreas().count(1) == 0);
    assert(a1->checkIntersects(*seg) == false);

    p.clear();
    p.addCorner(p.numCorners(), Point2(3 + seg_size, 4));
    p.addCorner(p.numCorners(), Point2(10 + seg_size, 10));
    p.addCorner(p.numCorners(), Point2(-1 + seg_size, 18));
    p.addCorner(p.numCorners(), Point2(-8 + seg_size, 11));
    
    a1->setShape(p);

    terrain.updateArea(a1);

    seg = terrain.getSegment(0,0);
    assert(seg->getAreas().size() == 1);
    assert(seg->getAreas().count(1) == 1);
    assert(a1->checkIntersects(*seg));
    
    seg = terrain.getSegment(1,0);
    assert(seg->getAreas().size() == 1);
    assert(seg->getAreas().count(1) == 1);
    assert(a1->checkIntersects(*seg));

    clipped = a1->clipToSegment(*seg);
    assert(clipped.isValid());
    
    seg = terrain.getSegment(-1,0);
    assert(seg->getAreas().size() == 0);
    assert(seg->getAreas().count(1) == 0);
    assert(a1->checkIntersects(*seg) == false);
    
    seg = terrain.getSegment(0,1);
    assert(seg->getAreas().size() == 1);
    assert(seg->getAreas().count(1) == 1);
    assert(a1->checkIntersects(*seg));
    
    clipped = a1->clipToSegment(*seg);
    assert(clipped.isValid());

    seg = terrain.getSegment(2,0);
    assert(seg->getAreas().size() == 0);
    assert(seg->getAreas().count(1) == 0);
    assert(a1->checkIntersects(*seg) == false);

    clipped = a1->clipToSegment(*seg);
    assert(clipped.isValid());

    terrain.removeArea(a1);

    seg = terrain.getSegment(0,0);
    assert(seg->getAreas().size() == 0);
    assert(seg->getAreas().count(1) == 0);

    seg = terrain.getSegment(1,0);
    assert(seg->getAreas().size() == 0);
    assert(seg->getAreas().count(1) == 0);

    seg = terrain.getSegment(-1,0);
    assert(seg->getAreas().size() == 0);
    assert(seg->getAreas().count(1) == 0);

    seg = terrain.getSegment(0,1);
    assert(seg->getAreas().size() == 0);
    assert(seg->getAreas().count(1) == 0);

    testAreaShader();

    testAddToSegment();
    
    return EXIT_SUCCESS;
}