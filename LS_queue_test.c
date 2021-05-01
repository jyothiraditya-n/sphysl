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
#include <LS_queue.h>

int is_prime(void *input) {
	size_t value = (size_t) input;
	
	for(size_t i = 2; i < value; i += 2) {
		if(value % i == 0) {
			printf("%zu is not a prime number.\n", value);
			return 0;
		}
	}

	printf("%zu is a prime number.\n", value);
	return 0;
}

int main(int argc, char **argv) {
	if(argc > 1) {
		printf("%s: Error: Too many arguments.\n", argv[0]);
		return 1;
	}

	time_t now;
	srand((unsigned) time(&now));

	LS_queue_t *queue = LS_alloc_queue();

	if(!queue) { 
		printf("%s: Error: Cannot create queue.\n", argv[0]);
		return 2;
	}

	while(1) {
		size_t more_primes = LS_rand() % (10 - LS_sizeof_queue(queue));

		while(more_primes) {
			void *prime = (void *) (LS_rand() % 1048576);

			printf("\nLS_enqueue(queue, is_prime, %zu)\n",
				(size_t) prime);

			LS_qtask_t *ret = LS_enqueue(queue, is_prime, prime);

			if(!ret) {
				printf("%s: Error: Cannot initialise queue.\n",
					argv[0]);

				return 3;
			}

			more_primes = LS_rand() % (10 - LS_sizeof_queue(queue));
		}

		size_t op = rand() % 2;

		if(op) {
			printf("\nLS_finish(queue);\n\n");
			int ret = LS_finish(queue);

			if(ret) {
				printf("%s: Error running tasks.\n",
					argv[0]);

				return 4;
			}
		}

		else {
			printf("\nLS_finish_p(queue);\n\n");
			int ret = LS_finish_p(queue);

			if(ret) {
				printf("%s: Error running tasks.\n",
					argv[0]);

				return 4;
			}

			LS_wait4(queue);

			if(ret) {
				printf("%s: Error running tasks.\n",
					argv[0]);

				return 4;
			}
		}
	}
}