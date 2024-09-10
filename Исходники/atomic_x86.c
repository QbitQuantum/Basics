	/* _Atomic_fetch_xor_8 */
_Uint8_t _Fetch_xor_8(volatile _Uint8_t *_Tgt, _Uint8_t _Value)
	{	/* xor _Value with *_Tgt atomically with
			sequentially consistent memory order */
 #if _MS_32
	_Compiler_barrier();
	__asm
		{
		mov esi, _Tgt;
		mov eax, [esi];
		mov edx, 4[esi];
	again:
		mov ecx, edx;
		mov ebx, eax;
		xor ebx, dword ptr _Value;
		xor ecx, dword ptr _Value[4];
		lock cmpxchg8b [esi];
		jnz again;
		mov dword ptr _Value, eax;
		mov dword ptr _Value[4], edx;
		}
	_Compiler_barrier();

 #elif _MS_64
	_Value = _InterlockedXor64((volatile _LONGLONG *)_Tgt, _Value);
 #endif /* _MS_32 */

	return (_Value);
	}