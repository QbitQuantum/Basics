/**
 * Returns the variance of the given portfolio structure.
 *
 * @param portfolio  the portfolio structure
 *
 * @return the portfolio variance
 */
double EfficientPortfolioWithRisklessAsset::portfolioVariance(const Eigen::VectorXd& portfolio)
{
	Eigen::VectorXd riskyAssets = portfolio.head(dim - 1);

	return riskyAssets.dot(variance * riskyAssets);
}