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

	return;
}

size_t LS_sizeof_queue(LS_queue_t *queue) {
	return LS_sizeof_pipe(queue -> pipe);
}

LS_qtask_t *LS_enqueue(LS_queue_t *queue, int (*func)(void *),
	void *arg)
{
	LS_qtask_t *task = malloc(sizeof(LS_qtask_t));
	if(!task) return 0;

	LS_pframe_t *ret = LS_pipe(queue -> pipe, (void *) task);
	if(!ret) return 0;

	task -> func = func;
	task -> arg = arg;

	return task;
}

int LS_finish(LS_queue_t *queue) {
	LS_qtask_t *task = (LS_qtask_t *) LS_pull(queue -> pipe);

	while(task) {
		int ret = task -> func(task -> arg);
		
		if(ret) {
			queue -> exit_status = ret;
			return 1;
		}

		free(task);

		task = (LS_qtask_t *) LS_pull(queue -> pipe);
	}

	return 0;
}

int LS_finish_p(LS_queue_t *queue) {
	int ret = pthread_create(&queue -> thread, 0, _LS_finish_p,
		(void *) queue);
	
	if(ret) {
		queue -> pthread_create = ret;
		return 2;
	}

	return 0;
}

void *_LS_finish_p(void *arg) {
	LS_queue_t *queue = (LS_queue_t *) arg;

	LS_qtask_t *task = (LS_qtask_t *) LS_pull(queue -> pipe);

	while(task) {
		int ret = task -> func(task -> arg);
		
		if(ret) {
			queue -> exit_status = ret;
			return (void *) 1;
		}

		free(task);

		task = (LS_qtask_t *) LS_pull(queue -> pipe);
	}

	return 0;
}

int LS_wait4(LS_queue_t *queue) {
	void *exit;
	int ret = pthread_join(queue -> thread, &exit);

	if(ret) {
		queue -> pthread_join = ret;
		return 3;
	}

	if(exit) {
		return 1;
	}

	return 0;
}