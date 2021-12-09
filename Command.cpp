#include "Command.h"
#include "..\..\Engine\LoadingLog.h"


CommandParts::CommandParts( string con_command, int receptiontime, int validtime, COMMAND_SUCCESS_STATE successstate ){
	CommandSet( con_command, receptiontime, validtime, successstate );
}

void CommandParts::CommandSet( string con_command, int receptiontime, int validtime, COMMAND_SUCCESS_STATE successstate ){
	command				= con_command;
	reception_time		= receptiontime;
	valid_time			= validtime;
	success_state		= successstate;
	valid_count			= 0;
	//variation = 引数でキャラの情報を持ってくる

	//アンダーバー区切り
	char delim = ',';
	size_t current = 0, found;
	while( (found = command.find_first_of( delim, current )) != string::npos ){
		commandArray_string.push_back( string( command, current, found - current ) );
		current = found + 1;
	}


	//区切った文字をALL_INPUTに変換
	for( int i=0 ; i<commandArray_string.size() ; i++ ){
		const string parts = commandArray_string[i];
		CommandAllButton button;	//毎回初期化

		//攻撃ボタン
		if( parts == "A" ){
			button.flag[BUTTON_ATTACK1] = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "B" ){
			button.flag[BUTTON_ATTACK2] = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "C" ){
			button.flag[BUTTON_ATTACK3] = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "D" ){
			button.flag[BUTTON_ATTACK4] = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "E" ){
			button.flag[BUTTON_ATTACK5] = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "F" ){
			button.flag[BUTTON_ATTACK6] = true;
			commandArray.push_back( button );
			continue;
		}

		//横同時押し
		if( parts == "AB" ){
			button.flag[BUTTON_ATTACK1] = true;
			button.flag[BUTTON_ATTACK2] = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "BC" ){
			button.flag[BUTTON_ATTACK2] = true;
			button.flag[BUTTON_ATTACK3] = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "AC" ){
			button.flag[BUTTON_ATTACK1] = true;
			button.flag[BUTTON_ATTACK3] = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "ABC" ){
			button.flag[BUTTON_ATTACK1] = true;
			button.flag[BUTTON_ATTACK2] = true;
			button.flag[BUTTON_ATTACK3] = true;
			commandArray.push_back( button );
			continue;
		}

		if( parts == "DE" ){
			button.flag[BUTTON_ATTACK4] = true;
			button.flag[BUTTON_ATTACK5] = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "EF" ){
			button.flag[BUTTON_ATTACK5] = true;
			button.flag[BUTTON_ATTACK6] = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "DF" ){
			button.flag[BUTTON_ATTACK4] = true;
			button.flag[BUTTON_ATTACK6] = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "DEF" ){
			button.flag[BUTTON_ATTACK4] = true;
			button.flag[BUTTON_ATTACK5] = true;
			button.flag[BUTTON_ATTACK6] = true;
			commandArray.push_back( button );
			continue;
		}
		//縦同時押し
		if( parts == "AD" ){
			button.flag[BUTTON_ATTACK1] = true;
			button.flag[BUTTON_ATTACK4] = true;
			button.multi_push = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "BE" ){
			button.flag[BUTTON_ATTACK2] = true;
			button.flag[BUTTON_ATTACK5] = true;
			button.multi_push = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "CF" ){
			button.flag[BUTTON_ATTACK3] = true;
			button.flag[BUTTON_ATTACK6] = true;
			button.multi_push = true;
			commandArray.push_back( button );
			continue;
		}
		
		//ATK
		if( parts == "ATK_P" ){	//P攻撃どれか
			button.flag[BUTTON_ATTACK1] = true;
			button.flag[BUTTON_ATTACK2] = true;
			button.flag[BUTTON_ATTACK3] = true;
			button.any_attack = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "ATK_K" ){	//K攻撃どれか
			button.flag[BUTTON_ATTACK4] = true;
			button.flag[BUTTON_ATTACK5] = true;
			button.flag[BUTTON_ATTACK6] = true;
			button.any_attack = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "ATK" ){	//攻撃どれか
			button.flag[BUTTON_ATTACK1] = true;
			button.flag[BUTTON_ATTACK2] = true;
			button.flag[BUTTON_ATTACK3] = true;
			button.flag[BUTTON_ATTACK4] = true;
			button.flag[BUTTON_ATTACK5] = true;
			button.flag[BUTTON_ATTACK6] = true;
			button.any_attack = true;
			commandArray.push_back( button );
			continue;
		}

		//ATK_DOUBLE
		if( parts == "ATK_PP" ){	//PP
			button.flag[BUTTON_ATTACK1] = true;
			button.flag[BUTTON_ATTACK2] = true;
			button.flag[BUTTON_ATTACK3] = true;
			button.any_attack_double = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "ATK_KK" ){	//KK
			button.flag[BUTTON_ATTACK4] = true;
			button.flag[BUTTON_ATTACK5] = true;
			button.flag[BUTTON_ATTACK6] = true;
			button.any_attack_double = true;
			commandArray.push_back( button );
			continue;
		}

		//ATK_TRIPLE
		if( parts == "ATK_PPP" ){	//PPP
			button.flag[BUTTON_ATTACK1] = true;
			button.flag[BUTTON_ATTACK2] = true;
			button.flag[BUTTON_ATTACK3] = true;
			button.any_attack_triple = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "ATK_KKK" ){	//KKK
			button.flag[BUTTON_ATTACK4] = true;
			button.flag[BUTTON_ATTACK5] = true;
			button.flag[BUTTON_ATTACK6] = true;
			button.any_attack_triple = true;
			commandArray.push_back( button );
			continue;
		}

		//攻撃ボタン　離したとき
		if( parts == "!A" ){
			button.flag[BUTTON_ATTACK1] = true;
			button.release = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!B" ){
			button.flag[BUTTON_ATTACK2] = true;
			button.release = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!C" ){
			button.flag[BUTTON_ATTACK3] = true;
			button.release = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!D" ){
			button.flag[BUTTON_ATTACK4] = true;
			button.release = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!E" ){
			button.flag[BUTTON_ATTACK5] = true;
			button.release = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!F" ){
			button.flag[BUTTON_ATTACK6] = true;
			button.release = true;
			commandArray.push_back( button );
			continue;
		}
		//P離
		if( parts == "!AB" ){
			button.flag[BUTTON_ATTACK1] = true;
			button.flag[BUTTON_ATTACK2] = true;
			button.release = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!BC" ){
			button.flag[BUTTON_ATTACK2] = true;
			button.flag[BUTTON_ATTACK3] = true;
			button.release = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!AC" ){
			button.flag[BUTTON_ATTACK1] = true;
			button.flag[BUTTON_ATTACK3] = true;
			button.release = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!P" ){
			button.flag[BUTTON_ATTACK1] = true;
			button.flag[BUTTON_ATTACK2] = true;
			button.flag[BUTTON_ATTACK3] = true;
			button.release = true;
			button.any_attack = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!PP" ){
			button.flag[BUTTON_ATTACK1] = true;
			button.flag[BUTTON_ATTACK2] = true;
			button.flag[BUTTON_ATTACK3] = true;
			button.release = true;
			button.any_attack_double = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!PPP" ){
			button.flag[BUTTON_ATTACK1] = true;
			button.flag[BUTTON_ATTACK2] = true;
			button.flag[BUTTON_ATTACK3] = true;
			button.release = true;
			button.any_attack_triple = true;
			commandArray.push_back( button );
			continue;
		}
		//K離
		if( parts == "!DE" ){
			button.flag[BUTTON_ATTACK4] = true;
			button.flag[BUTTON_ATTACK5] = true;
			button.release = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!EF" ){
			button.flag[BUTTON_ATTACK5] = true;
			button.flag[BUTTON_ATTACK6] = true;
			button.release = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!DF" ){
			button.flag[BUTTON_ATTACK4] = true;
			button.flag[BUTTON_ATTACK6] = true;
			button.release = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!K" ){
			button.flag[BUTTON_ATTACK4] = true;
			button.flag[BUTTON_ATTACK5] = true;
			button.flag[BUTTON_ATTACK6] = true;
			button.release = true;
			button.any_attack = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!KK" ){
			button.flag[BUTTON_ATTACK4] = true;
			button.flag[BUTTON_ATTACK5] = true;
			button.flag[BUTTON_ATTACK6] = true;
			button.release = true;
			button.any_attack_double = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "!KKK" ){
			button.flag[BUTTON_ATTACK4] = true;
			button.flag[BUTTON_ATTACK5] = true;
			button.flag[BUTTON_ATTACK6] = true;
			button.release = true;
			button.any_attack_triple = true;
			commandArray.push_back( button );
			continue;
		}

		//溜め
		if( parts == "T" ){
			button.tame = true;
			commandArray.push_back( button );
			continue;
		}

		//レバー要素
		if( parts == "LU" ){
			button.lever_youso = true;
			button.flag[LEVER_UP] = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "LD" ){
			button.lever_youso = true;
			button.flag[LEVER_DOWN] = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "LL" ){
			button.lever_youso = true;
			button.flag[LEVER_LEFT] = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "LR" ){
			button.lever_youso = true;
			button.flag[LEVER_RIGHT] = true;
			commandArray.push_back( button );
			continue;
		}
		

		//レバー
		{
			int lever = atoi( parts.c_str() );
			switch(lever){
			case 1:
				button.flag[LEVER_DOWN] = true;
				button.flag[LEVER_LEFT] = true;
				break;
			case 2:
				button.flag[LEVER_DOWN] = true;
				break;
			case 3:
				button.flag[LEVER_DOWN] = true;
				button.flag[LEVER_RIGHT] = true;
				break;
			case 4:
				button.flag[LEVER_LEFT] = true;
				break;
			case 5:
				break;
			case 6:
				button.flag[LEVER_RIGHT] = true;
				break;
			case 7:
				button.flag[LEVER_UP] = true;
				button.flag[LEVER_LEFT] = true;
				break;
			case 8:
				button.flag[LEVER_UP] = true;
				break;
			case 9:
				button.flag[LEVER_UP] = true;
				button.flag[LEVER_RIGHT] = true;
				break;
			}
			commandArray.push_back( button );
			continue;
		}

	}
}


