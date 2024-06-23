import socket
import threading

class UDPClient:
    def __init__(self, local_ip, server_ip, receive_port, send_port):
        self.local_ip = local_ip
        self.server_ip = server_ip
        self.receive_port = receive_port
        self.send_port = send_port
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        self.receive_callback = None
        self.receive_thread = threading.Thread(target=self.receive_loop)
        self.receive_thread.daemon = True
        self.receive_thread.start()

        self.client_socket.bind((self.local_ip, self.receive_port))  # 수신할 포트 설정

    def set_receive_callback(self, callback):
        self.receive_callback = callback

    def receive_loop(self):
        while True:
            data, addr = self.client_socket.recvfrom(1024)
            if self.receive_callback:
                command, data = self.parse_message(data.decode())
                self.receive_callback(command, data, addr)

    def send_message(self, command, data):
        # Ensure command is exactly 4 characters long, trim if it's longer
        if len(command) > 4:
            print("Command is longer than 4 characters. Trimming to 4 characters.")
            command = command[:4]
        command = command.ljust(4)
        message = command + data
        self.client_socket.sendto(message.encode(), (self.server_ip, self.send_port))

    def parse_message(self, message):
        command = message[:4]
        data = message[4:]
        return command, data

    def close(self):
        self.client_socket.close()

# 테스트용 예제
if __name__ == "__main__":
    def on_receive_callback(command, data, addr):
        print(f"Received message from {addr}: Command: {command}, Data: {data}")

    local_ip = '127.0.0.1'  # 수신할 IP
    server_ip = '127.0.0.1'  # 보낼 IP
    receive_port = 5003  # 수신할 포트
    send_port = 5002  # 보낼 포트

    client = UDPClient(local_ip, server_ip, receive_port, send_port)
    client.set_receive_callback(on_receive_callback)

    while True:
        command = input("Enter command (up to 4 characters): ")
        data = input("Enter data: ")
        client.send_message(command, data)
