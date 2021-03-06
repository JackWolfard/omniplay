CC := gcc

CFLAGS :=  -g
LDFLAGS := -Wall -Werror -g 

#LDLIBS := libutil.a

KERN_CONFIG := replay_headers/include/linux/replay_configs.h

DEPS_DIR := .deps

TARGETS=parseklog parseulog parsemlog launcher resume parseckpt \
	getstats filemap replay_pause reset_ndx currentpid seqtt partt fulltt fullsend streamtt streamctl sync_files read_trace retaint mkpartition mkpart_iter launch_pin

# For automatic .h dependency tracking... may not work perfectly for launcher as
#    the include path changes for it
CFILES=$(wildcard *.c)
DEPS=$(patsubst %.c, .deps/%.d, $(CFILES))

.PHONY: all
all: $(TARGETS)

# Build dependencies + any extra flags

launcher: libutil.a
launcher: CFLAGS += --static -I../../eglibc-2.15/prefix/include -L../../eglibc-2.15/prefix/lib 

resume: resume.cpp libutil.a
	c++ -std=c++0x resume.cpp libutil.a -o resume -pthread --static

getstats: libutil.a

filemap: libutil.a 

parseklog: parseklib.o

rewriteklog: parseklib.o

libutil.a: util.o parseklib.o
	ar rv $@ $^
	ranlib $@

parseklib.o: $(KENREL_CONFIG)

reset_ndx: libutil.a

currentpid: libutil.a

seqtt: libutil.a 
seqtt: LDLIBS += -lrt 

launch_pin: libutil.a 
launch_pin: LDLIBS += -lrt 

partt: libutil.a
partt: LDFLAGS += -pthread


thread_test: LDFLAGS += -pthread 



streamtt: libutil.a streamtt.cpp 
	c++ -std=c++0x streamtt.cpp libutil.a -pthread -lrt -o streamtt -Wall -Werror

streamctl: streamctl.cpp streamserver.h parseklib.o streamnw.cpp streamnw.h
	c++ -Wall -Werror -std=c++0x streamctl.cpp streamnw.cpp parseklib.o -o streamctl -g

retaint: retaint_test.cpp libutil.a
	c++ -Wall -Werror -std=c++0x retaint_test.cpp parseklib.o libutil.a -o retaint -g


fulltt: libutil.a

fullsend: libutil.a

read_trace: read_trace.cpp
	c++ -Wall -Werror  -std=c++0x read_trace.cpp -lrt -o read_trace -g

mkpartition: libutil.a mkpartition.cpp 
	c++ -Wall -Werror -std=c++0x mkpartition.cpp libutil.a -pthread -lrt -o mkpartition -O8 

mkpartition_utils.o: mkpartition_utils.cpp mkpartition_utils.h
	c++ -std=c++0x mkpartition_utils.cpp -o mkpartition_utils.o -c -O8

mkpart_iter: mkpartition_utils.o libutil.a generate_splits.cpp mkpartition_iter.cpp
	c++ -std=c++0x mkpartition_utils.o libutil.a generate_splits.cpp mkpartition_iter.cpp -o mkpart_iter -O8

sync_files: sync_files.cpp streamserver.h parseklib.o streamnw.cpp streamnw.h
	c++ -Wall -Werror -std=c++0x sync_files.cpp parseklib.o streamnw.cpp -o sync_files 

.PHONY: clean
clean:
	rm -f *.a *.o $(TARGETS)

.deps/%.d: %.c .dep_dirs_made
	@$(CC) $(CFLAGS) -M -o $@ $<

.dep_dirs_made:
	@touch .dep_dirs_made
	@mkdir .deps

-include $(DEPS)

.PHONY: nuke
nuke: clean
	rm -rf .deps .dep_dirs_made

