#pragma once

#include "Game2D.h"
#include "Sound.h"
#include "Number.h"
#include "Timer.h"

#define MAX_BULLET 5
#define MAX_MONSTER 10

namespace jm
{

	float get_direction(const vec2& point) {
		//���� ���� �� ���� ó��
		//0.0 ������ 1.0 ���� 2.0 ���� 3.0 �Ʒ���
		if (point.x >= 0.0f&&point.y == 0.0f)
			return 0.0f;
		else if (point.x == 0.0f&&point.y > 0.0f)
			return 1.0f;
		else if (point.x < 0.0f&&point.y == 0.0f)
			return 2.0f;
		else if (point.x == 0.0f&&point.y < 0.0f)
			return 3.0f;

		float gradient = point.y / point.x;
		//���� ���� ���� ����ó��
		if (point.x >= 0.0f && (gradient >= -1.0f&&gradient <= 1.0f))
			return 0.0f;
		else if (point.y >= 0.0f && (gradient > 1.0f || gradient < -1.0f))
			return 1.0f;
		else if (point.x <= 0.0f && (gradient >= -1.0f&&gradient <= 1.0f))
			return 2.0f;
		else if (point.y <= 0.0f && (gradient > 1.0f || gradient < -1.0f))
			return 3.0f;
	}

	class Character//ĳ���� Ŭ����
	{
	public:
		float direction = 0.0f;//0,1,2,3������ ������ ���� ���� �Ʒ���
								//0.5�� 45�� ȸ��
		RGB color = Colors::gold;//�Ӹ� ����
		vec2 center = vec2(0.0f, 0.0f);//ĳ���� ��ġ

		void draw() {//ĳ���� �׸��� �Լ�
			//��
			beginTransformation();
			{
				translate(center);//ĳ���� ��ġ ��������
				rotate(direction*90.0);//����������
				translate(0.08f, 0.0f);//����ġ�� �ű��
				drawFilledBox(Colors::black, 0.07f, 0.03f);//�ѱ��� �׸���
			}
			endTransformation();

			//�Ӹ�
			beginTransformation();
			{
				translate(center);//ĳ���� ��ġ ��������
				setLineWidth(2.5f);
				drawFilledCircle(color, 0.06f);//�Ӹ��� �׸���
				drawWiredCircle(Colors::black, 0.06f);//������ ��ĥ�Ѵ�
			}
			endTransformation();
		}

		bool crush(vec2& point) {//�浹 �Լ�
			if ((point - center).distance() <= 0.12f)
				return true;//�浹 �ߴ�
			return false;//�浹 ���ߴ�
		}
	};

	class Monster
	{
	public:
		vec2 center = vec2(1.0f, 0.0f);
		vec2 velocity = vec2(1.0f, 0.0f);

		void draw(vec2& point) {//�׸� �� �ٶ󺸴� ���⿡ ���� ���Ͱ��� ����
			beginTransformation();
			{
				//�����̸��� gradient������ �����δ� ����(���� �ƴ�)�� ��Ÿ��
				float gradient = 180.0f / 3.14159f * atan((point.y - center.y) / (point.x - center.x));
				if ((point.x - center.x) < 0)//�а��̸� + 180��
					gradient += 180.0f;
				translate(center);
				rotate(gradient);//�ٶ󺸴� ������ŭ ȸ��
				translate(0.07f, 0.04f);
				drawFilledBox(Colors::black, 0.06f, 0.04f);
				translate(0.0f, -0.08f);
				drawFilledBox(Colors::black, 0.06f, 0.04f);
			}
			endTransformation();

			beginTransformation();
			{
				translate(center);
				setLineWidth(2.5f);
				drawFilledCircle(Colors::monster, 0.06f);
				drawWiredCircle(Colors::black, 0.06f);
			}
			endTransformation();
		}

		bool crush(vec2& point) {//�浹 �Լ�
			if ((point - center).distance() <= 0.06f)
				return true;//�浹 �ߴ�
			return false;//�浹 ���ߴ�
		}

