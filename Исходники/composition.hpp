/// TODO write the damn thing
notation::rhythm
waltzbeat_mid(units::beat biti)
{
    using namespace sgr::notation;
    using utility::rand;

    rhythm mid;
    for (int i = 0; i < biti.value; ++i) {
        double poudarek;
        if (i%3 == 0) {
            poudarek = 1;
        } else {
            poudarek = 0.7;
        }
        mid.push_back(hit(units::beat{double(i)}, units::beat{1}, poudarek));
    }

    for (int i = 0; i < 6; ++i) {
        int a = rand(0, 101);
        if (a < 35) {
            for (int j = 0; j < (biti/3).value; ++j) {
                mid.push_back(
                    hit(
                        units::beat{double(i)/2 + j*3},
                        units::beat{0.5},
                        0.5));
            }
        }
    }
    return mid;
}