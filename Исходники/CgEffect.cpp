void CgEffect::SetVector(const char* name, Vector4& v)
{
    cgSetParameter4f(this->retrieveParameter(name), v.GetX(), v.GetY(), v.GetZ(), v.GetW());
}