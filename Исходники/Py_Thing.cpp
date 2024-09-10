static int Entity_setattro(PyEntity *self, PyObject *oname, PyObject *v)
{
#ifndef NDEBUG
    if (self->m_entity.e == NULL) {
        PyErr_SetString(PyExc_AssertionError, "NULL entity in Entity.setattr");
        return -1;
    }
#endif // NDEBUG
    char * name = PyString_AsString(oname);
    if (strcmp(name, "map") == 0) {
        PyErr_SetString(PyExc_AttributeError, "map attribute forbidden");
        return -1;
    }
    Entity * entity = self->m_entity.e;
    //std::string attr(name);
    //if (v == NULL) {
        //entity->attributes.erase(attr);
        //return 0;
    //}
    if (strcmp(name, "type") == 0) {
        if (entity->getType() != 0) {
            PyErr_SetString(PyExc_RuntimeError, "Cannot mutate entity type");
            return -1;
        }
        if (!PyString_CheckExact(v)) {
            PyErr_SetString(PyExc_TypeError, "No string type");
            return -1;
        }
        const TypeNode * type = Inheritance::instance().getType(PyString_AsString(v));
        if (type == 0) {
            PyErr_SetString(PyExc_RuntimeError, "Entity type unknown");
            return -1;
        }
        entity->setType(type);
        return 0;
    }
    Element obj;
    if (PyObject_asMessageElement(v, obj) == 0) {
        PropertyBase * p = entity->setAttr(name, obj);
        if (p != 0) {
            p->setFlags(flag_unsent);
        }
        return 0;
    }
    // FIXME In fact it seems that nothing currently hits this bit, so
    // all this code is redundant for entity scripts.
    // If we get here, then the attribute is not Atlas compatable, so we
    // need to store it in a python dictionary
    if (self->Entity_attr == NULL) {
        self->Entity_attr = PyDict_New();
        if (self->Entity_attr == NULL) {
            return -1;
        }
    }
    return PyDict_SetItemString(self->Entity_attr, name, v);
}