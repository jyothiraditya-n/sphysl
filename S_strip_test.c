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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <S_consts.h>
#include <S_strip.h>

int main(int argc, char **argv) {
	if(argc > 1) {
		printf("%s: Error: Too many arguments.\n", argv[0]);
		return 1;
	}

	time_t now;
	srand((unsigned) time(&now));

	while(1) {
		char string[S_BUFSIZE];

		for(size_t i = 0; i < S_BUFSIZE - 1; i++) {
			string[i] = ' ' + (char) (rand() % ('~' - ' '));
		}

		string[S_BUFSIZE - 1] = 0;

		printf("Random String:\n\n");
		printf("%s\n\n", string);

		S_strip(string);

		printf("Stripped String:\n\n");
		printf("%s\n\n", string);
	}

	return 0;
}