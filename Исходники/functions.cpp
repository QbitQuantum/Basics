void Read_LD(string &input_directory, string& fname , MatrixXd& chol_factor, MatrixXd& chol_factor_inv){
    ifstream ld_file;
    ld_file.open(input_directory+fname);
  //  string ld_header;
    //getline(ld_file, ld_header);
    //vector<string> ld_header_split = split(ld_header, ' ');
    string ld_line;
    vector<string> ld_line_split;
    vector<vector<string>> all_ld_line_split;
    while(getline(ld_file, ld_line)){
        ld_line_split = split(ld_line, ' ');
        all_ld_line_split.push_back(ld_line_split);
    }
    ld_file.close();
    unsigned long num_snps = all_ld_line_split.size();
    MatrixXd numeric_ld(num_snps, num_snps);
    for(unsigned int i = 0; i < num_snps; i++){
        for(unsigned int j = 0; j < num_snps; j++){
            numeric_ld(i,j) = stod(all_ld_line_split[i][j]);
        }
    }
    double reg_factor;
    reg_factor = Regularize_LD(numeric_ld);


    chol_factor = numeric_ld.llt().matrixL(); //cholesky decompostion
    chol_factor.transpose();
    chol_factor.triangularView<Eigen::Upper>();
    chol_factor_inv = chol_factor.inverse(); //cholesky decomp inverse
    chol_factor_inv.triangularView<Eigen::Lower>();

}