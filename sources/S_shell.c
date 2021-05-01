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

#include <stdbool.h>
#include <stdio.h>

#include <LS_streq.h>

#include <S_consts.h>
#include <S_main.h>
#include <S_strip.h>

#include <S_shell.h>

void S_shell() {
	bool exit_condition = false;

	while(!exit_condition) {
		printf("%s> ", S_execname);

		char input[S_BUFSIZE];
		fgets(input, S_BUFSIZE, stdin);
		S_strip(input);

		if(LS_streq(input, "exit")) exit_condition = true;
	}
}