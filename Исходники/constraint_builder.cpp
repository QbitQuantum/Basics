void ConvexPolygon::calculateMatrixForm() {

    //every two adjacent endpoints define a line -> inequality constraint
    //first, resize A and b. x and b are column vectors
    this->A = Eigen::MatrixXd (this->endpoints.size(),2);
    this->b = Eigen::VectorXd (this->endpoints.size());
    Eigen::Vector2d normal;

    for(size_t i=1; i<endpoints.size(); i++) {
	//to define the correct line direction, we also need a point on the inside of the constraint - the seed
	normal(0) = endpoints[i-1](1) - endpoints[i](1);
	normal(1) = endpoints[i](0) - endpoints[i-1](0);
	if(normal.dot(seed) > 0) { //we want the outward pointing normal, so n.dot(s) < 0
	    normal = -normal;
	}
	normal.normalize();
	b(i-1) = -endpoints[i].dot(normal); //endpoints[i];
	A(i-1,0) = normal(0);
	A(i-1,1) = normal(1);
    }
    normal(0) = endpoints.back()(1) - endpoints.front()(1);
    normal(1) = endpoints.front()(0) - endpoints.back()(0);
    if(normal.dot(seed) > 0) { //we want the outward pointing normal, so n.dot(s) < 0
	normal = -normal;
    }
    normal.normalize();
    b(endpoints.size()-1) = -endpoints.front().dot(normal); //endpoints[i];
    A(endpoints.size()-1,0) = normal(0);
    A(endpoints.size()-1,1) = normal(1);
}