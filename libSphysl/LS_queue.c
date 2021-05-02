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

	queue -> size = 0;

	queue -> err_func_ret = 0;
	queue -> pthreadc_ret = 0;
	queue -> pthreadj_ret = 0;

	return queue;
}

void LS_free_queue(LS_queue_t *queue) {
	LS_free_pipe(queue -> pipe);

	free(queue);

	return;
}

LS_qtask_t *LS_enqueue(LS_queue_t *queue, int (*func)(void *), void *arg) {
	LS_qtask_t *task = malloc(sizeof(LS_qtask_t));
	if(!task) return 0;

	LS_pframe_t *ret = LS_pipe(queue -> pipe, (void *) task);
	if(!ret) return 0;

	task -> func = func;
	task -> arg = arg;

	queue -> size++;

	return task;
}

int LS_do(LS_queue_t *queue) {
	LS_qtask_t *task = (LS_qtask_t *) LS_pull(queue -> pipe);

	while(task) {
		queue -> err_func_ret = task -> func(task -> arg);

		queue -> size--;

		if(queue -> err_func_ret) {
			queue -> err_task.func = task -> func;
			queue -> err_task.arg = task -> arg;

			return 1;
		}

		free(task);

		task = (LS_qtask_t *) LS_pull(queue -> pipe);
	}

	return 0;
}

void *_LS_do(void *arg) {
	LS_queue_t *queue = (LS_queue_t *) arg;

	LS_qtask_t *task = (LS_qtask_t *) LS_pull(queue -> pipe);

	while(task) {
		queue -> err_func_ret = task -> func(task -> arg);

		queue -> size--;

		if(queue -> err_func_ret) {
			queue -> err_task.func = task -> func;
			queue -> err_task.arg = task -> arg;

			return (void *) 1;
		}

		free(task);

		task = (LS_qtask_t *) LS_pull(queue -> pipe);
	}

	return 0;
}

int LS_start(LS_queue_t *queue) {
	queue -> pthreadc_ret = pthread_create(&queue -> thread, 0, _LS_do,
		(void *) queue);
	
	if(queue -> pthreadc_ret) return 1;

	return 0;
}

int LS_wait4(LS_queue_t *queue) {
	void *exit;
	queue -> pthreadj_ret = pthread_join(queue -> thread, &exit);

	if(queue -> pthreadj_ret) return 2;

	if(exit) return 1;

	return 0;
}