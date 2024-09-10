template < class Traits > double test_sort(unsigned int degree, unsigned int n)
{
    typedef CGAL::Kinetic::Sort < Traits > Sort;
    Traits tr(0, 10000);
    Sort sort(tr);
    CGAL::Random r;
    for (unsigned int i = 0; i < n; ++i) {
        std::vector < double >cf;
        for (unsigned int j = 0; j < degree + 1; ++j) {
            cf.push_back(r.get_double());
        }
        typename Traits::Kinetic_kernel::Motion_function fn(cf.begin(),
            cf.end());
        typename Traits::Kinetic_kernel::Point_1 pt(fn);
        tr.active_points_1_table_handle()->insert(pt);
    }
    CGAL::Timer timer;
    timer.start();
    int ne = 0;
    while (tr.simulator_handle()->next_event_time() !=
    tr.simulator_handle()->end_time()) {
        tr.simulator_handle()->set_current_event_number(tr.
            simulator_handle()->
            current_event_number()
            + 1);
        ++ne;
        if (ne == 1000)
            break;
    }
    timer.stop();
    return timer.time() / static_cast < double >(ne);
}