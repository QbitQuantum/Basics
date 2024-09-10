bool cpu_CAS64(volatile i64* location, i64 expected, i64 newValue)
{
	const i64 initial = _InterlockedCompareExchange64((P64)location, newValue, expected);
	return initial == expected;
}