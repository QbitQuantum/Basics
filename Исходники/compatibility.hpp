	template <typename T> GLM_FUNC_QUALIFIER detail::tvec3<T> saturate(const detail::tvec3<T>& x){return clamp(x, T(0), T(1));}					//!< \brief Returns clamp(x, 0, 1) for each component in x. (From GLM_GTX_compatibility)