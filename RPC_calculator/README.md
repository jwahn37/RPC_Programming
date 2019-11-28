Parallel/Distributed Computing Assignment #2

1. RPC Programming (20 Points)



1. Compile

-idl파일을 통해 RPC를 위한 소스코드를 생성한다.
$sh RPC_idl_compile.sh calculator.x

-생성된 소스코드를 컴파일한다.
$make

2. Run

-Server 실행하기
$./calculator_server

-Client 실행하기
$./calculator_client $(SERVER_IP)

$(SERVER_IP): localhost, cspro5, ...