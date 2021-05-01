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

#include <stdio.h>

#include <S_shell.h>

#include <S_main.h>

char *S_execname;

int S_main(int argc, char **argv) {
	S_execname = argv[0];

	if(argc > 1) {
		printf("%s: Error: Too many arguments.\n", S_execname);
		return 1;
	}

	S_shell();

	return 0;
}