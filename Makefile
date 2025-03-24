CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS = -lX11
SRC = src/mowm.c
OUT = mowm
DISPLAY1 = DISPLAY=:1
KILL = pkill Xephyr || true;

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)

stop:
	$(KILL)

run-xsession: $(OUT)
	$(KILL) \
	DISPLAY=:0 Xephyr -ac -br -noreset -screen 800x600 :1 & \
	sleep 1 && $(DISPLAY1) ./$(OUT)

run-tty: $(OUT)
	$(KILL) \
	startx ./$(OUT) -- :1
