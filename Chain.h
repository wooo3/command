#ifndef Chain_H
#define Chain_H



#include "..\..\Engine\Global.h"
#include "Command.h"
#include "..\..\Engine\Button\button.h"

#define ground 0



class ChainParts{
public:
	ChainParts(){
		skip_chain_route_id = skip_chain_count = INVALID_VAL;
		empty_flg = lever_empty_flg = button_empty_flg = true;
		end_flg = false;
	}
	CommandAllButton button;		//���o�[���{�^��
	string success_motion_name;		//�R�}���h�������Ɉڍs���郂�[�V������
	int skip_chain_route_id;		//�X�L�b�v���ID�w��@�w�肵�Ȃ��ꍇ��-1�iINVALID_VAL�j
	int skip_chain_count;			//�X�L�b�v���̃`�F�[���i�s�x�w��@�X�L�b�v���ID�ƃZ�b�g�Ŏw�肷��@�w�肵�Ȃ��ꍇ��-1�iINVALID_VAL�j

	bool empty_flg;				//�u���o�[�A�{�^���A���[�V�������v�Ŏg�p����R�̃Z�����󔒂̂Ƃ�true�i��̃f�[�^�Ƃ������Ƃ������j
	bool lever_empty_flg;		//���o�[��
	bool button_empty_flg;		//�{�^����

	bool end_flg;				//�uEND�v���w�肳�ꂽ�Ƃ��̏I��������

	int start_frame;			//�h���\�ɂȂ�t���[��
	int end_frame;				//�h���s�ɂȂ�t���[��

	void SetChainButton( string parts );
	void SetChainLever( string parts );
};



//ChainProperty::id
//100�ԁ`199�Ԃ�VT���̃`�F�[��
//200�ԁ`299�Ԃ͋�L�����Z���\

class ChainProperty{
public:
	int frame;			//�h���\�ɂȂ�t���[���i�قڋ�L�����`�F�[���p�j
	int id;					//ID
	int group;				//�O���[�v�ԍ�	���O���[�v�ԍ����w�肷�邱�ƂŔh�����\
	string start_motion_name;	//�J�n���[�V������
	COMMAND_SUCCESS_STATE success_state;		//�R�}���h�����������ԁi�n��j
	vector<ChainParts> parts;
};




class Chain{
public:
	Chain();
	void Reset();
	void DataLoad( char propertydata[64], istringstream* pIss=NULL );
	void DataLoadFromFileInMemory( char propertydata[64], CArchive* pArchive );

	DIRECTION chara_direction;


	vector<ChainProperty> chaindata;


	int chain_route_id;		//���s���̃`�F�[����ID
	int chain_count;		//���s���̃`�F�[���̐i�s�x

	string* chainname;		//�����������[�V�������ւ̃|�C���^
	
	void SetChainRoute( string* motion_name );	//�`�F�[�����[�g�̐ݒ�
	void ChainCountInc();			//�`�F�[���J�E���g��i�߂�
	void ChainEnd();				//�`�F�[���I�������@�_���[�W�̎��ƍU���I�����ɓ������΂����H
	void ChainSkip( int skipID, int skipCount );		//ID�ƃJ�E���g���w�肵�ă`�F�[�����X�L�b�v

	void InputStatus( BUTTON button, int* pMultipush, string* motion_name, int fgtFrame, bool hitFlg, float y_pos );		//����
	bool CommandCheck( BUTTON button, CommandAllButton chain_button, int* multipush_count );
};

#endif