build_dir = ./build
src_dir = ./src
objects = $(build_dir)/main.o $(build_dir)/input/sanitation.o \
					$(build_dir)/input/processing.o \
					$(build_dir)/input/parsing.o \
					$(build_dir)/utils/constants.o \
					$(build_dir)/utils/commands-map.o

dsh: pre-build $(objects)
	  gcc -o $(build_dir)/dsh $(objects)

pre-build:
	mkdir -p $(build_dir)/input
	mkdir -p $(build_dir)/utils

$(build_dir)/main.o: $(src_dir)/main.c
	gcc -c $(src_dir)/main.c -o $(build_dir)/main.o

$(build_dir)/input/sanitation.o: $(src_dir)/input/sanitation.c $(src_dir)/input/sanitation.h
	gcc -c $(src_dir)/input/sanitation.c -o $(build_dir)/input/sanitation.o

$(build_dir)/input/processing.o: $(src_dir)/input/processing.c $(src_dir)/input/processing.h
	gcc -c $(src_dir)/input/processing.c -o $(build_dir)/input/processing.o

$(build_dir)/input/parsing.o: $(src_dir)/input/parsing.c $(src_dir)/input/parsing.h
	gcc -c $(src_dir)/input/parsing.c -o $(build_dir)/input/parsing.o

$(build_dir)/utils/constants.o: $(src_dir)/utils/constants.c $(src_dir)/utils/constants.h
	gcc -c $(src_dir)/utils/constants.c -o $(build_dir)/utils/constants.o

$(build_dir)/utils/commands-map.o: $(src_dir)/utils/commands-map.c $(src_dir)/utils/commands-map.h
	gcc -c $(src_dir)/utils/commands-map.c -o $(build_dir)/utils/commands-map.o

clean: 
	rm $(build_dir)/dsh $(objects)
