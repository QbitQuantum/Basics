// Constructor
HyperSpace::HyperSpace( const vector<double>& up_bound , const vector<double>& lw_bound, double sigma , double xi, const unsigned num_dimensions) : dimension(num_dimensions), sigma(sigma), xi(xi) {


    /* Allocate storage for spatial bounds */
    this->lower_bounds = new double[num_dimensions];
    this->upper_bounds = new double[num_dimensions];


    double edge_length = this->hypercubeEdgeLenght();
    for(unsigned i=0 ; i < num_dimensions ; i++){

        this->lower_bounds[i] = lw_bound[i];
        this->upper_bounds[i] = edge_length * ceill(up_bound[i] / edge_length ); // Ensure that all regions will have the same size
    }

}