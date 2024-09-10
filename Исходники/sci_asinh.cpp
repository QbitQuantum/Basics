/*--------------------------------------------------------------------------*/
types::Function::ReturnValue sci_asinh(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::Double* pDblIn = NULL;
    types::Double* pDblOut = NULL;

    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), "asinh", 1);
        return types::Function::Error;
    }

    if (_iRetCount > 1)
    {
        Scierror(78, _("%s: Wrong number of output argument(s): %d expected.\n"), "asinh", 1);
        return types::Function::Error;
    }

    if (in[0]->isDouble())
    {
        pDblIn = in[0]->getAs<types::Double>();
        pDblOut = new types::Double(pDblIn->getDims(), pDblIn->getDimsArray(), pDblIn->isComplex());

        double* pInR = pDblIn->get();
        double* pOutR = pDblOut->get();
        int size = pDblIn->getSize();
        if (pDblIn->isComplex())
        {
            double* pInI = pDblIn->getImg();
            double* pOutI = pDblOut->getImg();

            for (int i = 0; i < size; i++)
            {
                //zcoss(-pInI[i], pInR[i], &pOutR[i], &pOutI[i]);
                std::complex<double> c(pInR[i], pInI[i]);
                std::complex<double> d = std::asinh(c);
                pOutR[i] = d.real();
                pOutI[i] = d.imag();
            }
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                pOutR[i] = asinh(pInR[i]);
            }
        }

        out.push_back(pDblOut);
    }
    else
    {
        ast::ExecVisitor exec;
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_asinh";
        return Overload::call(wstFuncName, in, _iRetCount, out, &exec);
    }

    return types::Function::OK;
}