bool CommandParts::CheckCommand( vector<ALL_INPUT>* buffer, Tame* tame, COMMAND_STRENGTH_CHECK* strength_check, int y_pos, int dy ){
	int commandIndex = 0;	//コマンド内を参照するためのインデックス
	int bufferIndex = 0;	//受け取ったバッファ内を参照するためのインデックス

	ALL_INPUT parts_success_input = ALL_INPUT();	//パーツが成功したときの入力
	bool parts_success_input_change = true;		//成功したときの入力が変わったか？

	CommandAllButton* check = NULL;		//チェックするコマンドを一時的に格納する

	COMMAND_STRENGTH_CHECK st_check_buf = COMMAND_STRENGTH_CHECK_MAX;	//成立時に代入するまで保持


	//コマンドが成立するか、コマンド入力受付限界まで、バッファとコマンドを比べる
	while( ( bufferIndex < reception_time ) && ( commandIndex < buffer->size() ) ){


		int commandlength = commandArray.size();	//ｺﾏﾝﾄﾞの文字数
		check = &commandArray[commandlength-commandIndex-1];
		
		//コマンドと入力を見比べる
		if( bufferIndex < buffer->size() ){
			int bufferlength = buffer->size();
			ALL_INPUT* pointer = (ALL_INPUT*)&(buffer->at(0));	//ﾊﾞｯﾌｧの先頭アドレス
			if( !parts_success_input.lever_match( pointer[bufferlength-bufferIndex-1] ) ){
				parts_success_input_change = true;
			}


			bool lever_match = false;
			bool button_match = false;
			if( !check->tame ){
				if( check->flag[BUTTON_ATTACK1] || check->flag[BUTTON_ATTACK2] || check->flag[BUTTON_ATTACK3] || check->flag[BUTTON_ATTACK4] || check->flag[BUTTON_ATTACK5] || check->flag[BUTTON_ATTACK6] ){		//攻撃ボタン要素があるか？
					if( check->release ){
						int any_need_count = 0;	//必要数
						if( check->any_attack )any_need_count = 1;
						else if( check->any_attack_double )any_need_count = 2;
						else if( check->any_attack_triple )any_need_count = 3;

						if( any_need_count > 0 ){
							int find_count = 0;
							for( int i=INPUT_LABEL::BUTTON_ATTACK1 ; i<=INPUT_LABEL::BUTTON_ATTACK6 ; i++ ){
								if( check->flag[i] ){
									if( check->flag[i] != pointer[bufferlength-bufferIndex-1].flag[i] ){
										find_count++;
									}
								}
							}
							if( find_count > any_need_count ){
								button_match = true;
							}
						}else{
							//ボタン不一致時true
							if( check->flag[BUTTON_ATTACK1] != pointer[bufferlength-bufferIndex-1].flag[BUTTON_ATTACK1] ||
								check->flag[BUTTON_ATTACK2] != pointer[bufferlength-bufferIndex-1].flag[BUTTON_ATTACK2] ||
								check->flag[BUTTON_ATTACK3] != pointer[bufferlength-bufferIndex-1].flag[BUTTON_ATTACK3] ||
								check->flag[BUTTON_ATTACK4] != pointer[bufferlength-bufferIndex-1].flag[BUTTON_ATTACK4] ||
								check->flag[BUTTON_ATTACK5] != pointer[bufferlength-bufferIndex-1].flag[BUTTON_ATTACK5] ||
								check->flag[BUTTON_ATTACK6] != pointer[bufferlength-bufferIndex-1].flag[BUTTON_ATTACK6] ){
									button_match = true;
							}
						}
					}else if( check->any_attack || check->any_attack_double || check->any_attack_triple ){
						//必要数
						int need_count = 1;
						if( check->any_attack_double )need_count = 2;
						if( check->any_attack_triple )need_count = 3;
						
						//押されているボタン数
						int checkcount = 0;
						for( int i=INPUT_LABEL::BUTTON_ATTACK1 ; i<=INPUT_LABEL::BUTTON_ATTACK6 ; i++ ){
							if( pointer[bufferlength-bufferIndex-1].flag[i] ){
								if( check->flag[i] ){
									checkcount++;
									if( checkcount >= need_count ){	//同じモーションで分ける用
										if( i == BUTTON_ATTACK1 )st_check_buf = COMMAND_STRENGTH_CHECK_L;
										if( i == BUTTON_ATTACK2 )st_check_buf = COMMAND_STRENGTH_CHECK_M;
										if( i == BUTTON_ATTACK3 )st_check_buf = COMMAND_STRENGTH_CHECK_H;
										if( i == BUTTON_ATTACK4 )st_check_buf = COMMAND_STRENGTH_CHECK_L;
										if( i == BUTTON_ATTACK5 )st_check_buf = COMMAND_STRENGTH_CHECK_M;
										if( i == BUTTON_ATTACK6 )st_check_buf = COMMAND_STRENGTH_CHECK_H;
									}
								}
							}
						}
						//チェック
						if( need_count > 0 && checkcount >= need_count ){
							button_match = true;
						}
					}else{
						//必要数
						int need_count = 0;
						for( int i=INPUT_LABEL::BUTTON_ATTACK1 ; i<=INPUT_LABEL::BUTTON_ATTACK6 ; i++ ){
							if( check->flag[i] ){
								need_count++;
							}
						}
						//押されているボタン数
						int checkcount = 0;
						for( int i=INPUT_LABEL::BUTTON_ATTACK1 ; i<=INPUT_LABEL::BUTTON_ATTACK6 ; i++ ){
							if( pointer[bufferlength-bufferIndex-1].flag[i] ){
								if( check->flag[i] ){
									checkcount++;
								}
							}
						}
						//チェック
						if( need_count > 0 && checkcount >= need_count ){
							button_match = true;
							//if( check->flag[BUTTON_ATTACK1] && check->flag[BUTTON_ATTACK2] ){	//EX技　絶対問題あるので直す
							if( need_count >= 2 ){	//大丈夫？
								*strength_check = COMMAND_STRENGTH_CHECK_EX;
							}
						}
					}
				}else{
					if( !check->lever_youso ){
						//レバー全一致判定
						if( ( check->flag[LEVER_UP] == pointer[bufferlength-bufferIndex-1].flag[LEVER_UP] ) &&
							( check->flag[LEVER_DOWN] == pointer[bufferlength-bufferIndex-1].flag[LEVER_DOWN] ) && 
							( check->flag[LEVER_LEFT] == pointer[bufferlength-bufferIndex-1].flag[LEVER_LEFT] ) && 
							( check->flag[LEVER_RIGHT] == pointer[bufferlength-bufferIndex-1].flag[LEVER_RIGHT] ) ){
								lever_match = true;
						}
					}else{
						//レバー要素含み判定
						if( ( check->flag[LEVER_UP] && pointer[bufferlength-bufferIndex-1].flag[LEVER_UP] ) ||
							( check->flag[LEVER_DOWN] && pointer[bufferlength-bufferIndex-1].flag[LEVER_DOWN] ) || 
							( check->flag[LEVER_LEFT] && pointer[bufferlength-bufferIndex-1].flag[LEVER_LEFT] ) || 
							( check->flag[LEVER_RIGHT] && pointer[bufferlength-bufferIndex-1].flag[LEVER_RIGHT] ) ){
								lever_match = true;
						}
					}
				}
			}

			if( parts_success_input_change ){
				if( lever_match ){
					//一緒だったら、次の入力を調べるためにインデックスを加算
					parts_success_input = pointer[bufferlength-bufferIndex-1];
					parts_success_input_change = false;

					//bufferIndex++;
					commandIndex++;
					if( commandIndex >= commandArray.size() ){
						break;	//成立！
					}
					continue;
				}
			}
			if( button_match ){
				//一緒だったら、次の入力を調べるためにインデックスを加算
				parts_success_input = pointer[bufferlength-bufferIndex-1];
				parts_success_input_change = true;

				//bufferIndex++;
				commandIndex++;
				if( commandIndex >= commandArray.size() ){
					break;	//成立！
				}
				continue;
			}


			//溜めチェック
			if( check->tame ){
				//Tの前の文字が溜めフレーム分入力されているか　例：4T6aなら4
				int tame_F = reception_time;		//溜めコマンドは入力猶予を使う　4溜め後即6じゃないと出ないので+5
				
				//必要数
				int need_tame = 0;
				for( int i=0 ; i<INPUT_LABEL_ALL ; i++ ){
					if( commandArray[commandlength-commandIndex-2].flag[i] ){
						need_tame++;
					}
				}
				if( commandArray[commandlength-commandIndex-2].any_attack )need_tame = 1;
				else if( commandArray[commandlength-commandIndex-2].any_attack_double )need_tame = 2;
				else if( commandArray[commandlength-commandIndex-2].any_attack_triple )need_tame = 3;
				
				//ため成功カウント
				int tame_OK = 0;
				for( int i=0 ; i<INPUT_LABEL_ALL ; i++ ){
					if( CheckTame( commandArray[commandlength-commandIndex-2].flag[i], tame->count_tame[i][1], tame_F ) ){
						tame_OK++;
					}
				}
			
				if( tame_OK > 0 && tame_OK >= need_tame ){
					//bufferIndex++;
					commandIndex += 2;	//'T'のぶんも
					if( commandIndex >= commandArray.size() ){
						break;	//成立！ whileを抜ける
					}
				}else{
					break;	//whileを抜ける
				}
			}
		}
		
		//バッファの次の場所を調べるためにインデックスを加算
		bufferIndex++;
	}

	//コマンドのインデックスが、コマンド配列の長さと等しかったらコマンドが成立した事になる
	if( commandIndex == commandArray.size() ){
		//if( 
		//	valid_count == 0 ||
		//	( !command_success_key_save.match( parts_success_input ) )
		//	){
		//	valid_count = 1;
		//	command_success_key_save = parts_success_input;		//入力を保存しておく
		//}
		//成立有効時間中にコマンドがもう一度成立した時はvalid_countをリセットしたい


		if( bufferIndex <= success_bufferIndex_save ){
			valid_count = 0;
		}


		if( valid_count > valid_time ){	//コマンド成立後の有効時間をチェック
			return false;
		}

		//地空をここで判定すると、コマンド入力が成立したときの状態で成功/失敗を判定してしまう
		//switch(success_state){
		//case COMMAND_SUCCESS_STATE_GROUND:	//地上しか出せない
		//	if(y_pos + dy > ground)return false;
		//	break;
		//case COMMAND_SUCCESS_STATE_AIR:		//空中しか出せない
		//	if(y_pos <= ground)return false;
		//	break;
		//case COMMAND_SUCCESS_STATE_LOCK:	//デバッグ用　ロック
		//	return false;
		//	break;
		//}
		valid_count++;

		if( commandArray[commandIndex-1].any_attack ){
			*strength_check = st_check_buf;
		}


		success_bufferIndex_save = bufferIndex;

		//コマンドが成立していたら、true を返す
		return true;
	}
	valid_count = success_bufferIndex_save = 0;	//念為
	return false;
}

