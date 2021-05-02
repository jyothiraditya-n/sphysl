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

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#include <S_consts.h>
#include <S_main.h>

#include <S_signal.h>

void S_handle_sigabrt(int signum) {
	(void) signum;

	char *message = "\n";
	write(S_STDOUT, message, _S_strlen(message));

	write(S_STDOUT, S_exec_name, _S_strlen(S_exec_name));
	
	message = ": Aborting...\n";
	write(S_STDOUT, message, _S_strlen(message));

	_exit(2);
}

void S_handle_sigint(int signum) {
	if(!S_interactive_mode) S_handle_sigterm(signum);

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, S_handle_sigint);

	char *message = "\nTo exit, type the command 'exit();' at the prompt.\n ";
	write(S_STDOUT, message, _S_strlen(message));

	return;
}

void S_handle_sigterm(int signum) {
	(void) signum;

	char *message = "\n";
	write(S_STDOUT, message, _S_strlen(message));

	write(S_STDOUT, S_exec_name, _S_strlen(S_exec_name));
	
	message = ": Terminating...\n";
	write(S_STDOUT, message, _S_strlen(message));

	_exit(0);
}

size_t _S_strlen(char *string) {
	size_t i = 0;
	while(string[i]) i++;
	
	return i;
}