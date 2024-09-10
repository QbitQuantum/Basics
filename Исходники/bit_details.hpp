constexpr T _tzcnt(T src, X...);

// Bit field extraction
template <class T, class = decltype(__builtin_ia32_bextr_u64(T(), T(), T()))>
constexpr T _bextr(T src, T start, T len);
template <class T, class... X>
constexpr T _bextr(T src, T start, T len, X...);

// Parallel bits deposit
template <class T, class = decltype(_pdep_u64(T()))>
constexpr T _pdep(T src, T mask);
template <class T, class... X>
constexpr T _pdep(T src, T mask, X...);

// Parallel bits extract
template <class T, class = decltype(_pext_u64(T()))>
constexpr T _pext(T src, T mask);
template <class T, class... X>
constexpr T _pext(T src, T mask, X...);

// Byte swap
template <class T, class = decltype(__builtin_bswap64(T()))>
constexpr T _byteswap(T src);
template <class T, class... X>
constexpr T _byteswap(T src, X...);

// Bit swap
template <class T>
constexpr T _bitswap(T src);
/* ************************************************************************** */
