#include "Chain.h"
#include "..\..\Engine\LoadingLog.h"

Chain::Chain(){
	Reset();
}
void Chain::Reset(){
	chaindata.clear();
	chain_count = INVALID_VAL;
	chain_route_id = INVALID_VAL;
	chainname = NULL;
	chara_direction = DIRECTION_LEFT;
}

void Chain::DataLoad( char propertydata[64], istringstream* pIss ){
	Reset();


	istringstream iss;
	if( !pIss ){	//直接別個のファイルから読み込み　アーカイブを使わない時
		LLog::GetInstance()->SetFileName( propertydata );
		ifstream ifs( propertydata );
		if( !ifs ){
			MessageBox( 0, 0, propertydata, 0 );
			return;
		}
		ostringstream oss;
		string str;

		//文字列ストリームにファイルの内容を出力
		oss << ifs.rdbuf();
		str = oss.str();

		iss = istringstream( str );	// create string stream of memory contents	// NOTE: this ends up copying the buffer!!!
	}

	string str;
	vector<vector<string>> table;
	istringstream* pUseIss = &iss;
	if( pIss ){
		pUseIss = pIss;
	}
	while( getline( *pUseIss, str ) ){	//一行ずつ文字列を読み込み、区切り文字で分けてリストに追加する
		
		if( str.find_last_not_of("\r") != string::npos ){
			str.erase( str.find_last_not_of("\r")+1 );	//改行ｺｰﾄﾞ削除
		}else{
			break;
		}

		vector<string> record;					// １行分の文字列のリスト
		istringstream streambuffer( str );		// 文字列ストリーム
		string token;							// １セル分の文字列
		if( table.empty() ){
			while( getline( streambuffer, token, ',' ) ){
				record.push_back( token );	// １セル分の文字列をリストに追加する
			}
		}else{
			record.resize( table[0].size() );
			for( int i=0 ; i<record.size() ; i++ ){
				if( !getline( streambuffer, token, ',' ) ){
					//break;
				}
				record[i] = token;	// １セル分の文字列をリストに追加する
			}
			if( record[1].empty() || record[1] == ""  || ( record[1][0] == 0 && record[1][1] == 0 && record[1][2] == 0 ) ){	//モーション名がなければデータなしとみなす
				continue;	//while
			}
		}
		
		table.push_back( record );	// １行分の文字列を出力引数のリストに追加する
	}


	for( int i=1 ; i<table.size() ; i++ ){	//一行目は説明なので飛ばす
		if( table[i].empty() || ( table[i].size() < 3 ) ){
			continue;
		}

		if( !table[i][1].empty() ){	//IDが空
			ChainProperty tmp;
			string search_str;	//文字列検索用
			unsigned int loc;	//文字列検索用

			//frame
			tmp.frame = atoi( table[i][1].c_str() );

			//ID
			tmp.id = atoi( table[i][2].c_str() );
			//group
			tmp.group = atoi( table[i][3].c_str() );
			//開始モーション名
			tmp.start_motion_name = table[i][4];
			//成立状態
			for( int j=0 ; j<COMMAND_SUCCESS_STATE_MAX ; j++ ){
				tmp.success_state = COMMAND_SUCCESS_STATE_MAX;
				if( j == 0 )search_str = "GROUND";
				if( j == 1 )search_str = "AIR";
				if( j == 2 )search_str = "LOCK";
				if( table[i][5] == search_str ){
					tmp.success_state = (COMMAND_SUCCESS_STATE)j;
					break;
				}
			}

			//コマンド
			for( int j=0 ; j<6 ; j++ ){
				ChainParts tmp2;
				string strtmp0 = table[i][6+ 5*j + 0];
				string strtmp1 = table[i][6+ 5*j + 1];
				string strtmp2 = table[i][6+ 5*j + 2];

				string strtmp3 = table[i][6+ 5*j + 3];
				string strtmp4 = table[i][6+ 5*j + 4];


				if( strtmp0.empty() && strtmp1.empty() && strtmp2.empty() ){	//3つのセルが空
					goto PARTS_PUSH_BACK_LABEL;
				}else{
					tmp2.empty_flg = false;	//空のデータではない
				}
				//======================= レバー、兼コード指定 =======================
				if( !strtmp0.empty() ){		//レバー、兼コード指定
					if( strtmp0 == "END" ){	//終了指定
						//break;
						tmp2.end_flg = true;
						goto PARTS_PUSH_BACK_LABEL;
					}else if( strtmp0 == "SKIP" ){	//スキップ指定
						tmp2.skip_chain_route_id	= atoi( strtmp1.c_str() );
						tmp2.skip_chain_count		= atoi( strtmp2.c_str() );
						goto PARTS_PUSH_BACK_LABEL;
					}else if( strtmp0 == "INC" ){	//カウントをインクリメントする　派生したくないときに使う
						tmp2.skip_chain_count++;
						goto PARTS_PUSH_BACK_LABEL;
					}else{
						tmp2.SetChainLever( strtmp0 );	//レバー指定
					}
				}

				//======================= ボタン、兼指定子第一引数 =======================
				if( !strtmp1.empty() ){		//ボタン、兼指定子第一引数
					if(0){
					}else{
						tmp2.SetChainButton( strtmp1 );
					}
				}

				//======================= モーション名、兼指定子第二引数 =======================
				if( !strtmp2.empty() ){		//モーション名、兼指定子第二引数
					if(0){
					}else{
						tmp2.success_motion_name = strtmp2;
					}
				}



				//======================= 開始F =======================
				if( !strtmp3.empty() ){
					if(0){
						tmp2.start_frame = -1;
					}else{
						tmp2.start_frame = atoi( strtmp3.c_str() );
					}
				}

				//======================= 終了F =======================
				if( !strtmp4.empty() ){
					if(0){
						tmp2.end_frame = -1;
					}else{
						tmp2.end_frame = atoi( strtmp4.c_str() );
					}
				}


				
				//======================= パーツ追加 =======================
PARTS_PUSH_BACK_LABEL:
				tmp.parts.push_back( tmp2 );
			}

			//追加
			chaindata.push_back( tmp );
		}
	}

}

