#include "GameExample.h"
#include <conio.h>

using namespace std;

int main(){
	int input = 0;
	std::cout << "=======================================================================================\n" << std::endl;
	std::cout << ">> 홍정모 교수님 게임 만들기 연습문제 - 중간평가" << std::endl;
	std::cout << ">> 조작법\tW - 위로 이동 A - 왼쪽으로 이동 S - 아래로 이동 D - 오른쪽으로 이동" << std::endl;
	std::cout << "\t\t마우스 왼쪽 클릭 - 총알 발사" << std::endl;
	std::cout << "\n>> 게임시작 : 'G'키  스킬사용 : 'C'키" << std::endl;
	std::cout << ">> 콘솔 종료 : 'E'키\n" << std::endl;
	std::cout << ">> 게임을 종료하시려면 오른쪽위에 있는 'E'버튼을 누르세요" << std::endl;
	std::cout << "\n=======================================================================================" << std::endl;
	while (true) {//'E'나 'G'를 입력할 때 까지 반복
		input = getch();
		if (input == 69 || input == 101) {
			std::cout << "\n>> 콘솔을 종료합니다.\n" << std::endl;
			std::cout << "=======================================================================================\n" << std::endl;
			return 0;
		}
		else if (input == 103 || input == 71)
			break;
	}
	jm::Game().run();
	return 0;
}