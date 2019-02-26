#ifndef __LD_INPUT_HPP
#define __LD_INPUT_HPP

#include <iostream>
#include <string>
#include <sstream>

#include "ld_termcolor.hpp"
#include "ld_linenoise.hpp"
#include "ld_output.hpp"
#include "ld_sutil.hpp"

#define USER_WANTS_QUIT std::runtime_error("User requested to quit")

namespace LD {
	/**
	 * Gets input. Uses [[linenoise::Readline]] if needed, else uses
	 * [[std::getline]].
	 *
	 * Returns true if the program should quit.
	 *
	 * @param prompt
	 * @param output
	 * @return
	 */
	bool get_input(const std::wstring & prompt, std::wstring & output) {
		// @formatter:off
	#ifdef LD_USE_LINENOISE
		std::string dummy_output = w2str(output);

		bool success =
			linenoise::Readline(LD::w2str(prompt).c_str(), dummy_output);

		output = s2wstr(dummy_output);

		return success;
	#else
		o(prompt);
		std::getline(std::wcin, output);

		return !std::wcin;
	#endif
		// @formatter:on
	}

	// @formatter:off
	bool get_input(const std::wstring & prompt, std::wstring & output,
				   bool log_color) {
	#ifdef LD_USE_TERMCOLOR
		if (log_color) {
			return get_input(LOG_STYLE + prompt + GET_ANSI(termcolor::reset),
							 output);
		} else {
	#endif
			return get_input(prompt, output);
	#ifdef LD_USE_TERMCOLOR
		}
	#endif
	}
	// @formatter:on

	/**
	 * [[LD::get_input]] but returns a value. Throws [[std::runtime_error]] if
	 * the user wishes to quit
	 *
	 * @param prompt
	 * @return
	 */
	std::wstring get_input(std::wstring & prompt, bool log_color = false) {
		std::wstring output;

		if (get_input(prompt, output, log_color)) {
			throw USER_WANTS_QUIT;
		}

		return output;
	}

	/**
	 * This function uses [[LD::get_input]] in a loop to get an object from the
	 * user that can be constructed from a string. The template type is named
	 * Num, but you can use whatever you want.
	 *
	 * Returns true if the user requested to quit.
	 *
	 * @tparam Num The type to construct. Must have a constructor that takes one
	 * parameter, an [[std::wstring]].
	 * @param prompt The prompt to use.
	 * @param output The variable to put the output in.
	 * @param log_color Whether to color the output. Defaults to false, can be
	 * omitted.
	 * @return
	 */
	template <class Num>
		bool get_num_input(
			const std::wstring & prompt, Num & output, bool log_color = false
		) {
			std::wstring input;

			while (true) {
				try {
					if (get_input(prompt, input, log_color)) {
						return true;
					}

					std::stringstream sstr(
						LD::w2str(LD::remove_surrounding_ws(input)));

					if (sstr.peek() == std::char_traits<wchar_t>::eof()) {
						throw std::runtime_error("empty input");
					}

					if ((
						    sstr >> output
					    ).peek() != std::char_traits<wchar_t>::eof()) {
						throw std::runtime_error("whole stream wasn't"
						                         " consumed");
					}

					return false;
				} catch (std::exception &) {
					errnl(L"You must enter a number!");
				}
			}
		}

	/**
	 * Gets a yes/no input from the user. You are advised to follow the normal
	 * CLI tradition, i.e. "Do this thing? [y/N]", including the capital "N".
	 *
	 * Throws an [[std::runtime_error]] if the user wishes to quit.
	 *
	 * @param prompt The prompt to show.
	 * @param log_color Whether to color it. Defaults to false.
	 * @return
	 */
	bool get_yn(const std::wstring & prompt, bool log_color = false) {
		std::wstring input;

		while (true) {
			if (get_input(prompt, input, log_color)) {
				throw USER_WANTS_QUIT;
			}

			std::transform(
				input.begin(), input.end(), input.begin(), ::tolower
			);

			if (input == L"y" || input == L"yes" || input == L"true" ||
			    input == L"1" || input == L"ye" || input == L"yeah" ||
			    input == L"absolutely" || input == L"i'm trapped in a computer"
				) {
				return true;
			} else if (input == L"n" || input == L"no" || input == L"false" ||
				       input == L"0" || input == L"nope" || input == L"never" ||
				       input == L"absolutely not" ||
				       input == L"is anyone there?"
				) {
				/*
				 * the fact that "is anyone there?" returns false is kind of
				 * sad, but it's true, to be honest
				 */
				return false;
			}
		}
	}

	/**
	 * Creates an option menu with the options `options`. Sets `selected` to the
	 * *index* of which item was selected.
	 *
	 * @param options
	 * @param selected
	 */
	void option_menu(
		const std::vector<std::wstring> options, math::Unsigned & selected
	) {
		/**
		 * store the menu so it can be printed more than once without
		 * recalculation
		 */
		std::wstringstream menu;

		/**
		 * make sure termcolor outputs ansi escapes to the menu
		 */
		menu
			// @formatter:off
	#ifdef LD_USE_TERMCOLOR
			<< GET_ANSI(termcolor::colorize)
	#endif
			// @formatter:on
			<< std::endl;

		/**
		 * just keeping track of iteration here
		 */
		math::Unsigned i = 0;

		std::wstring num_str;

		for (const std::wstring & option : options) {
			num_str = LD::s2wstr(i.to_string());

			menu << IMPORTANT
			     << num_str
			     // @formatter:off
	#ifdef LD_USE_TERMCOLOR
				 << GET_ANSI(termcolor::reset)
	#endif
				 // @formatter:on
				 << L") "
				 << option;

			if (i % 4 != 3) {
				menu << pad(option, 16);
			} else {
				menu << std::endl;
			}

			i++;
		}

		/*
		 * 0 instead of 3 here because `i` is incremented after the last
		 * iteration
		 */
		if (i % 4 != 0) {
			menu << std::endl;
		}

		menu << std::endl;

		std::wstring menu_str = menu.str();

		/**
		 * reuse this for multiple inputs
		 */
		std::wstring input;

		while (true) {
			o(menu_str);

			if (get_input(L"> ", input)) {
				selected = options.size();

				break;
			}

			nl();

			if (input.find_first_not_of(L"0123456789") != std::wstring::npos) {
				errnl(L"You must enter an integer!");

				continue;
			}

			math::Unsigned choice = LD::w2str(input);

			if (choice < options.size()) {
				selected = choice;

				return;
			} else {
				errnl(L"You must enter a valid choice!");
			}
		}
	}
}

#endif //__LD_INPUT_HPP
