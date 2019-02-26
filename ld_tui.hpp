#ifndef __LD_TUI_HPP
#define __LD_TUI_HPP

#include <unistd.h>
#include <termios.h>
#include <vector>

#include "ld_ansi.hpp"
#include "ld_sutil.hpp"

namespace LD {
	namespace TUI {
		struct Keys {
			/**
			 * An enum of all possible keys. Only the first 128 can be
			 * returned by [[LD::TUI::_getch]], [[LD::TUI::getch]] uses
			 * the values above 127.
			 */
			enum Key : unsigned wchar_t {
				NUL = 0, SOH, STX, ETC, EOT, ENQ, ACK, BEL, BS, TAB, LF, VT, FF,
				CR, SO, SI, DLE, DC1, DC2, DC3, DC4, NAK, SYN, ETB, CAN, EM,
				SUB, ESC, FS, GS, RS, US, SPACE, EXCLAMATION, DBL_QUOTE,
				HASHTAG, DOLLAR, PERCENT, AMPERSAND, APOSTROPHE, O_PAREN,
				C_PAREN, STAR, PLUS, COMMA, HYPHEN, PERIOD, SLASH, ZERO, ONE,
				TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, COLON,
				SEMICOLON, O_ANGLE_BRACKET, EQUALS, C_ANGLE_BRACKET,
				QUESTION_MARK, AT, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O,
				P, Q, R, S, T, U, V, W, X, Y, Z, LEFT_SQUARE_BRACKET, BACKSLASH,
				RIGHT_SQUARE_BRACKET, CARET, UNDERSCORE, GRAVE, a, b, c, d, e,
				f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
				LEFT_CURLY_BRACE, PIPE, RIGHT_CURLY_BRACE, TILDE, DELETE,
				F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
				UP, DOWN, RIGHT, LEFT
			};

			static std::vector<std::wstring> key_debug;
		};

		/**
		 * Gets one character from the connected terminal.
		 *
		 * @return The character. Can only be in the range 0-127,
		 * inclusive.
		 */
		unsigned char _getch() {
			unsigned char  buf = 0;
			struct termios old {};

			tcgetattr(0, & old);

			tcflag_t old_icanon = old.c_lflag & ICANON,
			         old_echo   = old.c_lflag & ECHO;
			cc_t     old_vmin   = old.c_cc[VMIN],
			         old_vtime  = old.c_cc[VTIME];

			old.c_lflag &= ~ICANON;
			old.c_lflag &= ~ECHO;
			old.c_cc[VMIN]  = 1;
			old.c_cc[VTIME] = 0;

			tcsetattr(0, TCSANOW, & old);
			read(0, & buf, 1);

			old.c_lflag |= old_icanon;
			old.c_lflag |= old_echo;
			old.c_cc[VMIN]  = old_vmin;
			old.c_cc[VTIME] = old_vtime;

			tcsetattr(0, TCSADRAIN, & old);

			return buf;
		}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "RedundantCast"
#pragma ide diagnostic ignored "missing_default_case"

		Keys::Key getch() {
			unsigned char ch = _getch();

			if (ch != Keys::ESC) {
				return static_cast<Keys::Key>(ch);
			}

			switch (_getch()) {
				case Keys::LEFT_SQUARE_BRACKET: {
					ch = _getch();

					if (ch >= Keys::A && ch <= Keys::D) {
						return static_cast<Keys::Key>(Keys::UP + ch -
						                              Keys::A);
					}

					auto key = static_cast<Keys::Key>(ch);

					switch (ch) {
						case Keys::ONE:
							switch (_getch()) {
								case Keys::FIVE:
									key = Keys::F5;

									break;
								case Keys::SEVEN:
									key = Keys::F6;

									break;
								case Keys::EIGHT:
									key = Keys::F7;

									break;
								case Keys::NINE:
									key = Keys::F8;

									break;
							}

							break;
						case Keys::TWO:
							switch (_getch()) {
								case Keys::ZERO:
									key = Keys::F9;

									break;
								case Keys::ONE:
									key = Keys::F10;

									break;
								case Keys::THREE:
									key = Keys::F11;

									break;
								case Keys::FOUR:
									key = Keys::F12;

									break;
							}

							break;
					}

					_getch();

					return key;
				}
				case Keys::O:
					ch = _getch();

					if (ch >= Keys::P && ch <= Keys::S) {
						return static_cast<Keys::Key>(Keys::F1 + ch - Keys::P);
					}
			}

			return static_cast<Keys::Key>(ch);
		}

#pragma clang diagnostic pop
	}
}

std::vector<std::wstring> LD::TUI::Keys::key_debug = {
	L"NUL", L"SOH", L"STX", L"ETC", L"EOT", L"ENQ", L"ACK", L"BEL", L"BS",
	L"TAB", L"LF", L"VT", L"FF", L"CR", L"SO", L"SI", L"DLE", L"DC1", L"DC2",
	L"DC3", L"DC4", L"NAK", L"SYN", L"ETB", L"CAN", L"EM", L"SUB", L"ESC",
	L"FS", L"GS", L"RS", L"US", L"SPACE", L"EXCLAMATION", L"DBL_QUOTE",
	L"HASHTAG", L"DOLLAR", L"PERCENT", L"AMPERSAND", L"APOSTROPHE", L"O_PAREN",
	L"C_PAREN", L"STAR", L"PLUS", L"COMMA", L"HYPHEN", L"PERIOD", L"SLASH",
	L"ZERO", L"ONE", L"TWO", L"THREE", L"FOUR", L"FIVE", L"SIX", L"SEVEN",
	L"EIGHT", L"NINE", L"COLON", L"SEMICOLON", L"O_ANGLE_BRACKET", L"EQUALS",
	L"C_ANGLE_BRACKET", L"QUESTION_MARK", L"AT", L"A", L"B", L"C", L"D", L"E",
	L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q",
	L"R", L"S", L"T", L"U", L"V", L"W", L"X", L"Y", L"Z",
	L"LEFT_SQUARE_BRACKET", L"BACKSLASH", L"RIGHT_SQUARE_BRACKET", L"CARET",
	L"UNDERSCORE", L"GRAVE", L"a", L"b", L"c", L"d", L"e", L"f", L"g", L"h",
	L"i", L"j", L"k", L"l", L"m", L"n", L"o", L"p", L"q", L"r", L"s", L"t",
	L"u", L"v", L"w", L"x", L"y", L"z", L"LEFT_CURLY_BRACE", L"PIPE",
	L"RIGHT_CURLY_BRACE", L"TILDE", L"DELETE",
	L"F1", L"F2", L"F3", L"F4", L"F5", L"F6", L"F7", L"F8", L"F9", L"F10",
	L"F11", L"F12", L"UP", L"DOWN", L"RIGHT", L"LEFT"
};

#endif //__LD_TUI_HPP
