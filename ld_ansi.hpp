#ifndef __LD_ANSI_HPP
#define __LD_ANSI_HPP

#include <string>

#include "ld_wstr.hpp"

#define LD_S static std::wstring
#define LD_R(x) { return std::wstring(L"\033") + x; }
#define WTS wtostring
#define NUM size_t

namespace LD {
	/**
	 * http://matthieu.benoit.free.fr/68hc11/vt100.htm
	 */
	struct ANSI {
		// @formatter:off
		LD_S c_up(NUM n = 1)      LD_R(L"[" + WTS(n) + L"A")
		LD_S c_down(NUM n = 1)    LD_R(L"[" + WTS(n) + L"B")
		LD_S c_forward(NUM n = 1) LD_R(L"[" + WTS(n) + L"C")
		LD_S c_back(NUM n = 1)    LD_R(L"[" + WTS(n) + L"D")
		LD_S c_mov(NUM x, NUM y)  LD_R(L"[" + WTS(y + 1) + L";" + WTS(x + 1) + L"H")
		LD_S c_off()              LD_R(L"[?25l")
		LD_S c_on()               LD_R(L"[?25h")
		LD_S c_save()             LD_R(L"7")
		LD_S c_restore()          LD_R(L"8")
		LD_S c_lf()               LD_R(L"D")
		LD_S c_crlf()             LD_R(L"E")
		LD_S c_rlf()              LD_R(L"M")
		LD_S c_home()             LD_R(L"[H")
		// @formatter:on

		enum EraseLineEnum : NUM {
			ELINEFROMC = 0,
			ELINETOC   = 1,
			ELINE      = 2
		};

		enum EraseScreenEnum : NUM {
			ESCREENFROMC = 0,
			ESCREENTOC   = 1,
			ESCREEN      = 2
		};

		// @formatter:off
		LD_S erase_screen(EraseScreenEnum set) LD_R(L"[" + WTS(set) + L"J")
		LD_S erase_line(EraseLineEnum set)     LD_R(L"[" + WTS(set) + L"K")
		// @formatter:on

		LD_S bel() { return L"\x07"; }
	};
}

#undef LD_S
#undef LD_R
#undef WTS

#endif //__LD_ANSI_HPP
