
2018학년도 1학기 논리설계 과제
made by. Euncho Bae

논리설계 프로젝트
 1. Mid Project 
 2. Final Project

-----------------------------------------------------------------------
Mid Project

목표: 4 bit adder/subtractor을 설계하고 주어진 testbench를 이용해 검증하시오.

설계 내용:
 - 수업시간에 배운 adder/subtractor 회로도를 참고해 input 신호 M에 따라 adder 또는 subtractor로 동작하는 회로를 구성한다.
 - addends는 모두 4bit이며 결과값은 4-bit sum과 carry out으로 나타낸다.
 - output에 overflow 발생 여부를 표시하시오
 - half adder, full adder를 먼저 구현하고, 이를 이용해 adder/subtractor를 설계하라.

파일 구성:
 1) mid_report.docx: 설계도, 설계 과정 및 결과
 2) addsub.v
 3) full_adder.v
 4) half_adder.v

-----------------------------------------------------------------------
Final Project

목표: vending machine을 state 기반의 sequential circuit으로 설계하고 제공된 testbench를 사용해 검증하시오.

설계 내용:
 - 구매할 음료의 종류 지정
 - clock 의 posedge 마다 coin을 insert
 - 음료수 가격 이상의 coin을 넣으면 다음 clock에서 음료수 배출
   * COKE: 300원
   * SPRITE: 250원

파일 설명:
 1) final_report.docx: 프로젝트를 위한 state 설정과 state diagram 설명
 2) vending_machine.txt: vending_machine.v 의 txt 파일
 3) vending_machine.v: 베릴로그 코드

