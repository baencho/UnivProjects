segbuf.c
 경로: home/nyam/linux(커널 소스파일 디렉토리)/fs/nilfs2/segbuf.c
 설명:  Nilfs2에서 submit_bio를 호출하는 함수는 nilfs_segbuf_submit_bio()로 segbuf.c 파일에 정의되어있다. 이 nilfs_segbuf_submit_bio() 함수에서 bi_bdev내의 super_block 구조체인 bd_super에  인자로 받은 segbuf (nilfs_segment_buffer 구조체)에 들어있는 super_bd(super_block구조체)를 넣어주었다.

blk-core.c
 경로: home/nyam/linux(커널 소스파일 디렉토리)/block/blk-core.c
 설명: 
	line 40에 시간을 받아오기 위해 <linux/time.h> 헤더를 포함시켰다.
	line 52에 queue를 구현했다. 그리고 queue를 export해서 모듈에서 사용할 수 있게 하였다
	line 2213- submit_bio 함수 안 time, sector번호, system이름을 받아 que에 저장하였다.


mybasic.c
 경로: ~/Downloads/euncho
 설명: 모듈을 구현한 파일이다. 안에 custom_write이라는 함수를 구현하여 원하는 정보를 로그에 출력하게 하였다. 

mybasic.ko
 경로: ~/Downloads/euncho
 설명: mybasic.c 와 Makefile로 컴파일한 모듈 파일

Makefile
 경로: ~/Downloads/euncho
 설명: KDIR에 커널 소스 경로를 저장하여 mybasic.c를 컴파일 하는데 쓰인다.