void Chain::DataLoadFromFileInMemory( char propertydata[64], CArchive* pArchive ){
	if( !pArchive ){
		MessageBox( 0, 0, "アーカイブファイルが読み込まれていません", 0 );
		return;
	}

	int inMemoryFileSize = 0;
	char* inMemoryFilePointer = NULL;
	pArchive->GetFileSizeAndPointer( propertydata, &inMemoryFileSize, &inMemoryFilePointer );

	string s( inMemoryFilePointer, ( inMemoryFilePointer + inMemoryFileSize ) );
	istringstream iss( s );

	DataLoad( propertydata, &iss );
}


void ChainParts::SetChainButton( string parts ){
	button_empty_flg = false;
	//buttonの型はCommandAllButtonなので細かい指定が可能
	//攻撃ボタン
	if( parts == "A" ){
		button.flag[BUTTON_ATTACK1] = true;
		return;
	}
	if( parts == "B" ){
		button.flag[BUTTON_ATTACK2] = true;
		return;
	}
	if( parts == "C" ){
		button.flag[BUTTON_ATTACK3] = true;
		return;
	}
	if( parts == "D" ){
		button.flag[BUTTON_ATTACK4] = true;
		return;
	}
	if( parts == "E" ){
		button.flag[BUTTON_ATTACK5] = true;
		return;
	}
	if( parts == "F" ){
		button.flag[BUTTON_ATTACK6] = true;
		return;
	}

	//横２P
	if( parts == "AB" ){
		button.flag[BUTTON_ATTACK1] = true;
		button.flag[BUTTON_ATTACK2] = true;
		button.multi_push = true;
		return;
	}
	if( parts == "BC" ){
		button.flag[BUTTON_ATTACK2] = true;
		button.flag[BUTTON_ATTACK3] = true;
		button.multi_push = true;
		return;
	}
	//横２K
	if( parts == "DE" ){
		button.flag[BUTTON_ATTACK4] = true;
		button.flag[BUTTON_ATTACK5] = true;
		button.multi_push = true;
		return;
	}
	if( parts == "EF" ){
		button.flag[BUTTON_ATTACK5] = true;
		button.flag[BUTTON_ATTACK6] = true;
		button.multi_push = true;
		return;
	}

	//縦２
	if( parts == "AD" ){
		button.flag[BUTTON_ATTACK1] = true;
		button.flag[BUTTON_ATTACK4] = true;
		button.multi_push = true;
		return;
	}
	if( parts == "BE" ){
		button.flag[BUTTON_ATTACK2] = true;
		button.flag[BUTTON_ATTACK5] = true;
		button.multi_push = true;
		return;
	}
	if( parts == "CF" ){
		button.flag[BUTTON_ATTACK3] = true;
		button.flag[BUTTON_ATTACK6] = true;
		button.multi_push = true;
		return;
	}

	//横３
	if( parts == "ABC" ){
		button.flag[BUTTON_ATTACK1] = true;
		button.flag[BUTTON_ATTACK2] = true;
		button.flag[BUTTON_ATTACK3] = true;
		button.multi_push = true;
		return;
	}
	if( parts == "DEF" ){
		button.flag[BUTTON_ATTACK4] = true;
		button.flag[BUTTON_ATTACK5] = true;
		button.flag[BUTTON_ATTACK6] = true;
		button.multi_push = true;
		return;
	}

	//攻撃ボタン要素
	if( parts == "ATK_P" ){
		button.flag[BUTTON_ATTACK1] = true;
		button.flag[BUTTON_ATTACK2] = true;
		button.flag[BUTTON_ATTACK3] = true;
		button.any_attack = true;
		return;
	}
	if( parts == "ATK_K" ){
		button.flag[BUTTON_ATTACK4] = true;
		button.flag[BUTTON_ATTACK5] = true;
		button.flag[BUTTON_ATTACK6] = true;
		button.any_attack = true;
		return;
	}


	//オート
	if( parts == "AUTO" ){
		return;
	}

	button_empty_flg = true;
}

