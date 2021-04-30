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

CC ?= gcc
CFLAGS += -L ./
CPPFLAGS += -std=c99 -Wall -Wextra -I ./ -I sources/ -I libSphysl/
EXT ?=

LD ?= ld

CLEAN += $(foreach obj,$(wildcard *.o) $(wildcard sources/*.o),rm $(obj);)

DEEP_CLEAN += $(foreach pdf,$(wildcard *.pdf),rm $(pdf);)
DEEP_CLEAN += $(foreach lib,$(wildcard *.a),rm $(lib);)

objs += $(patsubst %.c,%.o,$(wildcard *.c) $(wildcard sources/*.c))
progs += $(patsubst %.c,%$(EXT),$(wildcard *.c))
libs += -lSphysl

existing_progs += $(foreach prog,$(progs),$(wildcard $(prog)))

DEEP_CLEAN += $(foreach prog,$(existing_progs),rm $(prog);)

.PHONY : all clean deep-clean

all : $(progs)
	cd docs; make; cd ..
	mv docs/*.pdf ./
	rename -e 's/.pdf/-docs.pdf/g' *

clean :
	cd docs; make clean; cd ..
	cd libSphysl; make clean; cd ..
	$(CLEAN)

deep-clean : clean
	cd docs; make deep-clean; cd ..
	cd libSphysl; make deep-clean; cd ..
	-$(DEEP_CLEAN)

$(progs) : %$(EXT) : %.o sources.o libSphysl.a
	$(CC) $(CFLAGS) $< sources.o -o $@ $(libs)

$(objs) : %.o : %.c
	$(CC) $(CPPFLAGS) -c $< -o $@

sources.o : $(objs)
	$(LD) -r sources/*.o -o sources.o

libSphysl.a :
	cd libSphysl; make; cd ..
	mv libSphysl/*.a ./