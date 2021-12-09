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
	COMMAND_EX_CODE_VARIABLE,		//トリガー中のみ
	COMMAND_EX_CODE_CHARA_FLAG_1,	//キャラフラグ
	COMMAND_EX_CODE_CHARA_FLAG_2,
	COMMAND_EX_CODE_CHARA_FLAG_3,
	COMMAND_EX_CODE_CHARA_FLAG_4,
	COMMAND_EX_CODE_CHARA_FLAG_5,
	COMMAND_EX_CODE_CHARA_FLAG_6,
	COMMAND_EX_CODE_CHARA_FLAG_7,
	COMMAND_EX_CODE_CHARA_FLAG_8,
	COMMAND_EX_CODE_LIFE_RED,		//体力1/5
	COMMAND_EX_CODE_LIFE_GREEN,		//体力MAX
	COMMAND_EX_CODE_HASEI,			//百鬼→空刃　のような派生用（キャラフラグと併用　絶対成立する）
	COMMAND_EX_CODE_CANCEL_ONLY,	//キャンセルからしか出せない
	COMMAND_EX_CODE_FORCE_CANCEL,	//キャンセルしようとしている技が、キャンセル可能技かどうかを見ず成立する
	COMMAND_EX_CODE_MAX,
};
#define COMMAND_CHARAFLAG_MAX 8

enum COMMAND_SUCCESS_STATE{
	COMMAND_SUCCESS_STATE_GROUND,
	COMMAND_SUCCESS_STATE_AIR,
	COMMAND_SUCCESS_STATE_LOCK,	//使わない物
	COMMAND_SUCCESS_STATE_MAX
};


enum COMMAND_STRENGTH_CHECK{	//弱中強EX判別用
	COMMAND_STRENGTH_CHECK_L,
	COMMAND_STRENGTH_CHECK_M,
	COMMAND_STRENGTH_CHECK_H,
	COMMAND_STRENGTH_CHECK_EX,	//2016/4/24 EXは同時押しとかゲージ消費の関係で使わないことにする
	COMMAND_STRENGTH_CHECK_MAX
};


class Tame{		//溜め用
public:
#define tame_clear_count 9	//離してから次の入力まで有効な時間
	Tame(){
		memset( this, 0, sizeof(Tame) );
	}

	//[3] リアルタイムな溜め時間、離したときに[0]を保存する、ため保存クリアまでのカウント
	int count_tame[INPUT_LABEL_ALL][3];
};


class CommandAllButton : public ALL_INPUT{
public:
	bool lever_youso;	//レバー要素用
	bool tame;			//溜め用
	bool release;		//ボタン離し用
	bool multi_push;	//ボタン同時押し用
	bool any_attack;		//攻撃ボタンどれでもOK
	bool any_attack_double;	//攻撃ボタンどれでもOK（2つ同時押し用）
	bool any_attack_triple;	//攻撃ボタンどれでもOK（3つ同時押し用）
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




class CommandParts{		//波動拳A　波動拳B　等のように使うクラス
public:
	CommandParts(){
		reception_time = valid_time = valid_count = variation = 0;
		commandArray.clear();
	};
	CommandParts( string con_command, int receptiontime, int validtime, COMMAND_SUCCESS_STATE successstate );

	void CommandSet( string con_command, int receptiontime, int validtime, COMMAND_SUCCESS_STATE successstate );
	

	string command;			//csvの一行から読み込むコマンド
	int reception_time;		//csvの一行から読み込む入力猶予時間
	int valid_time;			//csvの一行から読み込むコマンドの有効時間
	int valid_count;		//コマンドが成立してからのカウント
	COMMAND_SUCCESS_STATE success_state;		//コマンドが成功する状態（地空）
	int variation;

	vector<string> commandArray_string;			//2,3,6,a とかで分割したコマンド 文字列
	vector<CommandAllButton> commandArray;		//2,3,6,a とかで分割したコマンド ボタン

	bool CheckTame( bool check_btn, int tame_time, int need_tame );	//ためチェック
	bool CheckCommand( vector<ALL_INPUT>*, Tame* tame, COMMAND_STRENGTH_CHECK* abc_check, int y_pos, int dy );	//コマンドバッファを受け取りコマンドが成立しているか判定する

	ALL_INPUT command_success_key_save;	//コマンド成立時の入力を保存しておく（綾瀬Vスキル→最速カカト先行入力を許可しようとして、２回目のK入力で出なかったので）
	int success_bufferIndex_save;
};


#define COMMAND_SUCCESS_MOTION_NAME_ALL 4
//４つの理由
//リュウみたいなコマンド構成のキャラを作ったとき
//236236ABC(UC)＞236236AorBorC(SC)＞623AB＞623B　というふうにしたいため

class CommandProperty{
public:
	int variation;	//variation

	string command;	//コマンド(この文字で入力が判定される)
	COMMAND_SUCCESS_STATE success_state;		//コマンドが成功する状態（地空）
	int reception_time;		//入力受付時間
	int valid_time;			//入力が成立してから有効な時間
	string motion_name;		//コマンド成立時に移行するモーション名
	string ng_key;			//禁止キー
	
	COMMAND_EX_CODE ex_code1;	//特殊指定１
	COMMAND_EX_CODE ex_code2;	//特殊指定２
	COMMAND_EX_CODE ex_code3;	//特殊指定３

	int tama_id;			//弾ID　指定した弾IDが一つでも残っていればコマンド失敗
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
	int player_y;		//y座標
	int player_dy;		//dy
	vector<ALL_INPUT> command_buffer;	//入力したコマンドを入れるバッファ
	

	vector<CommandParts> skillcommand;	//CommandPartsをコマンド数分
	CommandParts CommandPushBack( string com, int receptiontime, int validtime, COMMAND_SUCCESS_STATE successstate );

	string* commandname[COMMAND_SUCCESS_MOTION_NAME_ALL];	//成立したコマンドのモーション名へのポインタ
	int commandpriority[COMMAND_SUCCESS_MOTION_NAME_ALL];	//成立したコマンドの優先度へのポインタ
	
	int find_command_count;			//成立したコマンドの数

	void InputStatus( BUTTON button, int* tamaID, bool isAI );		//コマンドまとめ
	

	int multipush_count[INPUT_LABEL_ALL];	//同時押し用


	COMMAND_STRENGTH_CHECK strength_check;
	void SuccessButtonSet( int index, ALL_INPUT allInput, CommandAllButton allButton );
	void EX_NotEnough( int index );
	ALL_INPUT success_input[COMMAND_SUCCESS_MOTION_NAME_ALL];			//成立時の入力を保存しておく（EXでゲージ足りなかったときにCOMMAND_STRENGTH_CHECK（強度）を変更する用）
	CommandAllButton success_button[COMMAND_SUCCESS_MOTION_NAME_ALL];	//成立時のコマンドパーツを保存しておく


	Tame tame;
	void InputTame( bool press, int* count_tame, bool isLR=false );

	bool chara_flag[COMMAND_CHARAFLAG_MAX];	//例外用キャラフラグ
	bool vTrg_flag;	//VT中か
	bool cancelOnly_flag;	//キャンセル中か
	bool ExCodeCheck( CommandProperty* c_property, bool* c_flag, bool Vtrg, bool cancelOnly );
	bool TamaID_Check( CommandProperty* c_property, int* tamaID );


	bool before_chara_direction;	//1F前の向き
};

#endif