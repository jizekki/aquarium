CC = gcc
CFLAGS   = -Wall -Wextra
LIBS = -pthread
SRC_PATH = src/
TEST_PATH = tst/
BUILD_PATH = build/

BIN = server fake_client test_aquarium test_fish test_frame test_utils test_view

.PHONY: all
all: $(BIN)

server: server.o frame.o connection.o view.o command.o config.o utils.o fish.o aquarium.o
	$(CC) -o server $(BUILD_PATH)server.o $(BUILD_PATH)connection.o $(BUILD_PATH)frame.o $(BUILD_PATH)command.o $(BUILD_PATH)view.o $(BUILD_PATH)config.o $(BUILD_PATH)utils.o $(BUILD_PATH)fish.o $(BUILD_PATH)aquarium.o $(LIBS)

%.o: $(SRC_PATH)%.c $(SRC_PATH)%.h build
	$(CC) -o $(BUILD_PATH)$@ -c $< $(CFLAGS)

build:
	mkdir $(BUILD_PATH)

fake_client: fake_client.o 
	$(CC) -o fake_client $(BUILD_PATH)fake_client.o $(CFLAGS)

%.o: $(TEST_PATH)%.c build
	$(CC) -o $(BUILD_PATH)$@ -c $< $(CFLAGS)

test_aquarium: test_aquarium.o aquarium.o frame.o view.o fish.o test.o
	$(CC) -o test_aquarium $(BUILD_PATH)test_aquarium.o  $(BUILD_PATH)aquarium.o $(BUILD_PATH)frame.o $(BUILD_PATH)view.o $(BUILD_PATH)fish.o $(BUILD_PATH)test.o $(CFLAGS)

test_fish: test_fish.o fish.o frame.o test.o
	$(CC) -o test_fish $(BUILD_PATH)test_fish.o $(BUILD_PATH)frame.o $(BUILD_PATH)fish.o $(BUILD_PATH)test.o $(CFLAGS)

test_frame: test_frame.o frame.o test.o
	$(CC) -o test_frame $(BUILD_PATH)test_frame.o $(BUILD_PATH)frame.o $(BUILD_PATH)test.o $(CFLAGS)

test_utils: test_utils.o utils.o test.o
	$(CC) -o test_utils $(BUILD_PATH)test_utils.o $(BUILD_PATH)utils.o $(BUILD_PATH)test.o $(CFLAGS)

test_view: test_view.o view.o test.o
	$(CC) -o test_view $(BUILD_PATH)test_view.o $(BUILD_PATH)view.o $(BUILD_PATH)test.o $(CFLAGS)

test: test_view test_utils test_frame test_fish test_aquarium
	./test_utils
	./test_frame
	./test_fish
	./test_view
	./test_aquarium

launch_server: clean server
	./server 2> debug.log

launch_fake_client: fake_client
	./fake_client

clean:
	$(RM) *.o *~ $(BIN) $(BUILD_PATH)*
