#ifndef __LD_OUTPUT_HPP
#define __LD_OUTPUT_HPP

#include <iostream>
#include <string>

#include "ld_termcolor.hpp"

namespace LD {
	/**
	 * Outputs `text`.
	 *
	 * @param text The text to output.
	 */
	void o(const std::wstring & text) {
		//std::wcout << text;
		std::wprintf(text.c_str());
	}

	/**
	 * Flushes stdout after [[LD::o]].
	 */
	void fl() {
		std::wcout << std::flush;
	}

	/**
	 * Outputs `text`, then flushes the output.
	 *
	 * @param text The text to output.
	 */
	void ofl(const std::wstring & text) {
		o(text);
		fl();
	}

	/**
	 * Newline.
	 */
	void nl() {
		std::wcout << std::endl;
	}

	/**
	 * Logs a message to [[std::wcout]] using [[LOG_STYLE]]. This does flush
	 * afterwards.
	 *
	 * @param message The message to log.
	 */
	void log(const std::wstring & message) {
		// @formatter:off
		#ifdef LD_USE_TERMCOLOR
			o(LOG_STYLE + message + GET_ANSI(termcolor::reset));
		#else
			o(message);
		#endif

		fl();
		// @formatter:on
	}

	/**
	 * [[LD::log]] with a newline.
	 *
	 * @param message
	 */
	void lognl(const std::wstring & message) {
		log(message);
		nl();
	}

	/**
	 * Logs a message to [[std::wcout]] using [[ERR_STYLE]]. This does flush
	 * afterwards.
	 *
	 * @param message The message to log.
	 */
	void err(const std::wstring & message) {
		// @formatter:off
		#ifdef LD_USE_TERMCOLOR
			o(ERR_STYLE + message + GET_ANSI(termcolor::reset));
		#else
			o(message);
		#endif

		fl();
		// @formatter:on
	}

	/**
	 * [[LD::err]] with a newline.
	 *
	 * @param message
	 */
	void errnl(const std::wstring & message) {
		err(message);
		nl();
	}
}

#endif //__LD_OUTPUT_HPP
