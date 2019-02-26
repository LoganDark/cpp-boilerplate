#ifndef __LD_WSTR_HPP
#define __LD_WSTR_HPP

#include <codecvt>
#include <locale>

#include "ld_num.hpp"

namespace LD {
	/**
	 * Used by [[LD::s2wstr]] and [[LD::w2str]].
	 */
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	/**
	 * Converts a narrow string (std::string) to a wide string (std::wstring).
	 *
	 * @param src
	 * @return
	 */
	std::wstring s2wstr(const std::string & src) {
		return converter.from_bytes(src);
	}

	/**
	 * [[std::to_string]] but wide.
	 *
	 * @param src
	 * @return
	 */
	template <typename Num>
		std::wstring wtostring(const Num & src) {
			return s2wstr(std::to_string(src));
		}

	/**
	 * Same as above, but works with Unsigned/Rational/etc.
	 *
	 * @param src
	 * @return
	 */
	template <>
		std::wstring wtostring<math::Unsigned>(const math::Unsigned & src) {
			return s2wstr(src.to_string());
		}

	template <>
		std::wstring wtostring<math::Integer>(const math::Integer & src) {
			return s2wstr(src.to_string());
		}

	template <>
		std::wstring wtostring<math::Rational>(const math::Rational & src) {
			return s2wstr(src.to_string());
		}

	/**
	 * Converts a wide string (std::wstring) to a narrow string (std::string).
	 *
	 * @param src
	 * @return
	 */
	std::string w2str(const std::wstring & src) {
		return converter.to_bytes(src);
	}

	/**
	 * Converts a C-string (string literal) to a wide string.
	 *
	 * @param src
	 * @return
	 */
	std::wstring c2wstr(const char * src) {
		return s2wstr(std::string(src));
	}
}

#endif //__LD_WSTR_HPP
