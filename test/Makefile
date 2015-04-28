CFLAGS = -Wall -g
TERR_TEST_OBJS = terr_t1.o
TERR = terr
TERR_SRC_PATH = $(abspath ../src)

$(TERR):$(TERR_TEST_OBJS)
	cd $(TERR_SRC_PATH) && $(MAKE)
	$(CC) *.o -o $@ -lterr -L../

$(TERR_TEST_OBJS):%.o:%.c
		$(CC) -c $(CFLAGS) $< -o $@

.PHONY : clean
clean :
	cd $(TERR_SRC_PATH) && $(MAKE) clean
	-rm  $(TERR_TEST_OBJS) $(TERR)
