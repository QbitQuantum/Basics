// 这个文件是 MCF 的一部分。
// 有关具体授权说明，请参阅 MCFLicense.txt。
// Copyleft 2013 - 2018, LH_Mouse. All wrongs reserved.

#include "variable_map.h"
#include "last_error.h"
#include "endian.h"
#include "sha256.h"

static bool ValidateKey(size_t *restrict puInvalidIndex, const wchar_t *pwszKey){
	// Get the array index of the first character that is not acceptable.
	size_t uIndex = wcsspn(pwszKey, L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_");
	// The key is invalid if `uIndex` does not designate the null terminator.
	if(pwszKey[uIndex] != 0){
		return false;
	}
	// If it does, `uIndex` will equal the length of the key. The key is invalid if has a length of zero.
	if(uIndex == 0){
		return false;
	}
	*puInvalidIndex = uIndex;
	return true;
}

bool MCFBUILD_VariableMapIsKeyValid(const wchar_t *pwszKey){
	size_t uInvalidIndex;
	return ValidateKey(&uInvalidIndex, pwszKey);
}
bool MCFBUILD_VariableMapValidateKey(size_t *restrict puInvalidIndex, const wchar_t *pwszKey){
	if(!ValidateKey(puInvalidIndex, pwszKey)){
		MCFBUILD_SetLastError(ERROR_INVALID_NAME);