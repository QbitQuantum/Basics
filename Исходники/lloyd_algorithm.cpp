int main (int argc, char *argv[]) {
    // Cube
    std::list<Plane> planes;
    planes.push_back(Plane(1, 0, 0, -1));
    planes.push_back(Plane(-1, 0, 0, -1));
    planes.push_back(Plane(0, 1, 0, -1));
    planes.push_back(Plane(0, -1, 0, -1));
    planes.push_back(Plane(0, 0, 1, -1));
    planes.push_back(Plane(0, 0, -1, -1));

    std::vector<Point> points;
    int N, steps;
    // Number of points
    if (argc > 1) {
        N = atoi(argv[1]);
    } else {
        N = 50;
    }

    // Number of steps
    if (argc > 2) {
        steps = atoi(argv[2]);
    } else {
        steps = 10;
    }

    CGAL::Random_points_in_sphere_3<Point> g;
    for (int i = 0; i < N; i++) {
        Point p = *g++;
        points.push_back(p);
    }

    std::ofstream bos("before_lloyd.xyz");
    std::copy(points.begin(), points.end(),
              std::ostream_iterator<Point>(bos, "\n"));

    // Apply Lloyd algorithm: will generate points
    // uniformly sampled inside a cube.
    for (int i = 0; i < steps; i++) {
        std::cout << "iteration " << i + 1 << std::endl;

        CGAL::Timer timer;
        timer.start();
        lloyd_algorithm(planes.begin(),
                        planes.end(),
                        points);
        timer.stop();

        std::cout << "Execution time : " << timer.time() << "s\n";
    }

    std::ofstream aos("after_lloyd.xyz");
    std::copy(points.begin(), points.end(),
              std::ostream_iterator<Point>(aos, "\n"));

    return 0;
}