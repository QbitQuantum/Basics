static double gauss_kernel(double diff2, double var)
{
    return exp(-diff2 / (2 * var));
}