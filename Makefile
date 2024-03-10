SYSTEMC = /opt/systemc
SYSTEMC_ARCH = linux64

LIB_DIR = $(SYSTEMC)/lib-$(SYSTEMC_ARCH)

INCLUDE_DIR = -I. -I$(SYSTEMC)/include

RUNTIME_LIB_DIR = $(SYSTEMC)/lib-$(SYSTEMC_ARCH)

HEADERS = fir.h tb.h

SOURCES = fir.cc tb.cc main.cc

DEPENDENCIES = Makefile $(HEADERS) $(SOURCES)

LIBS = -lsystemc -lstdc++ -lm

TESTS = main

all: $(TESTS)
	./$(TESTS)
	@make cmp_result

$(TESTS): $(DEPENDENCIES)
	g++ -o $@ $(SOURCES) $(INCLUDE_DIR) -L$(LIB_DIR) $(LIBS) -Wl,-rpath=$(RUNTIME_LIB_DIR)

clean:
	rm -f $(TESTS) output.dat

GOLD_DIR = ./golden
GOLD_FILE = $(GOLD_DIR)/ref_output.dat

cmp_result:
	@echo "********************************************"
	@if diff -w $(GOLD_FILE) output.dat; then \
		echo "Simulation PASSED"; \
	else \
		echo "Simulation FAILED"; \
	fi
	@echo "********************************************"