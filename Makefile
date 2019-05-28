#Test_area Makefile for c /cpp/ assembly compilation with explanations
#NOTE: compiles cpp/c/assm to single executable

#MAKEFILE BASE SETUP

#Added to avoid problems for make if SHELL is defined by environment elsewhere
SHELL = /bin/sh
#In case different make programs have different suffix lists and implicit rules
#Done to improve portability. First line clears list, second adds only suffixes
#needed for this particular makefile.
.SUFFIXES:
.SUFFIXES: .c .o .cpp .hpp .s

#MACROS

__MKDIR ?= mkdir -p


#VARIABLES

#= is to recursively expand vars(any variables are expanded and those inside)
#:= simply expand only first level e.g var= $(vars) only expands vars once and
#none of those inside prevents infinite recursion Cflags = $(Cflags)
#?= assigns if not already, =+ appends to value of variable.
#****REMEMBER you can set vars at cli "make [target] FOO=bar" *****

#Remember to put all source files in SRC_DIR
TARGET_EXEC ?= test
BUILD_DIR ?= ./build
SRC_DIR ?= ./src

#makes list of source files of cpp, c and assembly (commented out)
C_SRC := $(shell find $(SRC_DIR) -name *.c)

CPP_SRC := $(shell find $(SRC_DIR) -name *.cpp)
ASMB_SRC := $(shell find $(SRC_DIR) -name *.s)
ALL_SRC_F := $(shell find $(SRC_DIR) -name *.s -or -name *.cpp -or -name *.c)


#makes list of object files in build dir (C only version commented out)
#OBJS := $(C_SRC:%=$(BUILD_DIR)/%.o)
OBJS := $(ALL_SRC_F:%=$(BUILD_DIR)/%.o)


#-D is macro define flag and g3 is highest debug inclusion level
DEBUG_FLAGS = -D DEBUG -g3
LFLAGS = 
#max optimization with pedantic (ISOC/C++ and stops forbidden extensions)
#and strict aliasing(pointers to same address warning)
CFLAGS =  -O3 -Wall -Wextra -Wpedantic -Wstrict-aliasing
CC = gcc -std=gnu11
CPP = g++ -std=c++11
#MMD(preprocessor flag)-Instead of outputting preprocessor result, generates a 
#rule for make describing dependencies of the main source file. MMD specifies 
#only user header files no system header files like -M. Generates as *.d file.
#Note: if -M is used the output file (*.cpp.o) will be a dependency file not an
#object file.
#MP(preprocessor flag)-adds phony target for each dependency other than main 
#file so each depend on nothing
CPPFLAGS ?= $(CFLAGS) -MMD -MP

#INCLUDES
LIB_FLAGS = #-l
#gets list of directory names in src directory
INC_DIRS :=$(shell find $(SRC_DIR) -type d)
#Adds the -I flag to the INC_DIRS list so var is not so nested and = is not need
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

#Necessary for cpp files. Takes preprocessor generated make rules and uses the
#include(adds makefile to this one) to add them to this makefile dynamically.
DEPS := $(OBJS:.o=.d)
-include $(DEPS)


#EXECUTABLE RULES
#remembr the .o file rule below will not compile if there isn't a call for it 
#in the prereqs of another rule. Same with all % pattern rules. Linking done
#here and the object files are put in src dir in build dir.

#links and puts target in build directory
$(BUILD_DIR)/$(TARGET_EXEC) : $(OBJS)
	$(CPP) $(OBJS) -o $@ $(LFLAGS)


#DEPENDENCY RULES

# Works by being called first as a dependency so mkdir macro
# will run pulling directory name/path from 'dir' command. Then by using $@ the
# path of the src file is included in the -o build flag retaining src structure.
# This path is also necessary for target build as we can use $^ or $(OBJS) which
# will include the path dynamically than statically if we were to rename the dir
# to 'objects' instead of src.

#C version
$(BUILD_DIR)/%.c.o : %.c
	$(__MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(LIB_FLAGS) -c $< -o $@

#assembly version
$(BUILD_DIR)/%.a.o : %.s
	$(__MKDIR) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

#cpp version
$(BUILD_DIR)/%.cpp.o : %.cpp
	$(__MKDIR) $(dir $@)
	$(CPP) $(CPPFLAGS) -c $< -o $@


#generic version

#Rule below compiles all .c files to .o files, -c compiles and does not link(ma
#kes .o files) -o for named file output
#$@ is target of rule (target is left of : and right is prereqs for that target
# % is pattern rule prereq (finds all matching following pattern), $<name of 
#first prereq, $^ names of all prereq with spaces between.

#%*.o : %*.c
#	$(CC) $< -o $@ $(CFLAGS)


#DUMMY RULES
#@ symbol is used at beginning of recipe to not print execution
clean:
	@rm -rf $(BUILD_DIR)



