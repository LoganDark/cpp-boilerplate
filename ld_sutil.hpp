#ifndef __LD_SUTIL_HPP
#define __LD_SUTIL_HPP

#include <istream>
#include <string>
#include <sstream>
#include <vector>

namespace LD {
	/**
	 * Consumes the next word from a [[std::wstringstream]], accounting for extra
	 * whitespace between words.
	 *
	 * @param stream The stream to consume the word from.
	 * @param output The string to put the output inside.
	 */
	void consume_word(
		std::basic_istream<wchar_t> & stream, std::wstring & output,
		std::wstring * trailingwhite = nullptr
	) {
		bool clearing_whitespace = false;

		while (true) {
			wchar_t next_int = stream.peek();

			if (next_int == std::char_traits<wchar_t>::eof()) {
				break;
			}

			wchar_t next = static_cast<char>(next_int);

			bool is_whitespace = std::isspace(next) != 0;

			if (clearing_whitespace) {
				if (is_whitespace) {
					int white = stream.get();

					if (trailingwhite != nullptr) {
						trailingwhite->append(1, white);
					}
				} else {
					break;
				}
			} else {
				if (is_whitespace) {
					clearing_whitespace = true;
				} else {
					output.append(1, stream.get());
				}
			}
		}
	}

	/**
	 * Removes leading whitespace from a string.
	 *
	 * @param str
	 * @return
	 */
	std::wstring remove_leading_ws(const std::wstring & str) {
		unsigned long pos = 0;

		while (pos < str.length() - 1 && std::isspace(str[pos]) != 0) {
			pos++;
		}

		return str.substr(pos);
	}

	/**
	 * Removes trailing whitespace from a string.
	 *
	 * @param str
	 * @return
	 */
	std::wstring remove_trailing_ws(const std::wstring & str) {
		unsigned long len = str.length();

		while (len > 0 && std::isspace(str[len - 1]) != 0) {
			len--;
		}

		return str.substr(0, len);
	}

	/**
	 * Removes surrounding (both leading and trailing) whitespace from a string.
	 *
	 * @param str
	 * @return
	 */
	std::wstring remove_surrounding_ws(const std::wstring & str) {
		return remove_leading_ws(remove_trailing_ws(str));
	}

	/**
	 * @param src The source string.
	 * @param width The width to pad the string to.
	 * @param character The character to pad with.
	 * @param lpad If this is true, pad from the left instead of the right.
	 * @return The padded string, guaranteed to be `width` characters long
	 */
	std::wstring pad(const std::wstring & src, unsigned long width,
	                 wchar_t character = ' ', bool lpad = false) {
		if (src.size() > width) {
			return src.substr(0, width);
		} else {
			std::wstring built;

			if (lpad) {
				built.append(width, character);
				built.append(src);

				return built.substr(src.size());
			} else {
				built.append(src);
				built.append(width, character);

				return built.substr(0, width);
			}
		}
	}

	template <class Char>
		std::vector<std::basic_string<Char>> split_str(
			const std::basic_string<Char> & str, const Char & ch) {
			std::vector<std::basic_string<Char>> strs;
			std::basic_stringstream<Char>        ss;

			size_t last = 0;
			size_t len  = 0;
			Char   peeked;
			while ((peeked = ss.peek()) != std::char_traits<Char>::eof()) {
				if (peeked == ch) {
					strs.push_back(str.substr(last, len));
					last += len + 1;
					len = 0;
				} else {
					len++;
				}
			}

			strs.push_back(str.substr(last, str.size() - last));

			return strs;
		}

	template <class Char>
		std::basic_string<Char> join_str(
			const std::vector<std::basic_string<Char>> & strs,
			const Char & ch) {
			if (strs.empty()) {
				return L"";
			}

			std::basic_string<Char> str;

			for (size_t i = 0; i < strs.size(); i++) {
				str.append(strs[i]);

				if (i < strs.size() - 1) {
					str.append(1, ch);
				}
			}

			return str;
		}

	std::wstring pad_multiline(const std::wstring & src, unsigned long width,
	                           wchar_t character = ' ', bool lpad = false) {
		std::vector<std::wstring> lines = split_str(src, L'\n');

		for (auto & line : lines) {
			line = pad(line, width, character, lpad);
		}

		return join_str(lines, L'\n');
	}

	std::pair<size_t, size_t> get_dimensions(const std::wstring & str) {
		std::wstringstream        ss(str);
		std::vector<std::wstring> lines = split_str(str, L'\n');
		size_t                    width = 0;

		for (const auto & line : lines) {
			if (line.size() > width) {
				width = line.size();
			}
		}

		return std::make_pair(width, lines.size());
	}

	std::pair<
		std::pair<
			std::vector<size_t>,
			std::vector<size_t>
		>,
		std::vector<std::vector<std::wstring>>
	> tabulate(
		const std::vector<std::vector<std::wstring>> & tbl, bool lpad = false) {
		if (tbl.empty()) {
			return {};
		}

		std::vector<size_t> cols;
		std::vector<size_t> rows;

		size_t width  = tbl.cbegin()->size();
		size_t height = tbl.size();

		cols.resize(width);
		rows.resize(height);

		std::vector<std::vector<std::wstring>> padded;

		padded.resize(height);

		for (auto & row : padded) {
			row.resize(width);
		}

		for (size_t y = 0; y < height; y++) {
			for (size_t x = 0; x < width; x++) {
				auto dims = get_dimensions(tbl.at(y).at(x));

				if (dims.first > cols[x]) {
					cols[x] = dims.first;
				}

				if (dims.second > rows[y]) {
					rows[y] = dims.second;
				}
			}
		}

		for (size_t y = 0; y < height; y++) {
			std::vector<std::wstring>       & padded_row = padded[y];
			const std::vector<std::wstring> & tbl_row    = tbl[y];

			for (size_t x = 0; x < width; x++) {
				padded_row[x] = pad_multiline(tbl_row[x], cols[x], ' ', lpad);
			}
		}

		return std::make_pair(std::make_pair(rows, cols), padded);
	}

	std::wstring render_tabulated(const std::pair<
		std::pair<
			std::vector<size_t>,
			std::vector<size_t>
		>,
		std::vector<std::vector<std::wstring>>
	> & data) {
		std::wstring result;

		auto rowcols = data.first;
		auto padded  = data.second;

		auto rows = rowcols.first,
		     cols = rowcols.second;

		result.append(L"┌");

		for (size_t i = 0; i < cols.size(); i++) {
			std::wstring built;
			built.append(cols[i] + 2, L'─');
			built.append(i == cols.size() - 1 ? L"┐\n" : L"┬");
			result.append(built);
		}

		for (size_t r = 0; r < rows.size(); r++) {
			auto & row_v = padded[r];

			result.append(L"│");

			size_t c = 0;
			for (auto & col_str : row_v) {
				result.append(L" " + col_str + L" │");

				c++;
			}

			result.append(r == rows.size() - 1 ? L"\n└" : L"\n├");

			for (size_t i = 0; i < cols.size(); i++) {
				std::wstring built;
				built.append(cols[i] + 2, L'─');
				built.append(r == rows.size() - 1
				             ? (i == cols.size() - 1 ? L"┘\n" : L"┴")
				             : (i == cols.size() - 1 ? L"┤\n" : L"┼"));
				result.append(built);
			}
		}

		return result.substr(0, result.size() - 1);
	}
}

#endif //__LD_SUTIL_HPP
