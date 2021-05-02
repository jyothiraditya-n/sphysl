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

LS_pipe_t *LS_alloc_pipe() {
	LS_pipe_t *pipe = malloc(sizeof(LS_pipe_t));
	if(!pipe) return 0;

	pipe -> in_frame = 0;
	pipe -> out_frame = 0;

	pipe -> size = 0;

	return pipe;
}

void LS_free_pipe(LS_pipe_t *pipe) {
	LS_pframe_t *current_frame = pipe -> in_frame;
	if(!current_frame) return;

	while(current_frame) {
		LS_pframe_t *frame_ahead = current_frame -> frame_ahead;

		free(current_frame);

		current_frame = frame_ahead;
	}

	free(pipe);
	
	return;
}

LS_pframe_t *LS_pipe(LS_pipe_t *pipe, void *data) {
	LS_pframe_t *new_frame = malloc(sizeof(LS_pframe_t));
	if(!new_frame) return 0;

	LS_pframe_t *in_frame = pipe -> in_frame;
	if(in_frame) in_frame -> frame_behind = new_frame;

	new_frame -> frame_ahead = in_frame;
	new_frame -> frame_behind = 0;

	new_frame -> data = data;

	pipe -> in_frame = new_frame;
	if(!pipe -> out_frame) pipe -> out_frame = new_frame;

	pipe -> size++;

	return new_frame;
}

void *LS_pull(LS_pipe_t *pipe) {
	LS_pframe_t *current_frame = pipe -> out_frame;
	if(!current_frame) return 0;

	LS_pframe_t *frame_behind = current_frame -> frame_behind;
	void *data = current_frame -> data;

	free(current_frame);

	if(frame_behind) {
		frame_behind -> frame_ahead = 0;

		pipe -> out_frame = frame_behind;

		pipe -> size--;
	}

	else {
		pipe -> in_frame = 0;
		pipe -> out_frame = 0;

		pipe -> size = 0;
	}

	return data;
}
