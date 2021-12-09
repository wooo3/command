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
	CommandAllButton button;		//レバー＆ボタン
	string success_motion_name;		//コマンド成立時に移行するモーション名
	int skip_chain_route_id;		//スキップ先のID指定　指定しない場合は-1（INVALID_VAL）
	int skip_chain_count;			//スキップ時のチェーン進行度指定　スキップ先のIDとセットで指定する　指定しない場合は-1（INVALID_VAL）

	bool empty_flg;				//「レバー、ボタン、モーション名」で使用する３つのセルが空白のときtrue（空のデータということを示す）
	bool lever_empty_flg;		//レバー空
	bool button_empty_flg;		//ボタン空

	bool end_flg;				//「END」が指定されたときの終了を示す

	int start_frame;			//派生可能になるフレーム
	int end_frame;				//派生不可になるフレーム

	void SetChainButton( string parts );
	void SetChainLever( string parts );
};



//ChainProperty::id
//100番～199番はVT中のチェーン
//200番～299番は空キャンセル可能

class ChainProperty{
public:
	int frame;			//派生可能になるフレーム（ほぼ空キャンチェーン用）
	int id;					//ID
	int group;				//グループ番号	同グループ番号を指定することで派生が可能
	string start_motion_name;	//開始モーション名
	COMMAND_SUCCESS_STATE success_state;		//コマンドが成功する状態（地空）
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


	int chain_route_id;		//実行中のチェーンのID
	int chain_count;		//実行中のチェーンの進行度

	string* chainname;		//成立したモーション名へのポインタ
	
	void SetChainRoute( string* motion_name );	//チェーンルートの設定
	void ChainCountInc();			//チェーンカウントを進める
	void ChainEnd();				//チェーン終了処理　ダメージの時と攻撃終了時に動かせばいい？
	void ChainSkip( int skipID, int skipCount );		//IDとカウントを指定してチェーンをスキップ

	void InputStatus( BUTTON button, int* pMultipush, string* motion_name, int fgtFrame, bool hitFlg, float y_pos );		//入力
	bool CommandCheck( BUTTON button, CommandAllButton chain_button, int* multipush_count );
};

#endif