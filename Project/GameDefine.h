#pragma once

#include "Mof.h"

// �ړ��\�͈͂̔���
#define FIELD_HALF_X (9.0f)
#define FIELD_HALF_Z (14.0f)

//�v���C���[
// �ړ����x
#define PLAYER_SPEED		(0.1f)

// �ړ����x
#define PLAYER_SHOT_SPEED		(0.4f)

//�e�̔��ˌ��x
#define PLAYERSHOT_COUNT (40)

//�e�̔��ˊԊu
#define PLAYERSHOT_WAIT (5)

//�e�̔��ˌ��x
#define WIDE_RED (0.05f)

enum PlayerMove {
	IDLE,
	LEFT,
	RIGHT,
};

enum PlayerShotMode {
	MODE_SINGLE,
	MODE_DOUBLE,
	MODE_TRIPLE,
};

enum PlayerShotSubMode {
	MODE_DIRECT,
	MODE_WIDE,
};

//�X�N���[�����x
#define SCROLL_SPEED (1.0f)

//�C�[�W���O�̎�ނ̒�`
enum EASING_TYPE {
	EASE_LINEAR,
	EASE_IN_SINE,
	EASE_OUT_SINE,
	EASE_INOUT_SINE,
};

//�A�j���[�V�����p�\����
struct ANIM_DATA {
	float Time;
	float Value;
	EASING_TYPE EasingType;
};

float InterpolationAnim(float AnimTime, ANIM_DATA* AnimData, int cnt);