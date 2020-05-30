#pragma once
#include"fmod.hpp"

class Sound {
public:
	FMOD::System	*system;
	FMOD::Sound		*sound;
	FMOD::Channel	*channel;
	FMOD_RESULT		result;
	void			*extradriverdata;

public:
	Sound() {//������ ���� nullptr�� �ʱ�ȭ
		system = nullptr;
		sound = nullptr;
		channel = nullptr;
		extradriverdata = nullptr;
	}
	bool check(const char a[],bool loop) {//��ο� �ݺ����θ� �Ű������� �޴´�
		result = FMOD::System_Create(&system);//�����ܰ�
		if (result != FMOD_OK) return false;
		result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (result != FMOD_OK) return false;
		if (loop)//�ݺ��ϸ�
			result = system->createSound(a, FMOD_LOOP_NORMAL, 0, &sound);//NOMAL
		else//�ƴϸ�
			result = system->createSound(a, FMOD_LOOP_OFF, 0, &sound); //OFF
		if (result != FMOD_OK) return false;
		return true;
	}
	bool play() {//���
		result = system->playSound(sound, 0, false, &channel);
		if (result != FMOD_OK) return false;
		return true;
	}
};