bool CommandParts::CheckTame( bool check_btn, int tame_time, int need_tame ){
	if( check_btn ){
		if( tame_time >= need_tame ){
			return true;
		}
	}
	return false;
}



CommandParts Command::CommandPushBack( string com, int receptiontime, int validtime, COMMAND_SUCCESS_STATE successstate ){
	CommandParts skl;
	skl.CommandSet( com, receptiontime, validtime, successstate );
	skillcommand.push_back( skl );
	return skl;
}



Command::Command(){
	Reset();
}
void Command::Reset(){
	commandproperty.clear();

	for( int i=0 ; i<INPUT_LABEL_ALL ; i++ ){
		multipush_count[i] = 0;
	}
	for( int i=0 ; i<COMMAND_CHARAFLAG_MAX ; i++ ){
		chara_flag[i] = false;
	}
	for( int i=0 ; i<COMMAND_SUCCESS_MOTION_NAME_ALL ; i++ ){
		commandpriority[i] = 0;
		commandname[i] = NULL;

		for( int j=0 ; j<INPUT_LABEL_ALL ; j++ ){
			success_button[i] = CommandAllButton();
		}
	}
	vTrg_flag = cancelOnly_flag = false;

	command_buffer.clear();
	command_buffer.reserve( commandbufsize );
	find_command_count = 0;
	strength_check = COMMAND_STRENGTH_CHECK_MAX;

	chara_direction = DIRECTION_LEFT;
	player_y = 0;
	player_dy = 0;

	skillcommand.clear();
	tame = Tame();
}

