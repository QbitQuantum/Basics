void Properties::resolveInheritance(const char* id)
{
    // Namespaces can be defined like so:
    // "name id : parentID { }"
    // This method merges data from the parent namespace into the child.

    // Get a top-level namespace.
    Properties* derived;
    if (id)
    {
        derived = getNamespace(id);
    }
    else
    {
        derived = getNextNamespace();
    }
    while (derived)
    {
        // If the namespace has a parent ID, find the parent.
        if (!derived->_parentID.empty())
        {
            Properties* parent = getNamespace(derived->_parentID.c_str());
            if (parent)
            {
                resolveInheritance(parent->getId());

                // Copy the child.
                Properties* overrides = new (std::nothrow) Properties(*derived);

                // Delete the child's data.
                for (size_t i = 0, count = derived->_namespaces.size(); i < count; i++)
                {
                    CC_SAFE_DELETE(derived->_namespaces[i]);
                }

                // Copy data from the parent into the child.
                derived->_properties = parent->_properties;
                derived->_namespaces = std::vector<Properties*>();
                std::vector<Properties*>::const_iterator itt;
                for (const auto space: parent->_namespaces)
                {
                    derived->_namespaces.push_back(new (std::nothrow) Properties(*space));
                }
                derived->rewind();

                // Take the original copy of the child and override the data copied from the parent.
                derived->mergeWith(overrides);

                // Delete the child copy.
                CC_SAFE_DELETE(overrides);
            }
        }

        // Resolve inheritance within this namespace.
        derived->resolveInheritance();

        // Get the next top-level namespace and check again.
        if (!id)
        {
            derived = getNextNamespace();
        }
        else
        {
            derived = NULL;
        }
    }
}