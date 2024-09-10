inline auto waveshaper_tanh(E1&& input, double saturation)
{
    return tanh(saturation * input) * (coth(saturation));
}