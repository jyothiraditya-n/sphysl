/* The Unsystematicaliser Physics Simulator (C) 2021 Jyothiraditya Nellakra
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

#ifndef S_SIGNAL_H
#define S_SIGNAL_H

#define S_STDIN 0
#define S_STDOUT 1

extern void S_handle_sigabrt(int signum);
extern void S_handle_sigint(int signum);
extern void S_handle_sigterm(int signum);

extern size_t _S_strlen(char *string);

#endif