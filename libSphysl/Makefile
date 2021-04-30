# The Simple Physics Simulation Language (C) 2021 Jyothiraditya Nellakra

# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later 
# version.

# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with
# this program. If not, see <https://www.gnu.org/licenses/>.

.DEFAULT_GOAL := all

AR ?= ar

CC ?= gcc
CPPFLAGS += -std=c99 -Wall -Wextra -I .

CLEAN += $(foreach obj,$(wildcard *.o),rm $(obj);)
DEEP_CLEAN += $(foreach lib,$(wildcard *.a),rm $(lib);)

objs = $(patsubst %.c,%.o,$(wildcard *.c))

.PHONY : all clean deep-clean

all : libSphysl.a

clean :
	$(CLEAN)

deep-clean : clean
	$(DEEP_CLEAN)

libSphysl.a : $(objs)
	$(AR) r libSphysl.a $(objs)

$(objs) : %.o : %.c
	$(CC) $(CPPFLAGS) -c $< -o $@