void ChainParts::SetChainLever( string parts ){
	lever_empty_flg = false;
	//buttonの型はCommandAllButtonなので細かい指定が可能
	//レバー要素
	if( parts == "LU" ){
		button.lever_youso = true;
		button.flag[LEVER_UP] = true;
		return;
	}
	if( parts == "LD" ){
		button.lever_youso = true;
		button.flag[LEVER_DOWN] = true;
		return;
	}
	if( parts == "LL" ){
		button.lever_youso = true;
		button.flag[LEVER_LEFT] = true;
		return;
	}
	if( parts == "LR" ){
		button.lever_youso = true;
		button.flag[LEVER_RIGHT] = true;
		return;
	}

	//レバー
	{
		int lever = atoi( parts.c_str() );
		switch( lever ){
		case 1:
			button.flag[LEVER_DOWN] = true;
			button.flag[LEVER_LEFT] = true;
			return;
		case 2:
			button.flag[LEVER_DOWN] = true;
			return;
		case 3:
			button.flag[LEVER_DOWN] = true;
			button.flag[LEVER_RIGHT] = true;
			return;
		case 4:
			button.flag[LEVER_LEFT] = true;
			return;
		case 5:
			return;
		case 6:
			button.flag[LEVER_RIGHT] = true;
			return;
		case 7:
			button.flag[LEVER_UP] = true;
			button.flag[LEVER_LEFT] = true;
			return;
		case 8:
			button.flag[LEVER_UP] = true;
			return;
		case 9:
			button.flag[LEVER_UP] = true;
			button.flag[LEVER_RIGHT] = true;
			return;
		}
	}

	lever_empty_flg = true;
}



void Chain::SetChainRoute( string* motion_name ){
	if( chain_count > 0 ){
		return;		//チェーンの最中なので再設定はできない　即抜ける
	}

	for( int i=0 ; i<chaindata.size() ; i++ ){
		if( chaindata[i].start_motion_name == (*motion_name) ){	//開始モーションと一致
			chain_route_id = i;
			chain_count = 0;
			chainname = NULL;
			break;
		}
	}
}

void Chain::ChainEnd(){
	chain_route_id = INVALID_VAL;
	chain_count = INVALID_VAL;
	chainname = NULL;
}

void Chain::ChainSkip( int skipID, int skipCount ){
	ChainEnd();		//一旦クリア
	chain_route_id = skipID;
	chain_count = skipCount;
}

void Chain::ChainCountInc(){
	chainname = NULL;

	////終了
	//if( chaindata[chain_route_id].parts[chain_count].end_flg ){
	//	ChainEnd();
	//	return;
	//}

	chain_count++;
}

