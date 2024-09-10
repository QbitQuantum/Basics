std::ostream& opec::operator<< (std::ostream& os, const opec::Solution& solution) {
    Vector countryProduction = solution.quantities.rowwise().sum();
    
    os << std::setw(20) << "Prices: " << solution.prices.transpose() << std::endl
       << std::setw(20) << "Inflated: " << Market::inflate(solution.prices).transpose() << std::endl            
       << std::setw(20) << "Values: " << solution.values.transpose() << std::endl
       << std::setw(20) << "Prod (round): " << solution.production.transpose() << std::endl
       << std::setw(20) << "Prod (country): " << countryProduction.transpose() << std::endl
       << "Quantities: " << std::endl << solution.quantities << std::endl;
    return os;
}