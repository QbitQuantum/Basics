            auto operator()(const C & c) const {
                using std::distance;

                return distance(c.begin(), c.end());
            }