CC = gcc
CFLAGS = -O2
LIBS = -lm

LIB_SRCS = BasicOperation.c Add_Sub.c Mul.c Div.c Squ.c exp.c
LIB_OBJS = $(LIB_SRCS:.c=.o)
LIBRARY = libntro.a
LIBRARY_EXECUTABLE = ntro

CAL_SRC = cal.c
CAL_OBJ = $(CAL_SRC:.c=.o)
CAL_EXECUTABLE = cal

VERI_SRC = verify.c
VERI_OBJ = $(VERI_SRC:.c=.o)
VERI_EXECUTABLE = verify

TEST_SRC = test.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_EXECUTABLE = test

.PHONY: all clean

all: $(LIBRARY) $(CAL_EXECUTABLE) $(VERI_EXECUTABLE) $(TEST_EXECUTABLE)

ntro : $(LIBRARY)

$(LIBRARY): $(LIB_OBJS)
	ar rcs $@ $^

$(CAL_EXECUTABLE): $(CAL_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(VERI_EXECUTABLE): $(VERI_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(TEST_EXECUTABLE): $(TEST_OBJ) $(LIB_SRCS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(LIB_OBJS) $(LIBRARY) $(TEST_OBJ) $(TEST_EXECUTABLE) $(CAL_OBJ) $(CAL_EXECUTABLE) $(VERI_OBJ) $(VERI_EXECUTABLE)
