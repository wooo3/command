#ifndef Command_H
#define Command_H

#define commandbufsize 70
#define charsize 4
#define command_yuuyo 15



#include <stdio.h>
#include "..\..\Engine\Global.h"
#include "..\..\Engine\Button\button.h"
#include "..\..\Engine\Archive\Archive.h"


#define ground 0




#define commandchar 10
#define COMMAND_PARTS_MAX 16

enum COMMAND_EX_CODE{
	COMMAND_EX_CODE_VARIABLE,		//�g���K�[���̂�
	COMMAND_EX_CODE_CHARA_FLAG_1,	//�L�����t���O
	COMMAND_EX_CODE_CHARA_FLAG_2,
	COMMAND_EX_CODE_CHARA_FLAG_3,
	COMMAND_EX_CODE_CHARA_FLAG_4,
	COMMAND_EX_CODE_CHARA_FLAG_5,
	COMMAND_EX_CODE_CHARA_FLAG_6,
	COMMAND_EX_CODE_CHARA_FLAG_7,
	COMMAND_EX_CODE_CHARA_FLAG_8,
	COMMAND_EX_CODE_LIFE_RED,		//�̗�1/5
	COMMAND_EX_CODE_LIFE_GREEN,		//�̗�MAX
	COMMAND_EX_CODE_HASEI,			//�S�S����n�@�̂悤�Ȕh���p�i�L�����t���O�ƕ��p�@��ΐ�������j
	COMMAND_EX_CODE_CANCEL_ONLY,	//�L�����Z�����炵���o���Ȃ�
	COMMAND_EX_CODE_FORCE_CANCEL,	//�L�����Z�����悤�Ƃ��Ă���Z���A�L�����Z���\�Z���ǂ�����������������
	COMMAND_EX_CODE_MAX,
};
#define COMMAND_CHARAFLAG_MAX 8

enum COMMAND_SUCCESS_STATE{
	COMMAND_SUCCESS_STATE_GROUND,
	COMMAND_SUCCESS_STATE_AIR,
	COMMAND_SUCCESS_STATE_LOCK,	//�g��Ȃ���
	COMMAND_SUCCESS_STATE_MAX
};


enum COMMAND_STRENGTH_CHECK{	//�㒆��EX���ʗp
	COMMAND_STRENGTH_CHECK_L,
	COMMAND_STRENGTH_CHECK_M,
	COMMAND_STRENGTH_CHECK_H,
	COMMAND_STRENGTH_CHECK_EX,	//2016/4/24 EX�͓��������Ƃ��Q�[�W����̊֌W�Ŏg��Ȃ����Ƃɂ���
	COMMAND_STRENGTH_CHECK_MAX
};


class Tame{		//���ߗp
public:
#define tame_clear_count 9	//�����Ă��玟�̓��͂܂ŗL���Ȏ���
	Tame(){
		memset( this, 0, sizeof(Tame) );
	}

	//[3] ���A���^�C���ȗ��ߎ��ԁA�������Ƃ���[0]��ۑ�����A���ߕۑ��N���A�܂ł̃J�E���g
	int count_tame[INPUT_LABEL_ALL][3];
};


class CommandAllButton : public ALL_INPUT{
public:
	bool lever_youso;	//���o�[�v�f�p
	bool tame;			//���ߗp
	bool release;		//�{�^�������p
	bool multi_push;	//�{�^�����������p
	bool any_attack;		//�U���{�^���ǂ�ł�OK
	bool any_attack_double;	//�U���{�^���ǂ�ł�OK�i2���������p�j
	bool any_attack_triple;	//�U���{�^���ǂ�ł�OK�i3���������p�j
	CommandAllButton(){
		lever_youso = false;
		tame = false;
		release = false;
		multi_push = false;
		any_attack = false;
		any_attack_double = false;
		any_attack_triple = false;
	}
	
};




class CommandParts{		//�g����A�@�g����B�@���̂悤�Ɏg���N���X
public:
	CommandParts(){
		reception_time = valid_time = valid_count = variation = 0;
		commandArray.clear();
	};
	CommandParts( string con_command, int receptiontime, int validtime, COMMAND_SUCCESS_STATE successstate );

	void CommandSet( string con_command, int receptiontime, int validtime, COMMAND_SUCCESS_STATE successstate );
	

	string command;			//csv�̈�s����ǂݍ��ރR�}���h
	int reception_time;		//csv�̈�s����ǂݍ��ޓ��͗P�\����
	int valid_time;			//csv�̈�s����ǂݍ��ރR�}���h�̗L������
	int valid_count;		//�R�}���h���������Ă���̃J�E���g
	COMMAND_SUCCESS_STATE success_state;		//�R�}���h�����������ԁi�n��j
	int variation;

