    void GadgetTreeReader::iterate(gadget::Node* parent, libember::glow::GlowElementCollection* collection)
    {
        if (collection != nullptr)
        {
            auto const last = std::end(*collection);
            for(auto it = std::begin(*collection); it != last; ++it)
            {
                auto& child = *it;
                auto const type = ber::Type::fromTag(child.typeTag());
                if (type.isApplicationDefined())
                {
                    if (type.value() == GlowType::Node)
                    {
                        auto& glownode = *dynamic_cast<GlowNode*>(&child);
                        auto node = gadget::NodeFactory::createNode(parent, glownode.identifier());
                        node->setDescription(glownode.description());
                        node->setSchema(glownode.schemaIdentifiers());

                        iterate(node, glownode.children());
                    }
                    else if (type.value() == GlowType::Parameter)
                    {
                        auto& glowparam = dynamic_cast<GlowParameter&>(child);
                        auto identifier = glowparam.identifier();
                        auto paramtype = glowparam.effectiveType();
                        switch(paramtype.value())
                        {
                            case libember::glow::ParameterType::Boolean:
                                transform(gadget::ParameterFactory::create(parent, identifier, false), &glowparam);
                                break;

                            case libember::glow::ParameterType::Enum:
                                transform(gadget::ParameterFactory::create(parent, identifier), &glowparam);
                                break;

                            case libember::glow::ParameterType::Integer:
                                transform(gadget::ParameterFactory::create(parent, identifier, 0, 1000, 0), &glowparam);
                                break;

                            case libember::glow::ParameterType::Octets:
                                break;

                            case libember::glow::ParameterType::Real:
                                transform(gadget::ParameterFactory::create(parent, identifier, 0.0, 1000.0, 0.0), &glowparam);
                                break;

                            case libember::glow::ParameterType::String:
                                transform(gadget::ParameterFactory::create(parent, identifier, std::string("text")), &glowparam);
                                break;

                            case libember::glow::ParameterType::Trigger:
                                break;

                            default:
                                volatile int x = paramtype.value();
                                break;
                        }
                    }
                }
            }
        }
    }