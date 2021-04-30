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

FLAGS += -interaction="nonstopmode" -output-directory="build/"

DEEP_CLEAN += $(foreach pdf,$(wildcard *.pdf),rm $(pdf);)

docs = sphysl.pdf libSphysl.pdf

.PHONY : all clean deep-clean

all : $(docs)

clean : build/
	rm -r build/

deep-clean : clean
	$(DEEP_CLEAN)

$(docs) : %.pdf : %.tex build/
	pdflatex $(FLAGS) $<
	mv build/$*.pdf $@

build/ :
	mkdir -p build/