	vector<string> commandArray_string;			//2,3,6,a �Ƃ��ŕ��������R�}���h ������
	vector<CommandAllButton> commandArray;		//2,3,6,a �Ƃ��ŕ��������R�}���h �{�^��

	bool CheckTame( bool check_btn, int tame_time, int need_tame );	//���߃`�F�b�N
	bool CheckCommand( vector<ALL_INPUT>*, Tame* tame, COMMAND_STRENGTH_CHECK* abc_check, int y_pos, int dy );	//�R�}���h�o�b�t�@���󂯎��R�}���h���������Ă��邩���肷��

	ALL_INPUT command_success_key_save;	//�R�}���h�������̓��͂�ۑ����Ă����i����V�X�L�����ő��J�J�g��s���͂������悤�Ƃ��āA�Q��ڂ�K���͂ŏo�Ȃ������̂Łj
	int success_bufferIndex_save;
};


#define COMMAND_SUCCESS_MOTION_NAME_ALL 4
//�S�̗��R
//�����E�݂����ȃR�}���h�\���̃L������������Ƃ�
//236236ABC(UC)��236236AorBorC(SC)��623AB��623B�@�Ƃ����ӂ��ɂ���������

class CommandProperty{
public:
	int variation;	//variation

	string command;	//�R�}���h(���̕����œ��͂����肳���)
	COMMAND_SUCCESS_STATE success_state;		//�R�}���h�����������ԁi�n��j
	int reception_time;		//���͎�t����
	int valid_time;			//���͂��������Ă���L���Ȏ���
	string motion_name;		//�R�}���h�������Ɉڍs���郂�[�V������
	string ng_key;			//�֎~�L�[
	
	COMMAND_EX_CODE ex_code1;	//����w��P
	COMMAND_EX_CODE ex_code2;	//����w��Q
	COMMAND_EX_CODE ex_code3;	//����w��R

	int tama_id;			//�eID�@�w�肵���eID����ł��c���Ă���΃R�}���h���s
};




class Command{
public:
	vector<CommandProperty> commandproperty;
	void DataLoad( char propertydata[64], istringstream* pIss=NULL );
	void DataLoadFromFileInMemory( char propertydata[64], CArchive* pArchive );


	Command();
	void Reset();
	void AddCommandBuffer( ALL_INPUT button );

	DIRECTION chara_direction;
	int player_y;		//y���W
	int player_dy;		//dy
	vector<ALL_INPUT> command_buffer;	//���͂����R�}���h������o�b�t�@
	

	vector<CommandParts> skillcommand;	//CommandParts���R�}���h����
	CommandParts CommandPushBack( string com, int receptiontime, int validtime, COMMAND_SUCCESS_STATE successstate );

	string* commandname[COMMAND_SUCCESS_MOTION_NAME_ALL];	//���������R�}���h�̃��[�V�������ւ̃|�C���^
	int commandpriority[COMMAND_SUCCESS_MOTION_NAME_ALL];	//���������R�}���h�̗D��x�ւ̃|�C���^
	
	int find_command_count;			//���������R�}���h�̐�

	void InputStatus( BUTTON button, int* tamaID, bool isAI );		//�R�}���h�܂Ƃ�
	

	int multipush_count[INPUT_LABEL_ALL];	//���������p


	COMMAND_STRENGTH_CHECK strength_check;
	void SuccessButtonSet( int index, ALL_INPUT allInput, CommandAllButton allButton );
	void EX_NotEnough( int index );
	ALL_INPUT success_input[COMMAND_SUCCESS_MOTION_NAME_ALL];			//�������̓��͂�ۑ����Ă����iEX�ŃQ�[�W����Ȃ������Ƃ���COMMAND_STRENGTH_CHECK�i���x�j��ύX����p�j
	CommandAllButton success_button[COMMAND_SUCCESS_MOTION_NAME_ALL];	//�������̃R�}���h�p�[�c��ۑ����Ă���


	Tame tame;
	void InputTame( bool press, int* count_tame, bool isLR=false );

	bool chara_flag[COMMAND_CHARAFLAG_MAX];	//��O�p�L�����t���O
	bool vTrg_flag;	//VT����
	bool cancelOnly_flag;	//�L�����Z������
	bool ExCodeCheck( CommandProperty* c_property, bool* c_flag, bool Vtrg, bool cancelOnly );
	bool TamaID_Check( CommandProperty* c_property, int* tamaID );


	bool before_chara_direction;	//1F�O�̌���
};

#endif