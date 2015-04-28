CFLAGS = -Wall -g
TERR_OBJS = terr.o terr_file.o terr_line.o
TERR_LIB = libterr.a
$(TERR_LIB):$(TERR_OBJS)
	 ar -r ../$@ $(TERR_OBJS)

$(TERR_OBJS):%.o:%.c %.h
		$(CC) -c $(CFLAGS) $< -o $@

.PHONY : clean
clean :
	-rm  $(TERR_OBJS) ../$(TERR_LIB)
