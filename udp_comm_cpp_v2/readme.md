project/
├── include/
│   ├── UdpComm.hpp
│   ├── CustomUdpComm.hpp
├── src/
│   ├── UdpComm.cpp
│   ├── CustomUdpComm.cpp
│   ├── main.cpp
│   ├── another_file.cpp
├── Makefile

# 실행 방법

	1.	터미널을 열고 프로젝트 디렉터리로 이동합니다.
	2.	make 명령어를 실행하여 프로젝트를 빌드합니다.
	3.	./udp_comm_app 명령어를 실행하여 프로그램을 시작합니다.

이제 main.cpp에서 CustomUdpComm 객체를 포인터로 선언하고 다른 파일인 another_file.cpp에서 extern 키워드를 사용하여 이를 참조할 수 있습니다. some_function에서 udp_comm 객체의 send_data 메서드를 호출하여 데이터를 보낼 수 있습니다.
