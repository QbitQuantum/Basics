int main()
{
    // Test constructor
    {
        Mercator::Forest mf;
    }

    // Test constructor
    {
        Mercator::Forest mf(23);
    }

    // Test getArea()
    {
        Mercator::Forest mf;

        Mercator::Area * a = mf.getArea();

        assert(a == 0);
    }

    // Test species()
    {
        Mercator::Forest mf;

        Mercator::Forest::PlantSpecies & mps = mf.species();

        assert(mps.empty());
    }

    {
        Mercator::Forest forest(4249162ul);

        Mercator::Forest::PlantSpecies & species = forest.species();

        const Mercator::Forest::PlantStore & plants = forest.getPlants();

        // Forest is not yet populated
        assert(plants.empty());
        assert(species.empty());
        forest.populate();
        // Forest has zero area, so even when populated it is empty
        assert(plants.empty());
        assert(species.empty());

        Mercator::Area* ar = new Mercator::Area(1, false);
        WFMath::Polygon<2> p;
        
        p.addCorner(p.numCorners(), Point2(5, 8));
        p.addCorner(p.numCorners(), Point2(40, -1));
        p.addCorner(p.numCorners(), Point2(45, 16));
        p.addCorner(p.numCorners(), Point2(30, 28));
        p.addCorner(p.numCorners(), Point2(-2, 26));
        p.addCorner(p.numCorners(), Point2(1, 5));
        
        ar->setShape(p);
        forest.setArea(ar);

        forest.populate();
        // Forest has no species, so even when populated it is empty
        assert(plants.empty());
        assert(species.empty());

        {
            Mercator::Species pine;
            pine.m_probability = 0.04;
            pine.m_deviation = 1.f;

            species.push_back(pine);
        }

        forest.populate();
        // Forest should now contain some plants
        assert(!plants.empty());

        dumpPlants(plants);

        int plant_count = countPlants(plants);

        {
            Mercator::Species oak;
            oak.m_probability = 0.02;
            oak.m_deviation = 1.f;

            species.push_back(oak);
        }

        forest.populate();
        // Forest should now contain some plants
        assert(!plants.empty());
        assert(countPlants(plants) > plant_count);

        dumpPlants(plants);

        std::cout << countPlants(plants) << "," << plant_count
                  << std::endl << std::flush;

    }
}