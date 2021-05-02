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

#ifndef LS_STACK_H
#define LS_STACK_H

typedef struct _LS_sframe_s {
	struct _LS_sframe_s *frame_below;

	void *data;

} LS_sframe_t;

typedef struct {
	LS_sframe_t *current_frame;

	size_t size;

} LS_stack_t;

extern LS_stack_t *LS_alloc_stack();
extern void LS_free_stack(LS_stack_t *stack);

extern LS_sframe_t *LS_push(LS_stack_t *stack, void *data);
extern void *LS_pop(LS_stack_t *stack);

#endif