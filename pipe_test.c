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

#include <LS_rand.h>
#include <LS_pipe.h>

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

	while(1) {
		int op = rand() % 4;

		if(op == 0) {
			LS_free_pipe(pipe);

			printf("LS_free_pipe(pipe)\n");
		}

		else if(op == 1) {
			size_t return_val = LS_sizeof_pipe(pipe);

			printf("LS_sizeof_pipe(pipe) = %zu\n", return_val);
		}

		else if(op == 2) {
			void *operand = LS_randp();
			LS_pipe(pipe, operand);

			printf("LS_pipe(pipe, %p)\n", operand);
		}

		else {
			void *return_val = LS_pull(pipe);

			printf("LS_pull(pipe) = %p\n", return_val);
		}
	}

	return 0;
}