void Command::AddCommandBuffer( ALL_INPUT button ){
	if( command_buffer.size() < commandbufsize ){
		command_buffer.push_back( button );
	}else{
		vector<ALL_INPUT>::iterator startIterator;
		startIterator = command_buffer.begin();
		command_buffer.erase( startIterator );
		command_buffer.push_back( button );
	}
}

//溜め入力
void Command::InputTame( bool press, int* count_tame, bool isLR ){

	if( isLR ){	//左右のとき
		if( before_chara_direction != chara_direction ){	//向きが変わったらクリア	相手に追い越された時に暴発しないように
			count_tame[0] = 0;
			count_tame[1] = 0;
			count_tame[2] = 0;
		}
	}
	

	if( press ){
		count_tame[0]++;
	}else{
		if( count_tame[0] > count_tame[1] ){
			count_tame[1] = count_tame[0];		//カウントを保持
			count_tame[2] = tame_clear_count;	//消滅タイマーセット
			count_tame[0] = 0;					//カウントをリセット
		}
	}
	count_tame[2]--;
	if( count_tame[2] <= 0 ){
		count_tame[1] = 0;		//保持していたカウントをクリア
	}

}

void Command::InputStatus( BUTTON button, int* tamaID, bool isAI ){
	if( !isAI ){
		for( int i=0 ; i<COMMAND_SUCCESS_MOTION_NAME_ALL ; i++ ){		//毎フレームクリア　ヒットストップや暗転中も入る
			commandname[i] = NULL;
			commandpriority[i] = INVALID_VAL;
		}
	}

	ALL_INPUT button_input_buffer;	//バッファに入れる用


	bool left_save = false;
	bool right_save = false;
	if( chara_direction == DIRECTION_RIGHT ){	//左向きの時コマンドの右と左を反転
		left_save = button.press.flag[LEVER_RIGHT];
		right_save = button.press.flag[LEVER_LEFT];
	}else{
		left_save = button.press.flag[LEVER_LEFT];
		right_save = button.press.flag[LEVER_RIGHT];
	}

	//移動　左右は1P側2P側で入れ替わる
	if( left_save ){
		button_input_buffer.flag[LEVER_LEFT] = true;
	}else if( right_save ){
		button_input_buffer.flag[LEVER_RIGHT] = true;
	}
	if( button.press.flag[LEVER_DOWN] ){
		button_input_buffer.flag[LEVER_DOWN] = true;
	}else if( button.press.flag[LEVER_UP] ){
		button_input_buffer.flag[LEVER_UP] = true;
	}

	
	//攻撃ボタン同時押しカウントをインクリメント
	for( int i=BUTTON_ATTACK1 ; i<=BUTTON_ATTACK6 ; i++ ){
		multipush_count[i]--;
	}

	//攻撃入力　A<B<Cの順に優先してみる
	//攻撃押した時　ついでに同時押しカウント（MULTIPUSH_DELAY）をセット
	for( int i=BUTTON_ATTACK1 ; i<=BUTTON_ATTACK6 ; i++ ){
		if( button.push.flag[i] ){
			multipush_count[i] = MULTIPUSH_DELAY;
			button_input_buffer.flag[i] = true;
		}
	}


	//AIの場合multipush_countを設定後に返す
	if( isAI ){
		return;
	}

	
	//攻撃同時押し
	if( (multipush_count[BUTTON_ATTACK1] > 0) && (multipush_count[BUTTON_ATTACK2] > 0) ){		//AB
		button_input_buffer.flag[BUTTON_ATTACK1] = true;
		button_input_buffer.flag[BUTTON_ATTACK2] = true;
	}
	if( (multipush_count[BUTTON_ATTACK2] > 0) && (multipush_count[BUTTON_ATTACK3] > 0) ){		//BC
		button_input_buffer.flag[BUTTON_ATTACK2] = true;
		button_input_buffer.flag[BUTTON_ATTACK3] = true;
	}
	if( (multipush_count[BUTTON_ATTACK1] > 0) && (multipush_count[BUTTON_ATTACK3] > 0) ){		//AC
		button_input_buffer.flag[BUTTON_ATTACK1] = true;
		button_input_buffer.flag[BUTTON_ATTACK3] = true;
	}
	if( (multipush_count[BUTTON_ATTACK1] > 0) && (multipush_count[BUTTON_ATTACK2] > 0) && (multipush_count[BUTTON_ATTACK3] > 0) ){		//ABC
		button_input_buffer.flag[BUTTON_ATTACK1] = true;
		button_input_buffer.flag[BUTTON_ATTACK2] = true;
		button_input_buffer.flag[BUTTON_ATTACK3] = true;
	}
	if( (multipush_count[BUTTON_ATTACK4] > 0) && (multipush_count[BUTTON_ATTACK5] > 0) ){		//DE
		button_input_buffer.flag[BUTTON_ATTACK4] = true;
		button_input_buffer.flag[BUTTON_ATTACK5] = true;
	}
	if( (multipush_count[BUTTON_ATTACK5] > 0) && (multipush_count[BUTTON_ATTACK6] > 0) ){		//EF
		button_input_buffer.flag[BUTTON_ATTACK5] = true;
		button_input_buffer.flag[BUTTON_ATTACK6] = true;
	}
	if( (multipush_count[BUTTON_ATTACK4] > 0) && (multipush_count[BUTTON_ATTACK6] > 0) ){		//DF
		button_input_buffer.flag[BUTTON_ATTACK4] = true;
		button_input_buffer.flag[BUTTON_ATTACK6] = true;
	}
	if( (multipush_count[BUTTON_ATTACK4] > 0) && (multipush_count[BUTTON_ATTACK5] > 0) && (multipush_count[BUTTON_ATTACK6] > 0) ){		//DEF
		button_input_buffer.flag[BUTTON_ATTACK4] = true;
		button_input_buffer.flag[BUTTON_ATTACK5] = true;
		button_input_buffer.flag[BUTTON_ATTACK6] = true;
	}

	if( (multipush_count[BUTTON_ATTACK1] > 0) && (multipush_count[BUTTON_ATTACK4] > 0) ){		//AD
		button_input_buffer.flag[BUTTON_ATTACK1] = true;
		button_input_buffer.flag[BUTTON_ATTACK4] = true;
	}
	if( (multipush_count[BUTTON_ATTACK2] > 0) && (multipush_count[BUTTON_ATTACK5] > 0) ){		//BE
		button_input_buffer.flag[BUTTON_ATTACK2] = true;
		button_input_buffer.flag[BUTTON_ATTACK5] = true;
	}
	if( (multipush_count[BUTTON_ATTACK3] > 0) && (multipush_count[BUTTON_ATTACK6] > 0) ){		//CF
		button_input_buffer.flag[BUTTON_ATTACK3] = true;
		button_input_buffer.flag[BUTTON_ATTACK6] = true;
	}

	//溜め
	for( int i=0 ; i<INPUT_LABEL_ALL ; i++ ){
		if( i == LEVER_LEFT ){	//左右は1P側2P側で入れ替わるので特別
			InputTame( left_save, tame.count_tame[LEVER_LEFT], true );
		}else if( i == LEVER_RIGHT ){
			InputTame( right_save, tame.count_tame[LEVER_RIGHT], true );
		}else{
			InputTame( button.press.flag[i], tame.count_tame[i] );
		}
	}
	before_chara_direction = chara_direction;	//向きを保持


	AddCommandBuffer( button_input_buffer );
	

	//コマンドチェック
	find_command_count = 0;		//成立したコマンドの数
	for( int i=0 ; i<skillcommand.size() ; i++ ){
		if( skillcommand[i].CheckCommand( &command_buffer, &tame, &strength_check, player_y, player_dy ) ){
			if( !ExCodeCheck( &commandproperty[i], chara_flag, vTrg_flag, cancelOnly_flag ) ){	//特殊指定チェック
				continue;
			}
			if( !TamaID_Check( &commandproperty[i], tamaID ) ){	//弾チェック
				continue;
			}

			if( skillcommand[i].valid_count == 1 ){	//成立した瞬間
				SuccessButtonSet( find_command_count, button_input_buffer, skillcommand[i].commandArray[ skillcommand[i].commandArray.size() - 1 ] );	//成立時の入力を保存
			}

			commandname[find_command_count] = &commandproperty[i].motion_name;	//モーション名配列の先頭アドレスを渡す
			commandpriority[find_command_count] = i;
			find_command_count++;

			if( find_command_count >= COMMAND_SUCCESS_MOTION_NAME_ALL ){	//これ以上いけない
				break;
			}
			//break;		//一つ成立したら抜ける　無駄な処理ではないので別に抜けなくてもいい
		}
	}

}

