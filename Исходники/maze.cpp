/** makes the walls of the maze. */
void Maze::make_walls() {
    using std::make_pair;
    using utility::rand;

    size_t complexity = size_t(this->complexity*(5*(width + height)));
    size_t density    = size_t(this->density*width/2*height/2);

    for (size_t i = 0; i < density; ++i) {
        size_t x = rand(0, width/2)*2;
        size_t y = rand(0, height/2)*2;
        setWall(x, y, WallTypes::INNER);

        std::vector<std::pair<size_t, size_t>> neigh;
        neigh.reserve(4);
        for (size_t j = 0; j < complexity; ++j) {
            // add all neighbors that are not out of bounds
            if (x > 1)        { neigh.push_back( make_pair(x-2, y) ); }
            if (x < height-2) { neigh.push_back( make_pair(x+2, y) ); }
            if (y > 1)        { neigh.push_back( make_pair(x, y-2) ); }
            if (y < width-2)  { neigh.push_back( make_pair(x, y+2) ); }
            if (neigh.size()) { // choose a random neighbor if there are any
                auto n = neigh[rand(0, neigh.size())];
                if (isPath(n.first, n.second)) {
                    auto link = make_pair(
                            x + static_cast<long long>(n.first - x)/2,
                            y + static_cast<long long>(n.second - y)/2);
                    setWall(n.first,    n.second,    WallTypes::INNER);
                    setWall(link.first, link.second, WallTypes::INNER);
                    x = n.first;
                    y = n.second;
                }
            }
            neigh.clear();
        }
    }

}