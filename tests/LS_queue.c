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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <LS_queue.h>
#include <LS_rand.h>

bool is_prime(size_t value) {
	for(size_t i = 2; i < value; i += 2) {
		if(value % i == 0) return false;
	}

	return true;
}

int func(void *input) {
	size_t value = (size_t) input;
	
	if(!is_prime(value)) {
		printf("%zu is not a prime number.\n", value);
		return 1;
	}

	printf("%zu is a prime number.\n", value);
	return 0;
}

int test(LS_queue_t *queue1, LS_queue_t *queue2, size_t test_size) {
	for(size_t i = 0; i < test_size; i++) {
		void *prime = LS_randp_in(1, 1000);

		printf("LS_enqueue(queue1, func, %zu);\n", (size_t) prime);
		LS_qtask_t *ret = LS_enqueue(queue1, func, prime);
		if(!ret) return 1;

		prime = LS_randp_in(1, 1000);

		printf("LS_enqueue(queue2, func, %zu);\n", (size_t) prime);
		ret = LS_enqueue(queue2, func, prime);
		if(!ret) return 1;
	}

	printf("\n");

	int ret1 = LS_start(queue1);
	int ret2 = LS_do(queue2);
	int ret3 = LS_wait4(queue1);

	if(ret1 == 1) return 2;

	if(ret2 == 1 && queue2 -> err_func_ret != 1) return 3;
	if(ret3 == 1 && queue1 -> err_func_ret != 1) return 3;

	if(ret3 == 2) return 4;

	return 0;
}

int main(int argc, char **argv) {
	if(argc > 1) {
		printf("%s: Error: Too many arguments.\n", argv[0]);
		return 1;
	}

	LS_queue_t *queue1 = LS_alloc_queue();
	LS_queue_t *queue2 = LS_alloc_queue();

	if(!queue1 || !queue2) { 
		printf("%s: Error: Cannot create queue.\n", argv[0]);
		return 2;
	}

	time_t now;
	srand((unsigned) time(&now));

	for(size_t i = 1; i < 10; i++) {
		int ret = test(queue1, queue2, i);

		if(ret == 1) {
			printf("%s: Error: Cannot allocate memory.\n", argv[0]);
			return 3;
		}

		if(ret == 2) {
			printf("%s: Error: Cannot create threads.\n", argv[0]);
			return 4;
		}

		if(ret == 3) {
			printf("%s: Error: Library is faulty.\n", argv[0]);
			return 5;
		}

		if(ret == 4) {
			printf("%s: Error: Cannot rejoin threads.\n", argv[0]);
			return 6;
		}

		printf("\n");
	}

	printf("%s: Library functions correctly.\n", argv[0]);

	LS_free_queue(queue1);
	LS_free_queue(queue2);

	return 0;
}