 void printProblem()
 {
     printName();
     std::cout << std::endl << "A_nodes_: " << std::endl << MatrixXi::Identity(A_nodes_.rows(), A_nodes_.rows()) * A_nodes_  << std::endl << std::endl;
     std::cout << "A_: " << std::endl << MatrixXd::Identity(A_.rows(), A_.rows()) * A_  << std::endl << std::endl;
     std::cout << "b_: " << std::endl << b_.transpose() << std::endl << std::endl;
 }