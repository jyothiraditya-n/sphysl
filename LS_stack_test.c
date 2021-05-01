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
#include <LS_stack.h>

int main(int argc, char **argv) {
	if(argc > 1) {
		printf("%s: Error: Too many arguments.\n", argv[0]);
		return 1;
	}

	LS_stack_t *stack = LS_alloc_stack();

	if(!stack) {
		printf("%s: Error: Cannot create stack.\n", argv[0]);
		return 2;
	}

	time_t now;
	srand((unsigned) time(&now));

	while(1) {
		int total = (4 + (10 - LS_sizeof_stack(stack)));
		int op = rand() % total;

		if(op == 0) {
			LS_free_stack(stack);

			printf("LS_free_stack(stack);\n");
		}

		else if(op == 1) {
			size_t return_val = LS_sizeof_stack(stack);

			printf("LS_sizeof_stack(stack) = %zu;\n", return_val);
		}

		else if(op == total - 1) {
			void *return_val = LS_pop(stack);

			printf("LS_pop(stack) = %p;\n", return_val);
		}

		else {
			void *operand = LS_randp();
			LS_sframe_t *ret = LS_push(stack, operand);

			if(!ret) {
				printf("%s: Error running tasks.\n",
					argv[0]);

				return 3;
			}

			printf("LS_push(stack, %p);\n", operand);
		}
	}

	return 0;
}