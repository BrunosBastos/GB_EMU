import socket
import select
import sys

HOST = "127.0.0.1"
PORT = 9000

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        print(f"[INFO] Connecting to emulator at {HOST}:{PORT}...")
        s.connect((HOST, PORT))
        print("[INFO] Connected! Waiting for messages...\n")

        while True:
            # wait for either socket or stdin input
            ready, _, _ = select.select([s, sys.stdin], [], [])

            for r in ready:
                if r == s:
                    data = s.recv(1024)
                    if not data:
                        print("[INFO] Connection closed by server.")
                        return
                    print(data.decode(errors="replace"), end="")
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

if __name__ == "__main__":
    main()