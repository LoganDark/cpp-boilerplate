#ifndef __LD_TERMCOLOR_HPP
#define __LD_TERMCOLOR_HPP

#include <string>
#include <sstream>

#include "ld_wstr.hpp"

#ifdef LD_USE_TERMCOLOR
	#include "termcolor/include/termcolor/termcolor.hpp"

	#define GET_ANSI(MAC) ([=]{std::stringstream ss; ss << termcolor::colorize << MAC; return LD::s2wstr(std::string(ss.str()));})()
	#define LOG_STYLE GET_ANSI(termcolor::cyan)
	#define ERR_STYLE GET_ANSI(termcolor::red)
	#define EMPHASIS GET_ANSI(termcolor::bold)
	#define IMPORTANT GET_ANSI(termcolor::underline)
#else
	#define GET_ANSI(MAC) std::wstring()
	#define LOG_STYLE ""
	#define ERR_STYLE ""
	#define EMPHASIS ""
	#define IMPORTANT ""
#endif

#endif //__LD_TERMCOLOR_HPP
