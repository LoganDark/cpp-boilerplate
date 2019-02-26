#ifndef __LD_CONTAINER_HPP
#define __LD_CONTAINER_HPP

#include <string>

#include "ld_wstr.hpp"

namespace LD {
	/**
	 * Converts a container to a string like [1, 2, 3].
	 *
	 * @tparam Container
	 * @param cont
	 * @return
	 */
	template <class Container>
		std::wstring wstr_container(const Container & cont) {
			if (cont.size() == 0) {
				return L"[]";
			}

			std::wstring built = L"[";

			for (int i = 0; i < cont.size(); i++) {
				built.append(wtostring(cont[i]) + L", ");
			}

			auto end = built.end();
			* (-- --end) = L']';

			return built.substr(0, built.length() - 1);
		}
}

#endif //__LD_CONTAINER_HPP
