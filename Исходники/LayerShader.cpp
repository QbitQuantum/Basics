Config
ShaderOptions::getConfig() const
{
    Config conf = ConfigOptions::getConfig();

    if (!_code.empty())
    {
        conf.setValue(_code);
    }

    conf.remove("sampler");
    for (unsigned i = 0; i < _samplers.size(); ++i) {
        Config c("sampler");
        c.add("name", _samplers[i]._name);
        if (_samplers[i]._uris.size() > 1) {
            Config urlarray("array");
            c.add(urlarray);
            for (std::vector<URI>::const_iterator j = _samplers[i]._uris.begin(); j != _samplers[i]._uris.end(); ++j) {
                urlarray.add(j->getConfig());
            }
        }
        else if (_samplers[i]._uris.size() == 1) {
            c.add("url", _samplers[i]._uris.back().getConfig());
        }
        conf.add(c);
    }

    conf.remove("uniform");
    for (unsigned i = 0; i < _uniforms.size(); ++i) {
        Config c("uniform");
        c.set("name", _uniforms[i]._name);
        c.set("value", _uniforms[i]._value);
        conf.add(c);
    }

    return conf;
}