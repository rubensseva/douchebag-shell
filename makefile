build_dir = ./build
src_dir = ./src
objects = $(build_dir)/main.o $(build_dir)/input/sanitation.o \
					$(build_dir)/input/processing.o \
					$(build_dir)/input/parsing.o \
					$(build_dir)/utils/constants.o \
					$(build_dir)/utils/env.o \
					$(build_dir)/command/command-map.o \

flags_1 = -c -g
flags_2 = -g


dsh: pre-build $(objects)
	  gcc -o $(build_dir)/dsh $(objects)

pre-build:
	mkdir -p $(build_dir)/input
	mkdir -p $(build_dir)/utils
	mkdir -p $(build_dir)/command


$(build_dir)/main.o: $(src_dir)/main.c
	gcc $(flags_1) $(src_dir)/main.c -o $(build_dir)/main.o

sanitation = input/sanitation
$(build_dir)/$(sanition).o: $(src_dir)/$(sanitation).c $(src_dir)/$(sanitation).h
	gcc $(flags_1) $(src_dir)/$(sanitation).c -o $(build_dir)/$(sanitation).o

processing = input/processing
$(build_dir)/$(processing).o: $(src_dir)/$(processing).c $(src_dir)/$(processing).h
	gcc $(flags_1) $(src_dir)/$(processing).c -o $(build_dir)/$(processing).o

parsing = input/parsing
$(build_dir)/$(parsing).o: $(src_dir)/$(parsing).c $(src_dir)/$(parsing).h
	gcc $(flags_1) $(src_dir)/$(parsing).c -o $(build_dir)/$(parsing).o

constants = utils/constants
$(build_dir)/$(constants).o: $(src_dir)/$(constants).c $(src_dir)/$(constants).h
	gcc $(flags_1) $(src_dir)/$(constants).c -o $(build_dir)/$(constants).o

command-map = command/command-map
$(build_dir)/$(command-map).o: $(src_dir)/$(command-map).c $(src_dir)/$(command-map).h
	gcc $(flags_1) $(src_dir)/$(command-map).c -o $(build_dir)/$(command-map).o

env = utils/env
$(build_dir)/$(env).o: $(src_dir)/$(env).c $(src_dir)/$(env).h
	gcc $(flags_1) $(src_dir)/$(env).c -o $(build_dir)/$(env).o

clean: 
	rm $(build_dir)/dsh $(objects)
