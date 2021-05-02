/* The Simple Physics Simulation Language (C) 2021 Jyothiraditya Nellakra
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later 
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more 
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>. */

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <LS_string.h>

bool LS_streq(const char *str1, const char *str2) {
	size_t strlength = strlen(str1);
	if(strlength != strlen(str2)) return false;

	size_t i = 0;
	char str1ch = str1[0];

	while(str1ch) {
		if(str1ch != str2[i]) return false;

		i++;
		str1ch = str1[i];
	}

	return true;
}

char *LS_strip(const char *source) {
	size_t length = strlen(source);

	char *dest = malloc(length);

	size_t i = 0;
	size_t j = 0;

	while(j < length) {
		if(!isspace(source[j])) {
			dest[i] = source[j];
			i++;
		}

		j++;
	}

	dest[i] = 0;

	return dest;
}