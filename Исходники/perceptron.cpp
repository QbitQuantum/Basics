void Perceptron::fit(const Matrix<float>& M, const Matrix<bool>& label)
{
    coeff = zeros<float>(M.colNb(), 1);
    std::size_t cpt = 0;
    bool coeff_changed = true;
    while(coeff_changed && cpt<max_iteration)
    {
        coeff_changed = false;
        for(std::size_t i=0;i<M.rowNb();++i)
        {
            Matrix<float> X = M.getRow(i);
            bool res = predict(X)(0, 0);
            if(res!=label(i, 0))
            {
                X.transpose();
                coeff_changed = true;
                if(label(i, 0))
                {
                    coeff+=alpha*X;
                    thresh-=alpha;
                }
                else
                {
                    coeff-=alpha*X;
                    thresh+=alpha;
                }
            }
        }
        ++cpt;
    }
}