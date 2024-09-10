void Value::setInteger(integer value)
{
	char buffer[128];

	_i64toa_s(value, buffer, sizeof(buffer), 10);

	_isNull = false;
	_value = buffer;
}