void Chain::InputStatus( BUTTON button, int* pMultipush, string* motion_name, int fgtFrame, bool hitFlg, float y_pos ){
	BUTTON button_save = button;
	if( chara_direction == DIRECTION_RIGHT ){	//左向きの時コマンドの右と左を反転
		button.press.flag[LEVER_LEFT]	= button_save.press.flag[LEVER_RIGHT];
		button.push.flag[LEVER_LEFT]	= button_save.push.flag[LEVER_RIGHT];
		button.press.flag[LEVER_RIGHT]	= button_save.press.flag[LEVER_LEFT];
		button.push.flag[LEVER_RIGHT]	= button_save.push.flag[LEVER_LEFT];
	}

	if( chain_route_id == INVALID_VAL )return;
	if( chain_count == INVALID_VAL )return;

	if( chain_count == 0 ){
		if( chaindata[chain_route_id].start_motion_name != (*motion_name) ){	//キャラのモーションとチェーン開始モーション名が違う
			//return;
		}
	}else if( chain_count > 0 ){
		if( chaindata[chain_route_id].parts[chain_count-1].success_motion_name != (*motion_name) ){	//キャラのモーションと一つ前のチェーンモーション名が違う
			//return;
		}
	}

	//チェーンスキップ
	int ID = chaindata[chain_route_id].parts[chain_count].skip_chain_route_id;
	int Count = chaindata[chain_route_id].parts[chain_count].skip_chain_count;
	if( ID != INVALID_VAL && Count != INVALID_VAL ){
		ChainSkip( ID, Count );
		return;
	}

	if( chaindata[chain_route_id].parts[chain_count].end_flg ){	//現在指定中のチェーンIDの次のパーツがEND指定のときはこれ以上進めないし派生できない
		return;
	}


	//次のパーツが成立しているか調べる（派生を含む
	int group_no = chaindata[chain_route_id].group;	//グループ番号
	for( int i=0 ; i<chaindata.size() ; i++ ){	//同じグループ番号のデータがあるか総当たりで調べる
		
		if( chaindata[i].group == group_no ){		//グループ番号が一致

			////ベクタの要素数を越えた　配列外を参照してはいけないので最優先
			//if( chaindata[i].parts.size() >= chain_count ){
			//	continue;
			//}


			//空白のデータである
			if( chaindata[i].parts[chain_count].empty_flg ){
				continue;
			}

			//終了データである
			if( chaindata[i].parts[chain_count].end_flg ){
				continue;
			}

			//成立状態判定
			switch( chaindata[i].success_state ){
			case COMMAND_SUCCESS_STATE_GROUND:	//地上しか出せない
				if( y_pos > ground ){
					continue;
				}
				break;
			case COMMAND_SUCCESS_STATE_AIR:		//空中しか出せない
				if( y_pos <= ground ){
					continue;
				}
				break;
			case COMMAND_SUCCESS_STATE_LOCK:	//デバッグ用　ロック
				continue;
				break;
			}

			//レバー＆ボタン判定
			if( !CommandCheck( button, chaindata[i].parts[chain_count].button, pMultipush ) ){
				continue;
			}

			if( fgtFrame < 2 ){
				continue;
			}
			if( chaindata[i].id >= 200 ){
				//空チェーン可能
			}else{
				if( !hitFlg ){
					continue;
				}
			}

			//ここまできたら成立
			chainname = &chaindata[i].parts[chain_count].success_motion_name;
			chain_route_id = i;		//チェーンID更新
			//chain_count++;	//チェーンカウントは呼び出し側で本当に成立したか確認した後に進める
			break;		//見つけ次第抜ける
		}
	}

}

bool Chain::CommandCheck( BUTTON button, CommandAllButton chain_button, int* multipush_count ){

	for( int i=0 ; i<INPUT_LABEL_ALL ; i++ ){
		if( i <= LEVER_RIGHT ){
			//レバー
			if( chaindata[chain_route_id].parts[chain_count].lever_empty_flg ){	//レバー空のときは通す
				continue;
			}
			if( chain_button.lever_youso ){
				//要素（UDLR）のとき
				if( chain_button.flag[i] ){	//trueのときのみ
					if( button.press.flag[i] != chain_button.flag[i] ){
						return false;
					}
				}
			}else{
				//絶対入力（123...）のとき
				if( chain_button.flag[i] != button.press.flag[i] ){
					return false;
				}
			}
		}else{
			
			//ボタン
			if( chain_button.any_attack ){
				//どれでもOK
				if( chain_button.flag[BUTTON_ATTACK1] ){	//必要な入力 P
					if( multipush_count[BUTTON_ATTACK1] <= 0 && multipush_count[BUTTON_ATTACK2] <= 0 && multipush_count[BUTTON_ATTACK3] <= 0 ){ 	//猶予
					//if( !button.push.flag[BUTTON_ATTACK1] && !button.push.flag[BUTTON_ATTACK2] && !button.push.flag[BUTTON_ATTACK3] ){	//猶予無し版
						return false;	//何も押されていなければ失敗
					}
				}
				if( chain_button.flag[BUTTON_ATTACK4] ){	//必要な入力 K
					if( multipush_count[BUTTON_ATTACK4] <= 0 && multipush_count[BUTTON_ATTACK5] <= 0 && multipush_count[BUTTON_ATTACK6] <= 0 ){ 
					//if( !button.push.flag[BUTTON_ATTACK4] && !button.push.flag[BUTTON_ATTACK5] && !button.push.flag[BUTTON_ATTACK6] ){
						return false;	//何も押されていなければ失敗
					}
				}
			}else if( chain_button.multi_push ){
				//同時押し用
				if( chain_button.flag[i] ){	//必要なボタンのみ見る
					if( multipush_count[i] <= 0 ){	//押されてからの猶予はあるか？
						return false;	//必要なボタンの猶予がなかったので失敗
					}
				}
			}else{
				//普通の指定
				if( chain_button.flag[i] ){	//必要な入力
					if( multipush_count[i] <= 0 ){	//猶予
						return false;
					}

					/*if( button.push.flag[i] != chain_button.flag[i] ){	//猶予無し版
						return false;
					}*/
				}
			}
		}
	}

	return true;
}


