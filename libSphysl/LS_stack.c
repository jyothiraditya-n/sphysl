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

#include <LS_stack.h>

LS_stack_t *LS_alloc_stack() {
	LS_stack_t *stack = malloc(sizeof(LS_stack_t));
	if(!stack) return 0;

	stack -> current_frame = 0;
	stack -> num_frames = 0;

	return stack;
}

void LS_free_stack(LS_stack_t *stack) {
	LS_sframe_t *current_frame = stack -> current_frame;
	if(!current_frame) return;

	while(current_frame) {
		LS_sframe_t *frame_below = current_frame -> frame_below;

		free(current_frame);

		current_frame = frame_below;
	}

	stack -> current_frame = 0;
	stack -> num_frames = 0;

	return;
}

size_t LS_sizeof_stack(LS_stack_t *stack) {
	return stack -> num_frames;
}

LS_sframe_t *LS_push(LS_stack_t *stack, void *data) {
	LS_sframe_t *new_frame = malloc(sizeof(LS_sframe_t));
	if(!new_frame) return 0;

	new_frame -> frame_below = stack -> current_frame;
	new_frame -> data = data;

	stack -> current_frame = new_frame;
	stack -> num_frames++;

	return new_frame;
}

void *LS_pop(LS_stack_t *stack) {
	LS_sframe_t *current_frame = stack -> current_frame;
	if(!current_frame) return 0;

	LS_sframe_t *frame_below = current_frame -> frame_below;
	void *data = current_frame -> data;
	
	free(current_frame);

	stack -> current_frame = frame_below;
	stack -> num_frames--;

	return data;
}