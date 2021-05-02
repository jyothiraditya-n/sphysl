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

#ifndef LS_PIPE_H
#define LS_PIPE_H

typedef struct _LS_pframe_s {
	struct _LS_pframe_s *frame_ahead;
	struct _LS_pframe_s *frame_behind;

	void *data;

} LS_pframe_t;

typedef struct {
	LS_pframe_t *in_frame;
	LS_pframe_t *out_frame;

	size_t size;

} LS_pipe_t;

extern LS_pipe_t *LS_alloc_pipe();
extern void LS_free_pipe(LS_pipe_t *pipe);

extern LS_pframe_t *LS_pipe(LS_pipe_t *pipe, void *data);
extern void *LS_pull(LS_pipe_t *pipe);

#endif