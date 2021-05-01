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

#include <stddef.h>
#include <stdlib.h>

#include <LS_pipe.h>

#include <LS_queue.h>

LS_queue_t *LS_alloc_queue() {
	LS_queue_t *queue = malloc(sizeof(LS_queue_t));
	if(!queue) return 0;

	queue -> pipe = LS_alloc_pipe();
	if(!queue -> pipe) return 0;

	return queue;
}

void LS_free_queue(LS_queue_t *queue) {
	LS_free_pipe(queue -> pipe);
	free(queue -> pipe);

	free(queue);

	return;
}

size_t LS_sizeof_queue(LS_queue_t *queue) {
	return LS_sizeof_pipe(queue -> pipe);
}

LS_queuet_t *LS_enqueue(LS_queue_t *queue, void *input, void *output,
	void *(*function)(void *))
{
	LS_queuet_t *task = malloc(sizeof(LS_queuet_t));
	if(!task) return 0;

	if(!LS_pipe(queue -> pipe, (void *) task)) return 0;

	task -> input = input;
	task -> output = output;
	task -> function = function;

	return task;
}

void LS_do(LS_queue_t *queue) {
	size_t total = LS_sizeof_pipe(queue -> pipe);
	
	for(size_t i = 0; i < total; i++) {
		LS_queuet_t *task = (LS_queuet_t *) LS_pull(queue -> pipe);
		task -> output = task -> function(task -> input);
	}

	return;
}

int LS_do_p(LS_queue_t *queue) {
	int ret = pthread_create(&queue -> thread, 0, _LS_do_p, (void *) queue);
	return ret;
}

void *_LS_do_p(void *input) {
	LS_queue_t *queue = (LS_queue_t *) input;

	size_t total = LS_sizeof_pipe(queue -> pipe);
	
	for(size_t i = 0; i < total; i++) {
		LS_queuet_t *task = (LS_queuet_t *) LS_pull(queue -> pipe);
		task -> output = task -> function(task -> input);
	}

	return 0;
}

int LS_stop(LS_queue_t *queue) {
	void *exit;
	int ret = pthread_join(queue -> thread, &exit);

	return ret;
}