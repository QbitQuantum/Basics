void TubeGenerator::generateCarbonTube(int n1, int n2, int k, float transition, float bondLength, std::vector<Molecule::Atom>& atoms, std::vector<Molecule::Link>& links)
{
    if (n1 < n2)
        std::swap(n1, n2);

    atoms.clear();
    links.clear();

    gameplay::Vector2 a1(1.7320508f, 0.0f);
    gameplay::Vector2 a2(-0.8660254f, 1.5f);

    gameplay::Vector2 R = (a1 * static_cast<float>(n1) + a2 * static_cast<float>(n2))* bondLength;
    gameplay::Vector2 L(-R.y, R.x);
    L.normalize();
    L.scale(k * bondLength);

    int ymin = -1;
    int ymax = static_cast<int>(ceilf(std::max(L.y, R.y) / bondLength)) + 1;
    int xmin = static_cast<int>(floorf(L.x / bondLength / a1.x)) - 1;
    int xmax = static_cast<int>(ceilf(R.x / bondLength / a1.x - a2.x * ymax)) + 1;

    std::map<std::tuple<int, int, int>, int> clippedAtoms;
    
    float Rlen = R.length();
    float Llen = L.length();
    float eps = 0.0001f;

    for (int y = ymin; y <= ymax; y++)
        for (int x = xmin; x <= xmax; x++)
        {
            // process hexagon atoms
            gameplay::Vector2 hexagonCenter(x * bondLength * a1.x + a2.x * y * bondLength, y * bondLength * a2.y);

            // process only two hexagon's atoms
            // these are unique to hexagon
            // the rest will be processed by other hexagons
            // each atom then can be uniquely defined by hexagon coordinates (x, y) and one index (0-1)
            for (int i = 0; i < 2; i++)
            {
                float phi = MATH_PI / 6.0f + MATH_PI / 3.0f * i;

                gameplay::Vector2 atomPosition(cosf(phi), sinf(phi));
                atomPosition = hexagonCenter + atomPosition * bondLength;

                // clip atoms by square defined by R and L vectors
                float u = gameplay::Vector2::dot(atomPosition, R) / Rlen;
                float v = gameplay::Vector2::dot(atomPosition, L) / Llen;

                if (u >= -eps && v >= -eps && u < Rlen - eps && v < Llen - eps)
                {
                    clippedAtoms.insert(std::make_pair(std::make_tuple(x, y, i), static_cast<int>(atoms.size())));
                    atoms.push_back({ 1, 0.0f, gameplay::Vector3(u, v, 0.0f) });
                    //atoms.push_back({ 1, 0.0f, gameplay::Vector3(atomPosition.x, atomPosition.y, 0.0f) });
                }
            }
        }

    std::vector<std::tuple<int, int, int>> unboundAtoms;

    // check links
    for (auto it = clippedAtoms.begin(), end_it = clippedAtoms.end(); it != end_it; it++)
    {
        int x = std::get<0>((*it).first);
        int y = std::get<1>((*it).first);

        if (std::get<2>((*it).first) == 0)
        {
            auto next = clippedAtoms.find(std::make_tuple(x, y, 1));
            if (next != clippedAtoms.end())
                links.push_back({ (*it).second, (*next).second, 1 });
            else
                unboundAtoms.push_back((*it).first);

            next = clippedAtoms.find(std::make_tuple(x, y - 1, 1));
            if (next != clippedAtoms.end())
                links.push_back({ (*it).second, (*next).second, 1 });
            else
                unboundAtoms.push_back((*it).first);

            next = clippedAtoms.find(std::make_tuple(x + 1, y, 1));
            if (next != clippedAtoms.end())
                links.push_back({ (*it).second, (*next).second, 1 });
            else
                unboundAtoms.push_back((*it).first);
        }
    }

    // bend graphene
    if (transition > 0.0f)
    {
        for (auto it = atoms.begin(), end_it = atoms.end(); it != end_it; it++)
        {
            float radius = R.length() / MATH_PIX2 / transition;
            float phi = (*it).pos.x / radius;
            (*it).pos.x = radius * sinf(phi);
            (*it).pos.z = radius * cosf(phi);
        }
    }

    // add new links
    //for (auto it = unboundAtoms.begin(), end_it = unboundAtoms.end(); it != end_it; it++)
    //{
    //    auto first = clippedAtoms.find(std::make_tuple(x, y, 0));
    //    if (first != clippedAtoms.end())
    //    {
    //        auto next = clippedAtoms.find(std::make_tuple(x, y, 1));
    //        if (next == clippedAtoms.end())
    //        {
    //            for (int x1 = xmax; x1 > x; x1--)
    //            {
    //                auto last = clippedAtoms.find(std::make_tuple(x1, y, 1));
    //                if (last != clippedAtoms.end())
    //                {
    //                    links.push_back({ (*first).second, (*last).second, 1 });
    //                    break;
    //                }
    //            }
    //        }

    //        next = clippedAtoms.find(std::make_tuple(x, y - 1, 1));
    //        if (next == clippedAtoms.end())
    //        {
    //            for (int x1 = xmin; x1 < x; x1++ )
    //            {
    //                auto last = clippedAtoms.find(std::make_tuple(x1, y - 1, 1));
    //                if (last != clippedAtoms.end())
    //                {
    //                    links.push_back({ (*first).second, (*last).second, 1 });
    //                    break;
    //                }
    //            }
    //        }

    //        next = clippedAtoms.find(std::make_tuple(x + 1, y, 1));
    //        if (next == clippedAtoms.end())
    //        {
    //            for (int x1 = xmin; x1 < x; x1++)
    //            {
    //                auto last = clippedAtoms.find(std::make_tuple(x1, y, 1));
    //                if (last != clippedAtoms.end())
    //                {
    //                    links.push_back({ (*first).second, (*last).second, 1 });
    //                    break;
    //                }
    //            }
    //        }
    //    }
    //}
}