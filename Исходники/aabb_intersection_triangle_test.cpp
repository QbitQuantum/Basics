void test_speed_for_query(const Tree& tree,
                          const Query_type query_type,
                          const char *query_name,
                          const double duration)
{
    typedef typename K::Ray_3 Ray;
    typedef typename K::Line_3 Line;
    typedef typename K::Point_3 Point;
    typedef typename K::Vector_3 Vector;
    typedef typename K::Segment_3 Segment;

    CGAL::Timer timer;
    unsigned int nb = 0;
    timer.start();
    while(timer.time() < duration)
    {
        switch(query_type)
        {
            case RAY_QUERY:
                {
                    Point source = random_point_in<K>(tree.bbox());
                    Vector vec = random_vector<K>();
                    Ray ray(source, vec);
                    tree.do_intersect(ray);
                    break;
                }
            case SEGMENT_QUERY:
                {
                    Point a = random_point_in<K>(tree.bbox());
                    Point b = random_point_in<K>(tree.bbox());
                    tree.do_intersect(Segment(a,b));
                    break;
                }
                break;
            case LINE_QUERY:
                {
                    Point a = random_point_in<K>(tree.bbox());
                    Point b = random_point_in<K>(tree.bbox());
                    tree.do_intersect(Line(a,b));
                    break;
                }
        }
        nb++;
    }
    unsigned int speed = (unsigned int)(nb / timer.time());
    std::cout.precision(10);
    std::cout.width(15);
    std::cout << speed << " intersections/s with " << query_name << std::endl;
    timer.stop();
}