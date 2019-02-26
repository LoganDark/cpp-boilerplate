#ifndef __LD_NUM_HPP
#define __LD_NUM_HPP

#include <string>
#include <sstream>

#include "precision/math_Rational.h"

namespace LD {
	/**
	 * This is not mine, this is Elias Yarrkov's: https://stackoverflow.com/a/101613
	 *
	 * Honestly, I can't comment this because I don't entirely understand how it
	 * works.
	 *
	 * @param base The number to exponentiate.
	 * @param exp The exponent.
	 * @return
	 */
	template <class Num>
		Num ipow(Num base, Num exp) {
			Num result = 1;

			for (;;) {
				if (exp % 2 == 1) {
					result *= base;
				}

				exp >>= 1;

				if (exp == 0) {
					break;
				}

				base *= base;
			}

			return result;
		}

	/**
	 * Raises a [[math::Rational]] to an integer power
	 *
	 * @param src
	 * @param exp
	 * @return
	 */
	math::Rational rpow(const math::Rational & src,
	                    const math::Integer & exp) {
		return math::Rational(ipow(src.numerator(), exp),
		                      ipow(src.denominator(), exp));
	}

	/**
	 * `lhs % rhs` for [[math::Rational]]s.
	 *
	 * @param lhs
	 * @param rhs
	 * @return
	 */
	math::Rational rmod(const math::Rational & lhs,
	                    const math::Rational & rhs) {
		math::Integer cd = lhs.denominator() * rhs.denominator();
		math::Integer ln = lhs.numerator() * cd;
		math::Integer rn = rhs.numerator() * cd;

		return math::Rational(ln % rn, cd);
	}

	/**
	 * Returns the absolute value of anything that can be compared to 0.
	 *
	 * @tparam Num
	 * @param num
	 * @return
	 */
	template <class Num>
		Num abs(Num num) {
			return num < 0 ? -num : num;
		}

	template <class Num>
		Num from_string(const std::wstring & str) {
			Num target;

			std::wstringstream sstr(str);
			sstr >> target;

			return target;
		}
}

#endif //__LD_NUM_HPP
