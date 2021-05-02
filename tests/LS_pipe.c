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

#include <LS_pipe.h>
#include <LS_rand.h>

int test(LS_pipe_t *pipe, size_t test_size) {
	void *data[test_size];

	size_t size = 0;

	for(size_t i = 0; i < test_size; i++) {
		data[i] = LS_randp();
		void *value = data[i];

		LS_pframe_t *ret = LS_pipe(pipe, value);
		if(!ret) return 1;

		printf("LS_pipe(pipe, %p);\n", value);
		size++;

		if(pipe -> size != size) {
			printf("\npipe -> size != size\n");
			printf("%zu != %zu\n\n", pipe -> size, size);

			return 2;
		}
	}

	printf("\n");

	for(size_t i = 0; i < test_size; i++) {
		void *ret_value = LS_pull(pipe);
		printf("LS_pull(pipe): %p\n", ret_value);
		size--;

		void *value = data[i];

		if(ret_value != value) {
			printf("\n%p != %p\n\n", ret_value, value);
			return 2;
		}

		if(pipe -> size != size) {
			printf("\npipe -> size != size\n");
			printf("%zu != %zu\n\n", pipe -> size, size);

			return 2;
		}
	}

	return 0;
}

int main(int argc, char **argv) {
	if(argc > 1) {
		printf("%s: Error: Too many arguments.\n", argv[0]);
		return 1;
	}

	LS_pipe_t *pipe = LS_alloc_pipe();
	
	if(!pipe) { 
		printf("%s: Error: Cannot create pipe.\n", argv[0]);
		return 2;
	}

	time_t now;
	srand((unsigned) time(&now));

	for(size_t i = 1; i < 10; i++) {
		int ret = test(pipe, i);

		if(ret == 1) {
			printf("%s: Error: Cannot allocate memory.\n", argv[0]);
			return 3;
		}

		if(ret == 2) {
			printf("%s: Error: Library is faulty.\n", argv[0]);
			return 4;
		}

		printf("\n");
	}

	printf("%s: Library functions correctly.\n", argv[0]);

	LS_free_pipe(pipe);

	return 0;
}