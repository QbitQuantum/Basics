unsigned int fast_inclusion(const tetra *t, const point *p) {

    auto &a = *t->p[0],
         &b = *t->p[1],
         &c = *t->p[2],
         &d = *t->p[3];

    Eigen::Matrix<double, 3, 3> A;

    A.col(0) << b.x - a.x, b.y - a.y, b.z - a.z;
    A.col(1) << c.x - a.x, c.y - a.y, c.z - a.z;
    A.col(2) << d.x - a.x, d.y - a.y, d.z - a.z;

    if (verbose == 3)
        std::cout << A << std::endl;

    Eigen::Matrix<double, 3, 1> x, B(p->x - a.x, p->y - a.y, p->z - a.z);

    x = A.inverse() * B;

    double sum = 0;

    for (unsigned int i = 0; i < 3; ++i) {

        if (std::abs(x[i]) < 1e-10)
            x[i] = 0;

        if (x[i] < 0)
            return 0; // outside
        else
            sum += x[i];
    }


    if (std::abs(sum - 1) < 1e-10)
        sum = 1;//return exact_inclusion(t, p);

    if (std::abs(sum) < 1e-10)
        sum = 0;

    if (sum > 1)
        return 0; // outside

    if (sum == 0)
        return 1; // vertex 0

    double u(x[0]), v(x[1]), w(x[2]);

    if (u == 1) {

        return 2; // vertex 1
    }

    else if (u > 0) {

        if (v > 0) {
            
            if (w > 0) {

                if (sum == 1)
                    return 14; // surface 321
                else
                    return 15; // inside
            }

            else {

                if (sum == 1)
                    return 6; // edge 21
                else
                    return 7; // surface 012
            }
        }

        else {
            
            if (w > 0) {

                if (sum == 1)
                    return 10; // edge 31
                else
                    return 11; // surface 031
            }

            else {

                return 3; // edge 10
            }
        } 
    } else {

        if (v == 1)
            return 4; // vertex 2

        else if (v > 0) {

            if (w > 0) {

                if (sum == 1)
                    return 12; // edge 32
                else
                    return 13; // surface 023
            }

            else {

                return 5; // edge 20
            }
        }

        else {

            if (w == 1)
                return 8; // vertex 3
            else
                return 9; // edge 30
        }        
    }

    return 0;
}