int main(){

	//Given the equation (2n)!/(n!)^2

	int n = 20;
	std::cout << "Calcuating number of routes..." << std::endl;
	long long answer = exp(lgamma((n + n) + 1)) / (exp(lgamma(n + 1))*exp(lgamma(n + 1)));
	std::cout << "The answer is: " << answer+1 << std::endl;

	system("Pause");
	return 0;
}