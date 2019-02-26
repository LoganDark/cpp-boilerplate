#ifndef __LD_PRNG_HPP
#define __LD_PRNG_HPP

#include <random>

#include "ld_wstr.hpp"

namespace LD {
	/**
	 * Generates an RNG using a seed from an [[std::random_device]].
	 *
	 * See https://stackoverflow.com/a/13445752 & [[wander]]
	 *
	 * @return The RNG
	 */
	std::mt19937 get_secure_RNG() {
		std::mt19937 rng;
		rng.seed(std::random_device()());

		return rng;
	}

	/**
	 * Generates an RNG using a seed from an [[std::random_device]].
	 *
	 * See https://stackoverflow.com/a/13445752 & [[wander]]
	 *
	 * @return The RNG
	 */
	int get_rn(std::mt19937 & rng, int min, int max) {
		if (min > max) {
			std::swap(max, min);
		}

		auto diff = static_cast<unsigned int>(max - min);

		return min + static_cast<int>(
			std::uniform_int_distribution<std::mt19937::result_type>(0, diff)(
				rng
			)
		);
	}
}

#endif //__LD_PRNG_HPP
