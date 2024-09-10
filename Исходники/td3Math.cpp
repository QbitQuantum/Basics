string td3Math::mod(vector<vector<string> > operands)
{
    bool op1 = td3Utility::isFloat(operands.at(0).at(0));
    bool op2 = td3Utility::isFloat(operands.at(1).at(0));
    return td3Utility::toString(
               fmod( td3Utility::stof(operands.at(0).at(0)),
                     td3Utility::stof(operands.at(1).at(0))), op1 || op2);
}