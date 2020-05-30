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
	Sound() {//생성자 전부 nullptr로 초기화
		system = nullptr;
		sound = nullptr;
		channel = nullptr;
		extradriverdata = nullptr;
	}
	bool check(const char a[],bool loop) {//경로와 반복여부를 매개변수로 받는다
		result = FMOD::System_Create(&system);//설정단계
		if (result != FMOD_OK) return false;
		result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (result != FMOD_OK) return false;
		if (loop)//반복하면
			result = system->createSound(a, FMOD_LOOP_NORMAL, 0, &sound);//NOMAL
		else//아니면
			result = system->createSound(a, FMOD_LOOP_OFF, 0, &sound); //OFF
		if (result != FMOD_OK) return false;
		return true;
	}
	bool play() {//재생
		result = system->playSound(sound, 0, false, &channel);
		if (result != FMOD_OK) return false;
		return true;
	}
};