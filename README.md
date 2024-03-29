# 2018_2_GDP
OpenGL로 만든 슈팅게임 

## 게임구성
게임은 총 2개의 스테이지로 구성되어 있다.  
1.	몬스터들을 피하며 총을 발사해 20마리 처치하기  
2.	중앙에 설치된 포대에서 나오는 레이저를 피하며 몬스터 40마리 처치하기  

## 게임진행을 위해 추가구현 한 기능
1.	게임 진행시간과 잡은 몬스터 수를 나타내기 위한 Number클래스
2.	이동, 공격 등의 기능을 위한 마우스클릭, KeyPush이벤트
3.	공격, 진행 시 출력될 소리에 대한 Sound클래스
4.	몬스터 랜덤생성, 캐릭터 추격을 위한 산술적 연산 및 이동
5.	소멸된 총알, 몬스터의 메모리 누수를 방지하기 위한 해결책

### 1. 게임 진행시간과 잡은 몬스터 수를 나타내기 위한 Number클래스
숫자를 그리기 위해서 필요한 정보는 선의 색상, 그리기 위한 좌표, 그리고자 하는 숫자, 크기조절 변수  
> Number.h 내의 drawNumber함수 참조

너비 0.25f, 높이 0,4f의 크기로 그리도록 구현하였으며 크기조절 변수를 통해 0.5배, 2배 등으로 사이즈를 조절가능 하도록 구현하였다. 또한 게임 중 눈에 잘 보이도록 하기 위해 선의 굵기는 10.0f로 고정하였다.  

### 2. 이동, 공격 등의 기능을 위한 마우스클릭, KeyPush이벤트
조작방법은 wasd를 이용한 상하좌우 이동, 캐릭터 기준 상하좌우를 클릭하면 그 방향으로 총을 발사한다.  
> GameExample.h헤더의 Game클래스(400번 줄)을 참조

마우스 클릭시 Bullet을 하나 동적할당하여 총알의 위치를 출력하기 위한 정보를 저장한다. 또한 캐릭터의 위치가 화면밖을 나가는 경우를 고려하여 이동연산을 구현하였다.  

### 3. 공격, 진행 시 출력될 소리에 대한 Sound클래스
소리가 출력되는 경우는 다음과 같다.  

1.	배경음악  
2.	공격
3.	몬스터 처치
4.	게임종료
5.	스킬 사용

> Sound.h헤더의 Sound클래스를 참조

Sound클래스는 check함수와 play함수가 있으며 각각 설정, 재생 파트를 맞고 있다. 반복여부는 배경음악만 반복하도록 설정을 하였으며 나머지 소리들은 이벤트 발생시에 play를 실행해 소리가 재생 되도록 설정하였다.  

### 4. 몬스터 랜덤생성, 캐릭터 추격을 위한 산술적 연산 및 이동
5초 간격으로 생성되는 몬스터들은 항상 캐릭터의 방향을 바라보고 캐릭터를 향해 전진해야 한다.  
GameExample.h의 Monser클래스(75번 줄)을 참조  
이미 알고있는 정보는 현재 캐릭터의 위치와 몬스터의 위치이기 때문에 선택한 방법은 x의 양의방향으로 몬스터를 그린 뒤 캐릭터와 몬스터의 좌표를 잇는 선의 기울기를 구한 뒤 기울기에 해당한 각도만큼 회전하는 방법을 선택하였다.  
캐릭터 추격은 기울기를 통해 캐릭터의 방향을 알았으니 바라보는 방향으로 단위백터를 구한 뒤 시간 간격만큼 위치를 이동해 줌으로 이동을 구현하였다.  

### 5. 소멸된 총알, 몬스터의 메모리 누수를 방지하기 위한 해결책
동적할당이 되는 객체는 총알과 몬스터 뿐이다. 총알은 화면범위를 나가거나 몬스터와의 충돌 시 소멸이 되어야 하고 몬스터는 총알과 충돌 시 소멸이 되어야 한다.
> 충돌 판정과 동적할당 및 delete연산은 GameExample.h의 랜더링부분 (542번 줄)을 참조
  
매 총알 마다 위치를 체크해 총알의 위치가 화면밖을 나갔을 경우 할당을 해제, nullptr로 바꾸어 줌으로 총알소멸을 구현하였고, 몬스터는 총알과 충돌하였을 때(몬스터와 총알의 거리가 일정 거리 미만이 되었을 때)에 총알과 몬스터를 할당해제 시킴으로 기능을 구현하였다.
