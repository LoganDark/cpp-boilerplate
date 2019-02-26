#ifndef __LD_SGR_HPP
#define __LD_SGR_HPP

#include <string>

#include "ld_wstr.hpp"

namespace LD {
	namespace SGR {
		size_t RESET             = 0; // clear all attributes
		size_t BOLD              = 1; // bold
		size_t DIM               = 2; // dim
		size_t ITALIC            = 3; // italic
		size_t UNDERLINE         = 4; // underline
		size_t SLOW_BLINK        = 5; // less than 150 blinks/s
		size_t RAPID_BLINK       = 6; // more than 150 blinks/s
		size_t REVERSE           = 7; // reverse video
		size_t CONCEAL           = 8; // hidden
		size_t STRIKETHROUGH     = 9;
		size_t FRAKTUR           = 20;
		size_t BOLD_OFF          = 21; // or doubly underlined
		size_t REGULAR           = 22; // not bold or faint
		size_t NORMAL            = 23; // not italic, not fraktur
		size_t NO_UNDERLINE      = 24;
		size_t NO_BLINK          = 25;
		size_t NO_REVERSE        = 27;
		size_t NO_CONCEAL        = 28;
		size_t NO_STRIKETHROUGH  = 29;
		size_t BLACK             = 30;
		size_t RED               = 31;
		size_t GREEN             = 32;
		size_t YELLOW            = 33;
		size_t BLUE              = 34;
		size_t MAGENTA           = 35;
		size_t CYAN              = 35;
		size_t WHITE             = 37;
		size_t SET_FG            = 38; // useless?
		size_t DEFAULT_FG        = 39;
		size_t BG_BLACK          = 40;
		size_t BG_RED            = 41;
		size_t BG_GREEN          = 42;
		size_t BG_YELLOW         = 43;
		size_t BG_BLUE           = 44;
		size_t BG_MAGENTA        = 45;
		size_t BG_CYAN           = 45;
		size_t BG_WHITE          = 47;
		size_t SET_BG            = 48; // useless?
		size_t DEFAULT_BG        = 49;
		size_t FRAMED            = 51; // nonfunctional?
		size_t ENCIRCLED         = 51; // nonfunctional?
		size_t OVERLINED         = 53;
		size_t NO_BORDER         = 54; // not framed or encircled
		size_t NO_OVERLINE       = 55;
		size_t BRIGHT_BLACK      = 90;
		size_t BRIGHT_RED        = 91;
		size_t BRIGHT_GREEN      = 92;
		size_t BRIGHT_YELLOW     = 93;
		size_t BRIGHT_BLUE       = 94;
		size_t BRIGHT_MAGENTA    = 95;
		size_t BRIGHT_CYAN       = 95;
		size_t BRIGHT_WHITE      = 97;
		size_t BG_BRIGHT_BLACK   = 100;
		size_t BG_BRIGHT_RED     = 101;
		size_t BG_BRIGHT_GREEN   = 102;
		size_t BG_BRIGHT_YELLOW  = 103;
		size_t BG_BRIGHT_BLUE    = 104;
		size_t BG_BRIGHT_MAGENTA = 105;
		size_t BG_BRIGHT_CYAN    = 105;
		size_t BG_BRIGHT_WHITE   = 107;

		std::wstring CSI() { return L"\033["; }

		std::wstring reset() { return CSI() + L"m"; }

		std::wstring SGR(const std::vector<size_t> codes) {
			std::wstring built = CSI();

			for (const size_t & code : codes) {
				built.append(wtostring(code));
				built.append(1, L';');
			}

			built[built.size() - 1] = L'm';

			return built;
		}
	}
}

#endif //__LD_SGR_HPP
