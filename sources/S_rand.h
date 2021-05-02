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

#include <stdint.h>
#include <stdlib.h>

#ifndef S_RAND_H

#if UINTPTR_MAX == 0xFFFFFFFF

#define S_rand() ((size_t) rand())

#elif UINTPTR_MAX == 0xFFFFFFFFFFFFFFFF

#define S_rand() ((size_t) rand() + ((size_t) rand() << 32))

#endif

#define S_rand_in(lim1, lim2) (lim1 + (S_rand() % (lim2 - lim1)))

#define S_randp() (void *) S_rand()
#define S_randp_in(lim1, lim2) (void *) S_rand_in(lim1, lim2)

#endif