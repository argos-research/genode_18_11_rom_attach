/*
 * \brief   Color representation
 * \date    2006-08-04
 * \author  Norman Feske
 */

/*
 * Copyright (C) 2006-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__UTIL__COLOR_H_
#define _INCLUDE__UTIL__COLOR_H_

#include <util/string.h>

namespace Genode {
	struct Color;

	inline size_t ascii_to(const char *, Color &);
}


struct Genode::Color
{
	int r, g, b, a;

	bool opaque()      const { return a == 255; }
	bool transparent() const { return a == 0; }

	/*
	 * \deprecated  use 'opaque' and 'transparent' instead
	 */
	bool is_opaque()      const { return opaque(); }
	bool is_transparent() const { return transparent(); }

	Color(int red, int green, int blue, int alpha = 255)
	: r(red), g(green), b(blue), a(alpha) { }

	Color(): r(0), g(0), b(0), a(0) { }

	bool operator == (Color const &other) const {
		return other.r == r && other.g == g && other.b == b; }

	bool operator != (Color const &other) const {
		return !operator == (other); }

	void print(Output &output) const
	{
		using Genode::print;

		print(output, Char('#'));
		print(output, Hex((unsigned char)r, Hex::OMIT_PREFIX, Hex::PAD));
		print(output, Hex((unsigned char)g, Hex::OMIT_PREFIX, Hex::PAD));
		print(output, Hex((unsigned char)b, Hex::OMIT_PREFIX, Hex::PAD));

		if (a != 255)
			print(output, Hex((unsigned char)a, Hex::OMIT_PREFIX, Hex::PAD));
	}
};


/**
 * Convert ASCII string to Color
 *
 * The ASCII string must have the format '#rrggbb' or '#rrggbbaa'.
 *
 * \return number of consumed characters, or 0 if the string contains
 *         no valid color
 */
inline Genode::size_t Genode::ascii_to(const char *s, Genode::Color &result)
{
	/* validate string */
	Genode::size_t const len = strlen(s);

	if (len < 7 || *s != '#') return 0;

	enum { HEX = true };

	for (unsigned i = 0; i < 6; i++)
		if (!is_digit(s[i + 1], HEX)) return 0;

	int const red   = 16*digit(s[1], HEX) + digit(s[2], HEX),
	          green = 16*digit(s[3], HEX) + digit(s[4], HEX),
	          blue  = 16*digit(s[5], HEX) + digit(s[6], HEX);

	bool const has_alpha = (len >= 9) && is_digit(s[7], HEX) && is_digit(s[8], HEX);

	int const alpha = has_alpha ? 16*digit(s[7], HEX) + digit(s[8], HEX) : 255;

	result = Color(red, green, blue, alpha);

	return has_alpha ? 9 : 7;
}

#endif /* _INCLUDE__UTIL__COLOR_H_ */
