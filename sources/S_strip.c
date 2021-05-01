/* The Unsystematicaliser Physics Simulator (C) 2021 Jyothiraditya Nellakra
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
#include <stddef.h>
#include <string.h>

#include <S_strip.h>

void S_strip(char *string) {
	size_t length = strlen(string);
	if(length == 0) return;

	size_t i = 0;
	size_t j = 0;

	while(j < length) {
		if(!isspace(string[j])) {
			string[i] = string[j];
			i++;
		}

		j++;
	}

	string[i] = 0;

	return;
}