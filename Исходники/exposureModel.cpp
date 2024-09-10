void exposureModel::setOffset(NumericVector offsets)
{
    if (offsets.length() != (nTpt))
    {
        Rcpp::Rcout << "Error: offsets must have length equal to the number of time points.\n";
        Rcpp::stop("Invalid offsets.");
    }
    int i;
    for (i = 0; i < offsets.length(); i++)
    {
        offset(i) = offsets(i);
    }
}