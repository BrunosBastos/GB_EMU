import socket
import select
import sys

HOST = "127.0.0.1"
PORT = 9000

DEBUG_ADDR = "DEF6"
LAST_OP = None
CURR_OP = None
DETECTED = False

def main():
    level = 0
    if len(sys.argv) > 1:
        level = int(sys.argv[1])

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        print(f"[INFO] Connecting to emulator at {HOST}:{PORT}...")
        s.connect((HOST, PORT))
        print("[INFO] Connected! Waiting for messages...\n")

        # s.sendall(str(level).encode("utf-8"))

        while True:
            # wait for either socket or stdin input
            ready, _, _ = select.select([s, sys.stdin], [], [])

            for r in ready:
                if r == s:
                    buffer = ""
                    while True:
                        data = s.recv(1024)
                        if not data:
                            return
                        buffer += data.decode(errors="replace")
                        while "\n" in buffer:
                            line, buffer = buffer.split("\n", 1)
                            handle(line)
                elif r == sys.stdin:
                    inp = sys.stdin.readline().strip()
                    if inp.lower() == "quit":
                        print("[INFO] Exiting...")
                        return
                    if inp.isdigit() and 0 <= int(inp) <= 3:
                        msg = f"[LEVEL]={inp}\n"
                        s.sendall(msg.encode("utf-8"))
                        print(f"[INFO] Sent: {msg}")
                    else:
                        print("[WARN] Invalid level, must be 0-3")


def handle(msg):
    global LAST_OP, CURR_OP, DEBUG_ADDR, DETECTED
    if msg.startswith("[MEM_WRITE]"):
        content = msg[len("[MEM_WRITE]"):].strip()
        parts = content.split(":")
        print(parts)
        if parts[0].strip() == DEBUG_ADDR:
            print(parts)
            DETECTED = True
    else:
        if CURR_OP is not None:
            LAST_OP = CURR_OP
        CURR_OP = msg
        if DETECTED:
            print(LAST_OP, CURR_OP)
            exit()

if __name__ == "__main__":
    main()