#pragma once
#include "DrawFunctions.h"
#include "Colors.h"

namespace jm {
	namespace number {
		//���� �׸��� �Լ��� color ���� point ��ġ scale_x x���� ���� scale_y y���� ���� �Ѵ� �⺻ 1.0f
		void drawNum1(const RGB& color, const vec2& point, const float& scale_x = 1.0f, const float& scale_y = 1.0f) {
			beginTransformation();
			{
				translate(point);
				scale(scale_x, scale_y);
				setLineWidth(10.0f);
				drawLine(color, vec2(0.125f, 0.2f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(0.125f, 0.0f), color, vec2(0.125f, -0.2f));
			}
			endTransformation();
		}

		void drawNum2(const RGB& color, const vec2& point, const float& scale_x = 1.0f, const float& scale_y = 1.0f) {
			beginTransformation();
			{
				translate(point);
				scale(scale_x, scale_y);
				setLineWidth(10.0f);
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(0.125f, 0.2f));
				drawLine(color, vec2(0.125f, 0.2f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(-0.125f, 0.0f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(-0.125f, 0.0f), color, vec2(-0.125f, -0.2f));
				drawLine(color, vec2(-0.125f, -0.2f), color, vec2(0.125f, -0.2f));
			}
			endTransformation();
		}

		void drawNum3(const RGB& color, const vec2& point, const float& scale_x = 1.0f, const float& scale_y = 1.0f) {
			beginTransformation();
			{
				translate(point);
				scale(scale_x, scale_y);
				setLineWidth(10.0f);
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(0.125f, 0.2f));
				drawLine(color, vec2(0.125f, 0.2f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(-0.125f, 0.0f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(0.125f, 0.0f), color, vec2(0.125f, -0.2f));
				drawLine(color, vec2(-0.125f, -0.2f), color, vec2(0.125f, -0.2f));
			}
			endTransformation();
		}

		void drawNum4(const RGB& color, const vec2& point, const float& scale_x = 1.0f, const float& scale_y = 1.0f) {
			beginTransformation();
			{
				translate(point);
				scale(scale_x, scale_y);
				setLineWidth(10.0f);
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(-0.125f, 0.0f));
				drawLine(color, vec2(0.125f, 0.2f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(-0.125f, 0.0f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(0.125f, 0.0f), color, vec2(0.125f, -0.2f));
			}
			endTransformation();
		}

		void drawNum5(const RGB& color, const vec2& point, const float& scale_x = 1.0f, const float& scale_y = 1.0f) {
			beginTransformation();
			{
				translate(point);
				scale(scale_x, scale_y);
				setLineWidth(10.0f);
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(0.125f, 0.2f));
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(-0.125f, 0.0f));
				drawLine(color, vec2(-0.125f, 0.0f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(0.125f, 0.0f), color, vec2(0.125f, -0.2f));
				drawLine(color, vec2(-0.125f, -0.2f), color, vec2(0.125f, -0.2f));
			}
			endTransformation();
		}

		void drawNum6(const RGB& color, const vec2& point, const float& scale_x = 1.0f, const float& scale_y = 1.0f) {
			beginTransformation();
			{
				translate(point);
				scale(scale_x, scale_y);
				setLineWidth(10.0f);
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(0.125f, 0.2f));
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(-0.125f, 0.0f));
				drawLine(color, vec2(-0.125f, 0.0f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(-0.125f, 0.0f), color, vec2(-0.125f, -0.2f));
				drawLine(color, vec2(0.125f, 0.0f), color, vec2(0.125f, -0.2f));
				drawLine(color, vec2(-0.125f, -0.2f), color, vec2(0.125f, -0.2f));
			}
			endTransformation();
		}

		void drawNum7(const RGB& color, const vec2& point, const float& scale_x = 1.0f, const float& scale_y = 1.0f) {
			beginTransformation();
			{
				translate(point);
				scale(scale_x, scale_y);
				setLineWidth(10.0f);
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(0.125f, 0.2f));
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(-0.125f, 0.0f));
				drawLine(color, vec2(0.125f, 0.2f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(0.125f, 0.0f), color, vec2(0.125f, -0.2f));
			}
			endTransformation();
		}

		void drawNum8(const RGB& color, const vec2& point, const float& scale_x = 1.0f, const float& scale_y = 1.0f) {
			beginTransformation();
			{
				translate(point);
				scale(scale_x, scale_y);
				setLineWidth(10.0f);
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(0.125f, 0.2f));
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(-0.125f, 0.0f));
				drawLine(color, vec2(0.125f, 0.2f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(-0.125f, 0.0f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(-0.125f, 0.0f), color, vec2(-0.125f, -0.2f));
				drawLine(color, vec2(0.125f, 0.0f), color, vec2(0.125f, -0.2f));
				drawLine(color, vec2(-0.125f, -0.2f), color, vec2(0.125f, -0.2f));
			}
			endTransformation();
		}

		void drawNum9(const RGB& color, const vec2& point, const float& scale_x = 1.0f, const float& scale_y = 1.0f) {
			beginTransformation();
			{
				translate(point);
				scale(scale_x, scale_y);
				setLineWidth(10.0f);
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(0.125f, 0.2f));
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(-0.125f, 0.0f));
				drawLine(color, vec2(0.125f, 0.2f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(-0.125f, 0.0f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(0.125f, 0.0f), color, vec2(0.125f, -0.2f));
				drawLine(color, vec2(-0.125f, -0.2f), color, vec2(0.125f, -0.2f));
			}
			endTransformation();
		}

		void drawNum0(const RGB& color, const vec2& point, const float& scale_x = 1.0f, const float& scale_y = 1.0f) {
			beginTransformation();
			{
				translate(point);
				scale(scale_x, scale_y);
				setLineWidth(10.0f);
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(0.125f, 0.2f));
				drawLine(color, vec2(-0.125f, 0.2f), color, vec2(-0.125f, 0.0f));
				drawLine(color, vec2(0.125f, 0.2f), color, vec2(0.125f, 0.0f));
				drawLine(color, vec2(-0.125f, 0.0f), color, vec2(-0.125f, -0.2f));
				drawLine(color, vec2(0.125f, 0.0f), color, vec2(0.125f, -0.2f));
				drawLine(color, vec2(-0.125f, -0.2f), color, vec2(0.125f, -0.2f));
			}
			endTransformation();
		}
	}

	//�����ϰ� drawNumber�Լ��� ���� number�� �׸����� �ϴ� ����
	void drawNumber(const RGB& color, const vec2& point, const int& number, const float& scale_x = 1.0f, const float& scale_y = 1.0f) {
		switch (number) {
		case 1:
			number::drawNum1(color, point, scale_x, scale_y);
			break;
		case 2:
			number::drawNum2(color, point, scale_x, scale_y);
			break;
		case 3:
			number::drawNum3(color, point, scale_x, scale_y);
			break;
		case 4:
			number::drawNum4(color, point, scale_x, scale_y);
			break;
		case 5:
			number::drawNum5(color, point, scale_x, scale_y);
			break;
		case 6:
			number::drawNum6(color, point, scale_x, scale_y);
			break;
		case 7:
			number::drawNum7(color, point, scale_x, scale_y);
			break;
		case 8:
			number::drawNum8(color, point, scale_x, scale_y);
			break;
		case 9:
			number::drawNum9(color, point, scale_x, scale_y);
			break;
		case 0:
			number::drawNum0(color, point, scale_x, scale_y);
			break;
		default:
			std::cout << "Number.h��� draw�Լ� default" << std::endl;
			break;
		}
	}
}