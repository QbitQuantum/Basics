int main() {
    double y_vals[] = {-1.5, 2, -2.5};
    double z_vals[] = {3, -2, 1};
    Vec<double> zeroes(3);                             // Vec size 3 (entries initialize to zero)
    Vec<double> x = Vec<double>::constantVec(3, 2.5);  // Vec size 3 with all entries set to 2.5
    Vec<double> y = Vec<double>(y_vals, 3);
    Vec<double> z(3);
    z.setEntries(z_vals, 3);
    Vec<int> ix(x);

    cout << "zeroes = " << zeroes << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;
    cout << "ix = " << ix << endl;
    cout << "z[0] = " << z[0] << ", z[1] = " << z[1] << ", z[2] = " << z[2] << endl;
    cout << "3.5 * x = " << (3.5 * x) << endl;
    cout << "x / 3.5 = " << (x / 3.5) << endl;
    cout << "x + y = " << (x + y) << endl;
    cout << "x - y = " << (x - y) << endl;
    cout << "x.concatenate(y) = " << x.concatenate(y) << endl;
    cout << "x.dot(y) = " << x.dot(y) << endl;
    cout << "x.cross(y) = " << x.cross(y) << endl;
    cout << "x.norm() = " << x.norm() << endl;
    cout << "x.unit_vector() = " << x.unit_vector() << endl;
    cout << "ix.norm() = " << ix.norm() << endl;
    cout << "ix.norm<double>() = " << ix.norm<double>() << endl;
    cout << "ix.unit_vector<double>() = " << ix.unit_vector<double>() << endl;
    cout << "scalar_triple_product(x, y, z) = " 
         << Vec<double>::scalar_triple_product(x, y, z) << endl;
    cout << "vector_triple_product(x, y, z) = " 
         << Vec<double>::vector_triple_product(x, y, z) << endl;
}