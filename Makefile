
# Compiler
CC := gcc
CPP := g++
AR := ar

# Package name
pkg_name := kmrJsoncpp

# Source code directory
src_dir := src

# Build directory
build_dir := build

# Library name
lib_name := $(build_dir)/lib$(pkg_name)

# Install directory
install_dir := /usr/local

# Compiler flags
CFLAGS := -Wall -Wextra -g -fPIC

# Defines
DEFINES :=

# Includes
includes := -Iinclude

# Source files
sources := $(src_dir)/json_array.cpp \
		   $(src_dir)/json_base.cpp \
		   $(src_dir)/json_bool.cpp \
		   $(src_dir)/json_integer.cpp \
		   $(src_dir)/json_object.cpp \
		   $(src_dir)/json_real.cpp \
		   $(src_dir)/json_string.cpp \
		   \

# Object files
cpp_objs := $(patsubst %.cpp, $(build_dir)/%.o, $(filter %.cpp, $(sources)))
c_objs := $(patsubst %.c, $(build_dir)/%.o, $(filter %.c, $(sources)))
objects := $(cpp_objs) $(c_objs)

# make all target
all: $(lib_name).so $(lib_name).a

$(lib_name).so: $(objects)
	$(CPP) -shared -o $@ $^

$(lib_name).a: $(objects)
	$(AR) rcs $@ $^

$(build_dir)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CPP) $(CFLAGS) $(DEFINES) $(includes) -o $@ -c $<

$(build_dir)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEFINES) $(includes) -o $@ -c $<

#make install target
install: all
	mkdir -p $(install_dir)/lib
	mkdir -p $(install_dir)/include/$(pkg_name)

	cp $(lib_name).so $(install_dir)/lib/
	cp $(lib_name).a  $(install_dir)/lib/

	cp  include/* $(install_dir)/include/$(pkg_name)/

clean:
	rm -rf $(build_dir)

.PHONY: all clean

