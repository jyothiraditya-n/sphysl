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
#include <pthread.h>

#include <LS_pipe.h>

#ifndef LS_QUEUE_H
#define LS_QUEUE_H

typedef struct {
	int (*func)(void *);
	void *arg;

} LS_qtask_t;

typedef struct {
	LS_pipe_t *pipe;

	pthread_t thread;

	int exit_status;
	int pthread_create;
	int pthread_join;

} LS_queue_t;

extern LS_queue_t *LS_alloc_queue();
extern void LS_free_queue(LS_queue_t *queue);
extern size_t LS_sizeof_queue(LS_queue_t *queue);

extern LS_qtask_t *LS_enqueue(LS_queue_t *queue, int (*func)(void *),
	void *arg);

extern int LS_finish(LS_queue_t *queue);
extern int LS_finish_p(LS_queue_t *queue);
extern int LS_wait4(LS_queue_t *queue);

extern void *_LS_finish_p(void *arg);

#endif