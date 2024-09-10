// static
void ff::QuaternionKey::InitTangents(QuaternionKey *pKeys, size_t nKeys, float tension)
{
	for (size_t i = 0; i < nKeys; i++)
	{
		QuaternionKey &keyCur       = pKeys[i];
		QuaternionKey &keyBefore    = pKeys[i ? i - 1 : nKeys - 1];
		QuaternionKey &keyNext      = pKeys[(i + 1) % nKeys];
		QuaternionKey &keyAfterNext = pKeys[(i + 2) % nKeys];

		XMVECTOR keyCurTangent;
		XMVECTOR keyNextTangent;
		XMVECTOR keyNextValue;

		XMQuaternionSquadSetup(
			&keyCurTangent,                       // A
			&keyNextTangent,                      // B
			&keyNextValue,                        // C
			XMLoadFloat4(&keyBefore._value),     // Q0
			XMLoadFloat4(&keyCur._value),        // Q1
			XMLoadFloat4(&keyNext._value),       // Q2
			XMLoadFloat4(&keyAfterNext._value)); // Q3

		XMStoreFloat4(&keyCur._tangent,  keyCurTangent);
		XMStoreFloat4(&keyNext._tangent, keyNextTangent);
		XMStoreFloat4(&keyNext._value,   keyNextValue);
	}
}