bool Command::ExCodeCheck( CommandProperty* c_property, bool* c_flag, bool Vtrg, bool cancelOnly ){
	int EXCODE[3] = { c_property->ex_code1, c_property->ex_code2, c_property->ex_code3 };
	bool rtn = true;
	//特殊指定チェック
	for( int i=0 ; i<3 ; i++ ){
		if( !rtn )break;	//一つ失敗していれば即失敗

		switch( EXCODE[i] ){
		case COMMAND_EX_CODE_VARIABLE:
			if( !Vtrg )rtn = false;
			break;
		case COMMAND_EX_CODE_CHARA_FLAG_1:
			if( !c_flag[0] )rtn = false;
			break;
		case COMMAND_EX_CODE_CHARA_FLAG_2:
			if( !c_flag[1] )rtn = false;
			break;
		case COMMAND_EX_CODE_CHARA_FLAG_3:
			if( !c_flag[2] )rtn = false;
			break;
		case COMMAND_EX_CODE_CHARA_FLAG_4:
			if( !c_flag[3] )rtn = false;
			break;
		case COMMAND_EX_CODE_CHARA_FLAG_5:
			if( !c_flag[4] )rtn = false;
			break;
		case COMMAND_EX_CODE_CHARA_FLAG_6:
			if( !c_flag[5] )rtn = false;
			break;
		case COMMAND_EX_CODE_CHARA_FLAG_7:
			if( !c_flag[6] )rtn = false;
			break;
		case COMMAND_EX_CODE_CHARA_FLAG_8:
			if( !c_flag[7] )rtn = false;
			break;
		case COMMAND_EX_CODE_CANCEL_ONLY:
			if( !cancelOnly )rtn = false;
			break;
		}
	}
	return rtn;
}