		void update(const float& dt, vec2& point)//��ġ�ű��
		{
			//�ӵ��� �ٶ󺸴� ������ ��������(�ӵ��� ���� 1.0f,1.0f)�� 1/20��
			velocity = vec2((point.x - center.x) / (point - center).distance() / 20, (point.y - center.y) / (point - center).distance() / 20);
			center += velocity * dt;
		}
	};

	class Turret {
	public:
		vec2 center = vec2(0.0f, 0.0f);
		int charge = 0;
		RGB color = Colors::monster;
		float direction = 0.0f;

		//�׸��� �Լ�
		void draw(Timer& timer,vec2& point) {
			//��ž�� ��8���� �ֱ⸦ ������
			charge = ((int)timer.stopAndGetElapsedMilli() / 1000) % 8;
			switch (charge)
			{
			case 1://��� 1 �����
				color = Colors::yellow;
				break;
			case 2://��� 2 �ϴû�
				color = Colors::skyblue;
				break;
			case 3://��� 3 �Ķ���
				color = Colors::blue;
				break;
			case 4://�߻� 4 ������
			case 5:
				color = Colors::red;
				break;
			default://���� ���ͻ�
				color = Colors::monster;
				//�ٶ󺸴� ������ point����
				direction = get_direction(point);
				break;
			}
			if (charge == 4) {//�߻���¸� �������׸���
				beginTransformation();
				{
					setLineWidth(2.5f);
					rotate(90.0f*direction);
					drawFilledTriangle(Colors::yellow, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f), vec2(1.0f, -1.0f));
					drawLine(Colors::black, vec2(0.0f, 0.0f), Colors::black, vec2(1.0f, 1.0f));
					drawLine(Colors::black, vec2(0.0f, 0.0f), Colors::black, vec2(1.0f, -1.0f));
				}
				endTransformation();
			}
			//�Ӹ�
			beginTransformation();
			{
				translate(center);
				setLineWidth(2.5f);
				drawFilledCircle(color, 0.06f);
				drawWiredCircle(Colors::black, 0.06f);
			}
			endTransformation();

			//��
			beginTransformation();
			{
				translate(center);
				rotate(90.0f*direction);
				translate(0.06f, 0.0f);
				drawFilledBox(Colors::black, 0.07f, 0.04f);
			}
			endTransformation();
		}

