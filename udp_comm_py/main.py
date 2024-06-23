from udp_client import UDPClient

def on_receive_callback(command, data, addr):
    print(f"Received message from {addr}: Command: {command}, Data: {data}")

if __name__ == "__main__":
    local_ip = '127.0.0.1'  # 수신할 IP
    server_ip = '192.168.1.100'  # 보낼 IP
    receive_port = 5003  # 수신할 포트
    send_port = 5002  # 보낼 포트

    client = UDPClient(local_ip, server_ip, receive_port, send_port)
    client.set_receive_callback(on_receive_callback)

    while True:
        command = input("Enter command (4 characters): ")
        data = input("Enter data: ")
        client.send_message(command, data)
