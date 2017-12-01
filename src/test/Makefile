DEPS_DIR = ../../dependencies

GTEST_DIR = $(DEPS_DIR)/googletest

SRC_DIR = ..

.PHONY: all clean test chrome-open-coverage

#TESTS = File

SPECS = $(addsuffix _spec,$(TESTS))

all: gtest_main.a $(SPECS)

clean:
	rm -f $(addsuffix .o,$(TESTS)) $(addsuffix .o,$(SPECS)) $(SPECS) *.gc* *.info

clear: clean
	rm -f gtest* It.o -R coverage

GTEST_INCLUDE = $(GTEST_DIR)/include

CPPFLAGS += -isystem $(GTEST_INCLUDE)

CXXBASEFLAGS = -g -std=c++14 -Wall -Wextra -Wpedantic -O -O0

CXXFLAGS += $(CXXBASEFLAGS) -pthread

COVER = --coverage

GTEST_HEADERS = $(GTEST_INCLUDE)/gtest/*.h $(GTEST_INCLUDE)/gtest/internal/*.h

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

COMPILER = $(CXX) $(CPPFLAGS) $(CXXFLAGS)

COMPILE_GTEST = $(COMPILER) -I$(GTEST_DIR) -c $(GTEST_DIR)/src

AR_GTEST = $(AR) $(ARFLAGS) $@ $^

LCOV_CURR_DIR = lcov --base-directory . --directory .

COMPILE_COMPONENT = $(COMPILER) -c $(SRC_DIR)

objDeps = $(1).o $(1)_spec.o

dirDeps = $(SRC_DIR)/$(1)/$(2)/$(2).h $(SRC_DIR)/$(1)/$(2)/$(2).cc $(SRC_DIR)/$(1)/$(2)/$(2)_spec.cc

define endl


endef

define spec
$(2).o: $(call dirDeps,$(1),$(2))
	$(COMPILE_COMPONENT)/$(1)/$(2)/$(2).cc $(COVER)

$(2)_spec.o: $(2).o
	$(COMPILE_COMPONENT)/$(1)/$(2)/$(2)_spec.cc

$(2)_spec: $(call objDeps,$(2)) gtest_main.a It.o $(3)
	$(COMPILER) $(COVER) -lpthread $$^ -o $$@
endef

gtest-all.o: $(GTEST_SRCS_)
	$(COMPILE_GTEST)/gtest-all.cc

gtest_main.o: $(GTEST_SRCS_)
	$(COMPILE_GTEST)/gtest_main.cc

gtest.a: gtest-all.o
	$(AR_GTEST)

gtest_main.a: gtest-all.o gtest_main.o
	$(AR_GTEST)

It.o: ./It/It.h ./It/It.cc
	$(COMPILER) -c ./It/It.cc

#$(eval $(call spec,.,File)

run: all
	$(foreach spec,$(SPECS),./$(spec) --gtest_color=yes$(endl))

cover: all
	$(LCOV_CURR_DIR) --zerocounters
	$(foreach spec,$(SPECS),./$(spec) --gtest_color=yes$(endl))
	$(LCOV_CURR_DIR) --capture -o test.info
	lcov --remove test.info "/*/include/*" -o spec.info
	genhtml spec.info --highlight --legend --demangle-cpp -o coverage

chrome-open-coverage: clean
	google-chrome coverage/index.html