		bool crush(vec2& point) {
			if (point.distance() <= 0.12f || (charge == 4 && get_direction(point) == direction))
				return true;
			return false;
		}
	};

	class Bullet//�Ѿ� Ŭ����
	{
	public:
		float direction = 0.0f;//0,1,2,3������ ������ ���� ���� �Ʒ���
								//0.5�� 45�� ȸ��
		vec2 center = vec2(0.0f, 0.0f);//�Ѿ� ��ġ
		vec2 velocity = vec2(0.0f, 0.0f);//�Ѿ� �ӵ�

		void draw()//�Ѿ� �׸���
		{
			beginTransformation();
			translate(center);
			rotate(direction*90.0);
			translate(0.1f, 0.0f);
			drawFilledRegularConvexPolygon(Colors::yellow, 0.02f, 8);
			drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8);
			endTransformation();
		}

		void update(const float& dt)//��ġ �ű��
		{
			center += velocity * dt;
		}
	};

	class Interface {//��� �������̽��Լ�
	private:
		vec2 center = vec2(0.0f, 0.875f);

	public:
		bool sound_on = true;//�Ҹ���� bool����
		bool skill_on = true;

		void draw_Interface(Timer& timer,int count) {
			int num_tmp = 0;
			beginTransformation();//���
			{
				setLineWidth(2.5f);
				translate(center);
				drawFilledBox(Colors::silver, 2.0f, 0.25f);
				drawWiredBox(Colors::black, 2.0f, 0.25f);
			}
			endTransformation();

			beginTransformation();//�ð� �ڽ�
			{
				setLineWidth(2.5f);
				translate(center - vec2(0.75f, 0.0f));
				drawFilledBox(Colors::white, 0.48f, 0.2f);
				drawWiredBox(Colors::black, 0.48f, 0.2f);
			}
			endTransformation();

			beginTransformation();//�ð�
			{
				num_tmp = (int)timer.stopAndGetElapsedMilli() / 1000;
				drawNumber(Colors::black, vec2(-0.6f, 0.875f), num_tmp % 10, 0.4f, 0.4f);
				num_tmp /= 10;
				drawNumber(Colors::black, vec2(-0.75f, 0.875f), num_tmp % 10, 0.4f, 0.4f);
				num_tmp /= 10;
				drawNumber(Colors::black, vec2(-0.9f, 0.875f), num_tmp % 10, 0.4f, 0.4f);
			}
			endTransformation();

			beginTransformation();//ī��Ʈ �ڽ�
			{
				setLineWidth(2.5f);
				translate(center - vec2(0.25f, 0.0f));
				drawFilledBox(Colors::yellow, 0.48f, 0.2f);
				drawWiredBox(Colors::black, 0.48f, 0.2f);
			}
			endTransformation();

			beginTransformation();//ī��Ʈ
			{
				drawNumber(Colors::black, vec2(-0.1f, 0.875f), count % 10, 0.4f, 0.4f);
				count /= 10;
				drawNumber(Colors::black, vec2(-0.25f, 0.875f), count % 10, 0.4f, 0.4f);
				count /= 10;
				drawNumber(Colors::black, vec2(-0.4f, 0.875f), count % 10, 0.4f, 0.4f);
			}
			endTransformation();

			beginTransformation(); {
				setLineWidth(2.5f);
				translate(center + vec2(0.83f, 0.0f));//0.83, 0.84375
				drawFilledCircle(Colors::yellow, 0.08f);
				drawWiredCircle(Colors::black, 0.08f);
				scale(1.2f, 1.2f);
				drawFilledTriangle(Colors::black, vec2(0.0f, 0.05f), vec2(0.0f, -0.05f), vec2(-0.05f, 0.02f));//����Ŀ���
				drawFilledTriangle(Colors::black, vec2(-0.05f, -0.02f), vec2(0.0f, -0.05f), vec2(-0.05f, 0.02f));
				drawWiredCircle(Colors::black, 0.02f);
				drawWiredCircle(Colors::black, 0.035f);
				if (!sound_on) {//���� �Ҹ��� ���������� ������ xǥ�� �׸���
					setLineWidth(3.5f);
					drawLine(Colors::red, vec2(0.045f, 0.045f), Colors::red, vec2(-0.045f, -0.045f));
					drawLine(Colors::red, vec2(-0.045f, 0.045f), Colors::red, vec2(0.045f, -0.045f));
				}
			}
			endTransformation();
			//�����ư
			beginTransformation(); {
				setLineWidth(2.5f);
				translate(center + vec2(0.62f, 0.0f));//0.62, 0.84375
				drawFilledCircle(Colors::white, 0.08f);//�ڽ��� ����E���� Exit�� E�Դϴ�
				drawWiredCircle(Colors::black, 0.08f);
				setLineWidth(4.0f);
				scale(1.2f, 1.2f);
				drawLine(Colors::black, vec2(0.03f, 0.04f), Colors::black, vec2(-0.03f, 0.04f));
				drawLine(Colors::black, vec2(-0.03f, 0.04f), Colors::black, vec2(-0.03f, -0.04f));
				drawLine(Colors::black, vec2(-0.03f, 0.0f), Colors::black, vec2(0.03f, 0.0f));
				drawLine(Colors::black, vec2(-0.03f, -0.04f), Colors::black, vec2(0.03f, -0.04f));
			}
			endTransformation();

			beginTransformation(); {
				setLineWidth(2.5f);
				translate(center + vec2(0.41f, 0.0f));//0.67, 0.84375
				if (skill_on) {
					drawFilledBox(Colors::gray, 0.16f, 0.16f);
					drawWiredBox(Colors::black, 0.16f, 0.16f);
					setLineWidth(4.0f);
					scale(1.2f, 1.2f);
					drawLine(Colors::white, vec2(0.03f, 0.04f), Colors::white, vec2(-0.03f, 0.04f));
					drawLine(Colors::white, vec2(-0.03f, 0.04f), Colors::white, vec2(-0.03f, -0.04f));
					drawLine(Colors::white, vec2(-0.03f, -0.04f), Colors::white, vec2(0.03f, -0.04f));
				}
				else {
					drawFilledBox(Colors::black, 0.16f, 0.16f);
				}
			}
			endTransformation();
		}
	};

	class Game : public Game2D {
		Interface interface;
		Timer timer[4];
		Sound sound[5];//��� �Ѿ� ���� �� ���� ��
		Character character;
		Turret* turret = nullptr;
		Monster* monster[MAX_MONSTER] = { nullptr, };
		Bullet* bullet[MAX_BULLET] = { nullptr, };

		int count = 0;
		int stage = 1;
		int sum_count = 0; 
		bool win = false;
		bool lose = false;

	public:
		Game()
			: Game2D("Shooting Game!", 900, 900, false)
		{
			this->sound[0].check("bgm.mp3", true);
			this->sound[1].check("shoot.mp3", false);
			this->sound[2].check("hit.mp3", false);
			this->sound[3].check("finish.mp3", false);
			this->sound[4].check("skill.mp3", false);
			timer[0].start();
			timer[1].start();
			timer[2].start();
			sound[0].play();
		}

		~Game() {
			for (int i = 0; i < MAX_BULLET; i++) {
				if (bullet[i] != nullptr) { delete bullet[i]; bullet[i] = nullptr; }
			}
			for (int i = 0; i < MAX_MONSTER; i++) {
				if (monster[i] != nullptr) { delete monster[i]; monster[i] = nullptr; }
			}
			if (turret != nullptr) { delete turret; turret = nullptr; }
		}


		void update() override {
			const vec2 mouse_pos = getCursorPos();
			if (win == false && lose == false) {
				if (count >= 20 && stage == 1) {
					for (int i = 0; i < MAX_BULLET; i++) {
						if (bullet[i] != nullptr) { delete bullet[i]; bullet[i] = nullptr; }
					}
					for (int i = 0; i < MAX_MONSTER; i++) {
						if (monster[i] != nullptr) { delete monster[i]; monster[i] = nullptr; }
					}
					timer[0].reset();
					timer[1].reset();
					timer[0].start();
					timer[1].start();
					turret = new Turret;
					character.center = vec2(-0.5f, -0.5f);
					character.direction = 0.0f;
					count = 0;
					stage++;
				}
				else if (count >= 40 && stage == 2) {
					for (int i = 0; i < MAX_BULLET; i++) {
						if (bullet[i] != nullptr) { delete bullet[i]; bullet[i] = nullptr; }
					}
					for (int i = 0; i < MAX_MONSTER; i++) {
						if (monster[i] != nullptr) { delete monster[i]; monster[i] = nullptr; }
					}
					if (turret != nullptr) { delete turret; turret = nullptr; }
					win = true;
					sound[3].play();
				}

				//ĳ�����̵� 0.5�� 45��
				if (isKeyPressed(GLFW_KEY_A))
					character.center.x -= 0.1f * getTimeStep();
				if (isKeyPressed(GLFW_KEY_S))
					character.center.y -= 0.1f * getTimeStep();
				if (isKeyPressed(GLFW_KEY_D))
					character.center.x += 0.1f * getTimeStep();
				if (isKeyPressed(GLFW_KEY_W))
					character.center.y += 0.1f * getTimeStep();

				//ĳ���� ��ġ���� -1.0 <= x <= 1.0, -1.0 <= y <= 0.75
				if (character.center.x <= -1.0f) { character.center.x = -1.0f; }
				if (character.center.x >= 1.0f) { character.center.x = 1.0f; }
				if (character.center.y >= 0.75f) { character.center.y = 0.75f; }
				if (character.center.y <= -1.0f) { character.center.y = -1.0f; }

				//�Ѿ˻���
				if (isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_1))
				{
					if ((getCursorPos() - vec2(0.83f, 0.875f)).distance() <= 0.08f) {
						interface.sound_on = !interface.sound_on;
						sound[0].channel->setPaused(!interface.sound_on);
					}
					else if ((getCursorPos() - vec2(0.62f, 0.875f)).distance() <= 0.08f) {
						sound[3].play();
						lose = true;
					}
					int index = 0;
					for (index = 0; index < MAX_BULLET; index++) {
						if (bullet[index] == nullptr)
							break;
					}
					if (index < MAX_BULLET) {
						bullet[index] = new Bullet;//�ϳ� �����Ҵ� �� ��
						bullet[index]->center = character.center;//��ġ ����
						character.direction = get_direction(mouse_pos - character.center);
						bullet[index]->direction = character.direction;
						sound[1].play();
						if (bullet[index]->direction == 0.0f)//���⸶�� �ӵ� ����
							bullet[index]->velocity = vec2(0.45f, 0.0f);
						else if (bullet[index]->direction == 0.5f)
							bullet[index]->velocity = vec2(0.225f, 0.225f);
						else if (bullet[index]->direction == 1.0f)
							bullet[index]->velocity = vec2(0.0f, 0.45f);
						else if (bullet[index]->direction == 1.5f)
							bullet[index]->velocity = vec2(-0.225f, 0.225f);
						else if (bullet[index]->direction == 2.0f)
							bullet[index]->velocity = vec2(-0.45f, 0.0f);
						else if (bullet[index]->direction == 2.5f)
							bullet[index]->velocity = vec2(-0.225f, -0.225f);
						else if (bullet[index]->direction == 3.0f)
							bullet[index]->velocity = vec2(0.0f, -0.45f);
						else if (bullet[index]->direction == 3.5f)
							bullet[index]->velocity = vec2(0.225f, -0.225f);
					}
				}

				if (isKeyPressedAndReleased(GLFW_KEY_P)) {
					interface.sound_on = !interface.sound_on;
					sound[0].channel->setPaused(!interface.sound_on);
				}
				if (isKeyPressedAndReleased(GLFW_KEY_C) && interface.skill_on) {
					for (int i = 0; i < MAX_MONSTER; i++) {
						if (monster[i] != nullptr) { delete monster[i]; monster[i] = nullptr; count++; sum_count++; }
					}
					interface.skill_on = false;
					timer[3].start();
					sound[4].play();
				}

				if ((int)timer[3].stopAndGetElapsedMilli() / 1000 >= 5)
					interface.skill_on = true;

				//���� ��ȯ
				if (timer[1].stopAndGetElapsedMilli() >= 5000.0) {
					for (int k = 0; k < 5; k++) {
						int index = 0;
						for (index = 0; index < MAX_MONSTER; index++) {
							if (monster[index] == nullptr)
								break;
						}
						if (index < MAX_MONSTER) {
							monster[index] = new Monster;
							srand((unsigned int)time(NULL) + k);
							switch (rand() % 16)
							{
							case 0:
								monster[index]->center = vec2(-1.0f, 1.0f);
								break;
							case 1:
								monster[index]->center = vec2(-5.0f, 1.0f);
								break;
							case 2:
								monster[index]->center = vec2(0.0f, 1.0f);
								break;
							case 3:
								monster[index]->center = vec2(0.5f, 1.0f);
								break;
							case 4:
								monster[index]->center = vec2(1.0f, 1.0f);
								break;
							case 5:
								monster[index]->center = vec2(-1.0f, 0.5f);
								break;
							case 6:
								monster[index]->center = vec2(1.0f, 0.5f);
								break;
							case 7:
								monster[index]->center = vec2(-1.0f, 0.0f);
								break;
							case 8:
								monster[index]->center = vec2(1.0f, 0.0f);
								break;
							case 9:
								monster[index]->center = vec2(-1.0f, -0.5f);
								break;
							case 10:
								monster[index]->center = vec2(1.0f, -0.5f);
								break;
							case 11:
								monster[index]->center = vec2(-1.0f, -1.0f);
								break;
							case 12:
								monster[index]->center = vec2(-5.0f, -1.0f);
								break;
							case 13:
								monster[index]->center = vec2(0.0f, -1.0f);
								break;
							case 14:
								monster[index]->center = vec2(0.5f, -1.0f);
								break;
							case 15:
								monster[index]->center = vec2(1.0f, -1.0f);
								break;
							}
						}
					}
					timer[1].reset();
					timer[1].start();
				}


				//������
				{
					for (int i = 0; i < MAX_BULLET; i++) {//�Ѿ� ��ġ����
						if (bullet[i] != nullptr) bullet[i]->update(getTimeStep());
					}
					for (int i = 0; i < MAX_BULLET; i++) {
						if (bullet[i] != nullptr && (bullet[i]->center.x >= 1.0f || bullet[i]->center.x <= -1.0f || bullet[i]->center.y >= 0.75f || bullet[i]->center.y <= -1.0f)) {
							//ȭ������� ������
							delete bullet[i];
							bullet[i] = nullptr;//������ ��� ĭ�� nullptr�� �صΰ�
						}
						for (int index = 0; index < MAX_MONSTER; index++) {
							if (monster[index] != nullptr&&bullet[i] != nullptr && monster[index]->crush(bullet[i]->center)) {
								delete bullet[i];
								delete monster[index];
								bullet[i] = nullptr;
								monster[index] = nullptr;
								sound[2].play();
								count++;
								sum_count++;
							}
						}
					}

					for (int i = 0; i < MAX_MONSTER; i++) {
						if (monster[i] != nullptr)monster[i]->update(getTimeStep(), character.center);
						if (monster[i] != nullptr&&character.crush(monster[i]->center)) {
							sound[3].play();
							for (int i = 0; i < MAX_BULLET; i++) {
								if (bullet[i] != nullptr) { delete bullet[i]; bullet[i] = nullptr; }
							}
							for (int i = 0; i < MAX_MONSTER; i++) {
								if (monster[i] != nullptr) { delete monster[i]; monster[i] = nullptr; }
							}
							if (turret != nullptr) { delete turret; turret = nullptr; }
							lose = true;
							sound[3].play();
							break;
						}
					}

					if (turret != nullptr&&turret->crush(character.center)) {

						for (int i = 0; i < MAX_BULLET; i++) {
							if (bullet[i] != nullptr) { delete bullet[i]; bullet[i] = nullptr; }
						}
						for (int i = 0; i < MAX_MONSTER; i++) {
							if (monster[i] != nullptr) { delete monster[i]; monster[i] = nullptr; }
						}
						if (turret != nullptr) { delete turret; turret = nullptr; }
						lose = true;
						sound[3].play();
					}
				}

				//�׸���
				character.draw();
				if (turret != nullptr) turret->draw(timer[0], character.center);
				for (int i = 0; i < MAX_MONSTER; i++) {
					if (monster[i] != nullptr) monster[i]->draw(character.center);
				}
				for (int i = 0; i < MAX_BULLET; i++) {
					if (bullet[i] != nullptr) bullet[i]->draw();
				}
				interface.draw_Interface(timer[0], count);
			}
			else if (win == true && lose == false) {
				beginTransformation();
				{
					drawFilledBox(Colors::skyblue, 2.0f, 2.0f);
				}
				endTransformation();

				beginTransformation();
				{//W
					setLineWidth(5.0f);
					translate(-0.45f, 0.375f);
					drawLine(Colors::black, vec2(-0.25f, 0.25f), Colors::black, vec2(-0.125f, -0.125f));
					drawLine(Colors::black, vec2(0.0f, 0.125f), Colors::black, vec2(-0.125f, -0.125f));
					drawLine(Colors::black, vec2(0.25f, 0.25f), Colors::black, vec2(0.125f, -0.125f));
					drawLine(Colors::black, vec2(0.0f, 0.125f), Colors::black, vec2(0.125f, -0.125f));
				}
				endTransformation();

				beginTransformation();
				{//I
					setLineWidth(5.0f);
					translate(0.0f, 0.375f);
					drawLine(Colors::black, vec2(-0.155f, 0.25f), Colors::black, vec2(0.155f, 0.25f));
					drawLine(Colors::black, vec2(0.0f, 0.25f), Colors::black, vec2(0.0f, -0.125f));
					drawLine(Colors::black, vec2(0.155f, -0.125f), Colors::black, vec2(-0.155f, -0.125f));
				}
				endTransformation();

				beginTransformation();
				{//N
					setLineWidth(5.0f);
					translate(0.45f, 0.375f);
					drawLine(Colors::black, vec2(-0.25f, 0.25f), Colors::black, vec2(-0.25f, -0.125f));
					drawLine(Colors::black, vec2(-0.25f, 0.25f), Colors::black, vec2(0.125f, -0.125f));
					drawLine(Colors::black, vec2(0.125f, 0.25f), Colors::black, vec2(0.125f, -0.125f));
				}
				endTransformation();
				//�����ư
				beginTransformation(); {
					setLineWidth(4.0f);
					translate(0.0f, -0.375f);//0.0f -0.375
					drawFilledBox(Colors::white, 0.45f, 0.23f);
					drawLine(Colors::black, vec2(0.03f, 0.04f), Colors::black, vec2(-0.03f, 0.04f));
					drawLine(Colors::black, vec2(-0.03f, 0.04f), Colors::black, vec2(-0.03f, -0.04f));
					drawLine(Colors::black, vec2(-0.03f, 0.0f), Colors::black, vec2(0.03f, 0.0f));
					drawLine(Colors::black, vec2(-0.03f, -0.04f), Colors::black, vec2(0.03f, -0.04f));
					setLineWidth(2.5f);
					drawWiredBox(Colors::black, 0.45f, 0.23f);
				}
				endTransformation();

				beginTransformation();//�ð� �ڽ�
				{
					setLineWidth(2.5f);
					drawFilledBox(Colors::yellow, 0.48f, 0.2f);
					drawWiredBox(Colors::black, 0.48f, 0.2f);
				}
				endTransformation();

				beginTransformation();//�ð�
				{
					drawNumber(Colors::black, vec2(0.15f, 0.0f), sum_count % 10, 0.4f, 0.4f);
					drawNumber(Colors::black, vec2(0.0f, 0.0f), (sum_count / 10) % 10, 0.4f, 0.4f);
					drawNumber(Colors::black, vec2(-0.15f, 0.0f), (sum_count / 100) % 10, 0.4f, 0.4f);
				}
				endTransformation();

				if (isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_1)) {//���� ���콺�� ������ ��
					if (mouse_pos.y >= -0.49&&mouse_pos.y <= -0.26&&mouse_pos.x >= -0.225f&&mouse_pos.x <= 0.225f)
						is_finish = true;//������
				}
			}
			else if (win == false && lose == true) {
				const vec2 mouse_pos = getCursorPos();
				//���
				beginTransformation();
				{
					drawFilledBox(Colors::skyblue, 2.0f, 2.0f);
				}
				endTransformation();

				beginTransformation();
				{//L
					setLineWidth(5.0f);
					translate(-0.45f, 0.375f);
					drawLine(Colors::black, vec2(-0.25f, 0.25f), Colors::black, vec2(-0.25f, -0.125f));
					drawLine(Colors::black, vec2(-0.25f, -0.125f), Colors::black, vec2(0.0f, -0.125f));
				}
				endTransformation();

				beginTransformation();
				{//O
					setLineWidth(5.0f);
					translate(-0.1f, 0.375f);
					drawLine(Colors::black, vec2(-0.25f, 0.25f), Colors::black, vec2(0.02f, 0.25f));
					drawLine(Colors::black, vec2(-0.25f, 0.25f), Colors::black, vec2(-0.25f, -0.125f));
					drawLine(Colors::black, vec2(-0.25f, -0.125f), Colors::black, vec2(0.02f, -0.125f));
					drawLine(Colors::black, vec2(0.02f, -0.125f), Colors::black, vec2(0.02f, 0.25f));
				}
				endTransformation();

				beginTransformation();
				{//O
					setLineWidth(5.0f);
					translate(0.3f, 0.375f);
					drawLine(Colors::black, vec2(-0.25f, 0.25f), Colors::black, vec2(0.0f, 0.25f));
					drawLine(Colors::black, vec2(-0.25f, 0.25f), Colors::black, vec2(-0.25f, 0.0625f));
					drawLine(Colors::black, vec2(-0.25f, 0.0625f), Colors::black, vec2(0.0f, 0.0625f));
					drawLine(Colors::black, vec2(0.0f, 0.0625f), Colors::black, vec2(0.0f, -0.125f));
					drawLine(Colors::black, vec2(-0.25f, -0.125f), Colors::black, vec2(0.0f, -0.125f));
				}
				endTransformation();

				beginTransformation();
				{//E
					setLineWidth(5.0f);
					translate(0.7f, 0.375f);
					drawLine(Colors::black, vec2(-0.25f, 0.25f), Colors::black, vec2(0.0f, 0.25f));
					drawLine(Colors::black, vec2(-0.25f, 0.25f), Colors::black, vec2(-0.25f, -0.125f));
					drawLine(Colors::black, vec2(-0.25f, 0.0625f), Colors::black, vec2(0.0f, 0.0625f));
					drawLine(Colors::black, vec2(-0.25f, -0.125f), Colors::black, vec2(0.0f, -0.125f));
				}
				endTransformation();
				//�����ư
				beginTransformation(); {
					setLineWidth(4.0f);
					translate(0.0f, -0.375f);//0.0f -0.375
					drawFilledBox(Colors::white, 0.45f, 0.23f);
					drawLine(Colors::black, vec2(0.03f, 0.04f), Colors::black, vec2(-0.03f, 0.04f));
					drawLine(Colors::black, vec2(-0.03f, 0.04f), Colors::black, vec2(-0.03f, -0.04f));
					drawLine(Colors::black, vec2(-0.03f, 0.0f), Colors::black, vec2(0.03f, 0.0f));
					drawLine(Colors::black, vec2(-0.03f, -0.04f), Colors::black, vec2(0.03f, -0.04f));
					setLineWidth(2.5f);
					drawWiredBox(Colors::black, 0.45f, 0.23f);
				}
				endTransformation();

				beginTransformation();//�ð� �ڽ�
				{
					setLineWidth(2.5f);
					drawFilledBox(Colors::yellow, 0.48f, 0.2f);
					drawWiredBox(Colors::black, 0.48f, 0.2f);
				}
				endTransformation();

				beginTransformation();//�ð�
				{
					drawNumber(Colors::black, vec2(0.15f, 0.0f), sum_count % 10, 0.4f, 0.4f);
					drawNumber(Colors::black, vec2(0.0f, 0.0f), (sum_count / 10) % 10, 0.4f, 0.4f);
					drawNumber(Colors::black, vec2(-0.15f, 0.0f), (sum_count / 100) % 10, 0.4f, 0.4f);
				}
				endTransformation();

				if (isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_1)) {//���� ���콺�� ������ ��
					if (mouse_pos.y >= -0.49&&mouse_pos.y <= -0.26&&mouse_pos.x >= -0.225f&&mouse_pos.x <= 0.225f)
						is_finish = true;
				}
			}
		}
	};
};