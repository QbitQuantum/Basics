String StructureShape::stringRepresentation()
{
    StringBuilder representation;
    representation.append("{");
    for (auto iter = m_fields.begin(), end = m_fields.end(); iter != end; ++iter) {
        String prop(iter->key.get());
        representation.append(prop);
        representation.append(", ");
    }

    if (representation.length() >= 3)
        representation.resize(representation.length() - 2);

    representation.append("}");

    return representation.toString();
}