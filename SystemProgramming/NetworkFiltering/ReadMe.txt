ReadMe

mybasic.ko: mybasic을 컴파일한 모듈 파일, insmod 명령어로 해당 모듈을 커널에 올릴 수 있다. 

mybasic.c: 모듈 소스 파일. 후크 포인터에 후크 함수들을 register한다. 후크 함수들과 다음의 함수들이 포함되어 있다. 
- custom_write()
- isStringToNumber(): x.x.x.x 형태의 string으로 된 ip주소를 int 타입으로 바꿔준다. 
- my_module_init(), my_module_exit(): 모듈을 올리고 내릴 때 불리는 함수. 

main: 서버와 통신하는 클라이언트를 구현한 코드

log.csv: 각 후크 포인터에서 hook으로 캡처한 패킷들을 로그로 만든 파일. main실행 후 ctrl+c 를 통해 main을 중지시키고 터미널에 dmesg를 입력하면 볼 수 있는 내용이다. 
