size_t Variant::deserialize(const unsigned char *buffer, size_t size)
{
    if (buffer != NULL && size > 0)
    {
        Variant::Type type = static_cast<Variant::Type>(*buffer);
        ++buffer;

        switch (type)
        {
            case UINT8:
            {
                typedef uint8_t Type;

                if ((size - 1) < sizeof(Type))
                    return 0;
                else
                {
                    setUint8(static_cast<Type>(*buffer));
                    size = sizeof(Type) + 1;
                }

                break;
            }

            case INT8:
            {
                typedef uint8_t Type;

                if ((size - 1) < sizeof(Type))
                    return 0;
                else
                {
                    setInt8(static_cast<Type>(*buffer));
                    size = sizeof(Type) + 1;
                }

                break;
            }

            case UINT16:
            {
                typedef uint16_t Type;

                if ((size - 1) < sizeof(Type))
                    return 0;
                else
                {
                    setUint16(ntohs(*reinterpret_cast<const Type *>(buffer)));
                    size = sizeof(Type) + 1;
                }

                break;
            }

            case INT16:
            {
                typedef int16_t Type;

                if ((size - 1) < sizeof(Type))
                    return 0;
                else
                {
                    setInt16(ntohs(*reinterpret_cast<const Type *>(buffer)));
                    size = sizeof(Type) + 1;
                }

                break;
            }

            case UINT32:
            {
                typedef uint32_t Type;

                if ((size - 1) < sizeof(Type))
                    return 0;
                else
                {
                    setUint32(ntohl(*reinterpret_cast<const Type *>(buffer)));
                    size = sizeof(Type) + 1;
                }

                break;
            }

            case INT32:
            {
                typedef int32_t Type;

                if ((size - 1) < sizeof(Type))
                    return 0;
                else
                {
                    setInt32(ntohl(*reinterpret_cast<const Type *>(buffer)));
                    size = sizeof(Type) + 1;
                }

                break;
            }

            case UINT64:
            {
                typedef uint64_t Type;

                if ((size - 1) < sizeof(Type))
                    return 0;
                else
                {
                    setUint64(ntohll(*reinterpret_cast<const Type *>(buffer)));
                    size = sizeof(Type) + 1;
                }

                break;
            }

            case INT64:
            {
                typedef int64_t Type;

                if ((size - 1) < sizeof(Type))
                    return 0;
                else
                {
                    setInt64(ntohll(*reinterpret_cast<const Type *>(buffer)));
                    size = sizeof(Type) + 1;
                }

                break;
            }

            case FLOAT:
            {
                typedef uint32_t Type;

                if ((size - 1) < sizeof(Type))
                    return 0;
                else
                {
                    setFloat(ntohf(*reinterpret_cast<const Type *>(buffer)));
                    size = sizeof(Type) + 1;
                }

                break;
            }

            case DOUBLE:
            {
                typedef uint64_t Type;

                if ((size - 1) < sizeof(Type))
                    return 0;
                else
                {
                    setDouble(ntohd(*reinterpret_cast<const Type *>(buffer)));
                    size = sizeof(Type) + 1;
                }
                break;
            }

            case BOOL:
            {
                typedef bool Type;

                if ((size - 1) < sizeof(Type))
                    return 0;
                else
                {
                    setBool(*reinterpret_cast<const Type *>(buffer));
                    size = sizeof(Type) + 1;
                }

                break;
            }

            case CHAR:
            {
                typedef char Type;

                if ((size - 1) < sizeof(Type))
                    return 0;
                else
                {
                    setChar(*reinterpret_cast<const Type *>(buffer));
                    size = sizeof(Type) + 1;
                }

                break;
            }

            case STRING:
            {
                typedef uint32_t Type;

                if ((size - 1) < sizeof(Type))
                    return 0;
                else
                {
                    Type len = ntohl(*reinterpret_cast<const Type *>(buffer));

                    if (len > 0 && len <= ((size - 1) - sizeof(Type)))
                        setString(reinterpret_cast<const char *>(buffer + sizeof(Type)), len);

                    size = sizeof(Type) + 1 + len;
                }

                break;
            }

            case BINARY:
            {
                typedef uint32_t Type;

                if ((size - 1) < sizeof(Type))
                    return 0;
                else
                {
                    Type len = ntohl(*reinterpret_cast<const Type *>(buffer));

                    if (len > 0 && len <= ((size - 1) - sizeof(Type)))
                        setBinary(reinterpret_cast<const unsigned char *>(buffer + sizeof(Type)), len);

                    size = sizeof(Type) + 1 + len;
                }

                break;
            }
        }

        return size;
    }

    return 0;
}