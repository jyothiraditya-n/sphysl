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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <LS_string.h>

int test(size_t test_size) {
	char string[test_size + 1];

	bool has_space = false;

	for(size_t i = 0; i < test_size; i++) {
		char strch = ' ' + (char) (rand() % ('~' - ' '));
		if(strch == ' ') has_space = true;

		string[i] = strch;
	}

	string[test_size] = 0;

	printf("strlen(string): %zu\n\n", strlen(string));

	printf("stripped = LS_strip(string);\n\n");
	char *stripped = LS_strip(string);

	printf("string: %s\n", string);
	printf("stripped: %s\n\n", stripped);

	bool result = LS_streq(string, stripped);

	printf("streq(string, stripped): %s\n", result ? "true" : "false");

	free(stripped);

	if(result != has_space) return 1;

	return 0;
}

int main(int argc, char **argv) {
	if(argc > 1) {
		printf("%s: Error: Too many arguments.\n", argv[0]);
		return 1;
	}

	time_t now;
	srand((unsigned) time(&now));

	for(size_t i = 1; i < 100; i++) {
		int ret = test(i);

		if(ret == 2) {
			printf("%s: Error: Library is faulty.\n", argv[0]);
			return 2;
		}

		printf("\n");
	}

	printf("%s: Library functions correctly.\n", argv[0]);

	return 0;
}