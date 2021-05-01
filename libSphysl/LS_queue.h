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

#include <LS_pipe.h>

#ifndef LS_QUEUE_H
#define LS_QUEUE_H

typedef struct {
	void *input;
	void *output;
	void *(*function)(void *);

} LS_queuet_t;

typedef struct {
	LS_pipe_t *pipe;

} LS_queue_t;

extern LS_queue_t *LS_alloc_queue();
extern void LS_free_queue(LS_queue_t *queue);
extern size_t LS_sizeof_queue(LS_queue_t *queue);

extern LS_queuet_t *LS_enqueue(LS_queue_t *queue, void *input, void *output,
	void *(*function)(void *));

extern void LS_do(LS_queue_t *queue, size_t num);
extern void LS_finish(LS_queue_t *queue);

#endif