bool Command::TamaID_Check( CommandProperty* c_property, int* tamaID ){
	bool rtn = true;
	for( int i=0 ; i<SHOT_USE_MAX ; i++ ){
		if( c_property->tama_id == tamaID[i] ){
			rtn = false;
			break;
		}
	}
	return rtn;
}

void Command::DataLoad( char propertydata[64], istringstream* pIss ){
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
		
		str.erase( str.find_last_not_of("\r")+1 );	//改行ｺｰﾄﾞ削除

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

		if( !table[i][1].empty() ){	//モーション名が空
			CommandProperty tmp;
			string search_str;	//文字列検索用
			unsigned int loc;	//文字列検索用


			//variation
			tmp.variation = atoi( table[i][1].c_str() );

			//モーション名
			tmp.motion_name = table[i][2];

			//コマンドが成功する状態（地空）
			for( int j=0 ; j<COMMAND_SUCCESS_STATE_MAX ; j++ ){
				tmp.success_state = COMMAND_SUCCESS_STATE_MAX;
				if( j == 0 )search_str = "GROUND";
				if( j == 1 )search_str = "AIR";
				if( j == 2 )search_str = "LOCK";
				if( table[i][3] == search_str ){
					tmp.success_state = (COMMAND_SUCCESS_STATE)j;
					break;
				}
			}


			//入力猶予
			tmp.reception_time = atoi( table[i][4].c_str() );
			//有効時間
			tmp.valid_time = atoi( table[i][5].c_str() );


			//特殊指定１
			for( int j=0 ; j<COMMAND_EX_CODE_MAX ; j++ ){
				tmp.ex_code1 = COMMAND_EX_CODE_MAX;
				if( j == 0 )search_str = "VARIABLE";
				if( j == 1 )search_str = "CHARA_FLAG_1";
				if( j == 2 )search_str = "CHARA_FLAG_2";
				if( j == 3 )search_str = "CHARA_FLAG_3";
				if( j == 4 )search_str = "CHARA_FLAG_4";
				if( j == 5 )search_str = "CHARA_FLAG_5";
				if( j == 6 )search_str = "CHARA_FLAG_6";
				if( j == 7 )search_str = "CHARA_FLAG_7";
				if( j == 8 )search_str = "CHARA_FLAG_8";
				if( j == 9 )search_str = "LIFE_RED";
				if( j == 10 )search_str = "LIFE_GREEN";
				if( j == 11 )search_str = "HASEI";
				if( j == 12 )search_str = "CANCEL_ONLY";
				if( j == 13 )search_str = "FORCE_CANCEL";
				if( table[i][6] == search_str ){
					tmp.ex_code1 = (COMMAND_EX_CODE)j;
					break;
				}
			}

			//特殊指定２
			for( int j=0 ; j<COMMAND_EX_CODE_MAX ; j++ ){
				tmp.ex_code2 = COMMAND_EX_CODE_MAX;
				if( j == 0 )search_str = "VARIABLE";
				if( j == 1 )search_str = "CHARA_FLAG_1";
				if( j == 2 )search_str = "CHARA_FLAG_2";
				if( j == 3 )search_str = "CHARA_FLAG_3";
				if( j == 4 )search_str = "CHARA_FLAG_4";
				if( j == 5 )search_str = "CHARA_FLAG_5";
				if( j == 6 )search_str = "CHARA_FLAG_6";
				if( j == 7 )search_str = "CHARA_FLAG_7";
				if( j == 8 )search_str = "CHARA_FLAG_8";
				if( j == 9 )search_str = "LIFE_RED";
				if( j == 10 )search_str = "LIFE_GREEN";
				if( j == 11 )search_str = "HASEI";
				if( j == 12 )search_str = "CANCEL_ONLY";
				if( j == 13 )search_str = "FORCE_CANCEL";
				if( table[i][7] == search_str ){
					tmp.ex_code2 = (COMMAND_EX_CODE)j;
					break;
				}
			}

			//特殊指定３
			for( int j=0 ; j<COMMAND_EX_CODE_MAX ; j++ ){
				tmp.ex_code3 = COMMAND_EX_CODE_MAX;
				if( j == 0 )search_str = "VARIABLE";
				if( j == 1 )search_str = "CHARA_FLAG_1";
				if( j == 2 )search_str = "CHARA_FLAG_2";
				if( j == 3 )search_str = "CHARA_FLAG_3";
				if( j == 4 )search_str = "CHARA_FLAG_4";
				if( j == 5 )search_str = "CHARA_FLAG_5";
				if( j == 6 )search_str = "CHARA_FLAG_6";
				if( j == 7 )search_str = "CHARA_FLAG_7";
				if( j == 8 )search_str = "CHARA_FLAG_8";
				if( j == 9 )search_str = "LIFE_RED";
				if( j == 10 )search_str = "LIFE_GREEN";
				if( j == 11 )search_str = "HASEI";
				if( j == 12 )search_str = "CANCEL_ONLY";
				if( j == 13 )search_str = "FORCE_CANCEL";
				if( table[i][8] == search_str ){
					tmp.ex_code3 = (COMMAND_EX_CODE)j;
					break;
				}
			}

			//禁止弾ID
			tmp.tama_id = atoi( table[i][9].c_str() );

			//コマンド
			for( int j=0 ; j<COMMAND_PARTS_MAX ; j++ ){
				if( !table[i][10+j].empty() ){
					tmp.command += ( table[i][10+j] + "," );
				}
			}

			

			//禁止キー
			tmp.ng_key = table[i][26];

			
			//追加
			commandproperty.push_back( tmp );
		}
	}

	for( int i=0 ; i<commandproperty.size() ; i++ ){
		CommandPushBack(
			commandproperty[i].command,
			commandproperty[i].reception_time,
			commandproperty[i].valid_time,
			commandproperty[i].success_state
			);
	}
}
void Command::DataLoadFromFileInMemory( char propertydata[64], CArchive* pArchive ){
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


//成立時の入力を保存
void Command::SuccessButtonSet( int index, ALL_INPUT allInput, CommandAllButton allButton ){
	success_input[index] = allInput;
	success_button[index] = allButton;
}
//EXで出そうとしたがゲージが足りなかったときにCOMMAND_STRENGTH_CHECKを変更
void Command::EX_NotEnough( int index ){
	if( success_button[index].any_attack_double || success_button[index].any_attack_triple ){
		if( success_button[index].flag[BUTTON_ATTACK1] ){	//P
			if( success_input[index].flag[BUTTON_ATTACK3] ){
				strength_check = COMMAND_STRENGTH_CHECK_H;
			}else if( success_input[index].flag[BUTTON_ATTACK2] ){
				strength_check = COMMAND_STRENGTH_CHECK_M;
			}else{
				strength_check = COMMAND_STRENGTH_CHECK_L;
			}
		}else if( success_button[index].flag[BUTTON_ATTACK4] ){	//K
			if( success_input[index].flag[BUTTON_ATTACK6] ){
				strength_check = COMMAND_STRENGTH_CHECK_H;
			}else if( success_input[index].flag[BUTTON_ATTACK5] ){
				strength_check = COMMAND_STRENGTH_CHECK_M;
			}else{
				strength_check = COMMAND_STRENGTH_CHECK_L;
			}
		}
	}
}