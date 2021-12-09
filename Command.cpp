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
	//variation = �����ŃL�����̏��������Ă���

	//�A���_�[�o�[��؂�
	char delim = ',';
	size_t current = 0, found;
	while( (found = command.find_first_of( delim, current )) != string::npos ){
		commandArray_string.push_back( string( command, current, found - current ) );
		current = found + 1;
	}


	//��؂���������ALL_INPUT�ɕϊ�
	for( int i=0 ; i<commandArray_string.size() ; i++ ){
		const string parts = commandArray_string[i];
		CommandAllButton button;	//���񏉊���

		//�U���{�^��
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

		//����������
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
		//�c��������
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
		if( parts == "ATK_P" ){	//P�U���ǂꂩ
			button.flag[BUTTON_ATTACK1] = true;
			button.flag[BUTTON_ATTACK2] = true;
			button.flag[BUTTON_ATTACK3] = true;
			button.any_attack = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "ATK_K" ){	//K�U���ǂꂩ
			button.flag[BUTTON_ATTACK4] = true;
			button.flag[BUTTON_ATTACK5] = true;
			button.flag[BUTTON_ATTACK6] = true;
			button.any_attack = true;
			commandArray.push_back( button );
			continue;
		}
		if( parts == "ATK" ){	//�U���ǂꂩ
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

		//�U���{�^���@�������Ƃ�
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
		//P��
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
		//K��
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

		//����
		if( parts == "T" ){
			button.tame = true;
			commandArray.push_back( button );
			continue;
		}

		//���o�[�v�f
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
		

		//���o�[
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
	int commandIndex = 0;	//�R�}���h�����Q�Ƃ��邽�߂̃C���f�b�N�X
	int bufferIndex = 0;	//�󂯎�����o�b�t�@�����Q�Ƃ��邽�߂̃C���f�b�N�X

	ALL_INPUT parts_success_input = ALL_INPUT();	//�p�[�c�����������Ƃ��̓���
	bool parts_success_input_change = true;		//���������Ƃ��̓��͂��ς�������H

	CommandAllButton* check = NULL;		//�`�F�b�N����R�}���h���ꎞ�I�Ɋi�[����

	COMMAND_STRENGTH_CHECK st_check_buf = COMMAND_STRENGTH_CHECK_MAX;	//�������ɑ������܂ŕێ�


	//�R�}���h���������邩�A�R�}���h���͎�t���E�܂ŁA�o�b�t�@�ƃR�}���h���ׂ�
	while( ( bufferIndex < reception_time ) && ( commandIndex < buffer->size() ) ){


		int commandlength = commandArray.size();	//����ނ̕�����
		check = &commandArray[commandlength-commandIndex-1];
		
		//�R�}���h�Ɠ��͂�����ׂ�
		if( bufferIndex < buffer->size() ){
			int bufferlength = buffer->size();
			ALL_INPUT* pointer = (ALL_INPUT*)&(buffer->at(0));	//�ޯ̧�̐擪�A�h���X
			if( !parts_success_input.lever_match( pointer[bufferlength-bufferIndex-1] ) ){
				parts_success_input_change = true;
			}


			bool lever_match = false;
			bool button_match = false;
			if( !check->tame ){
				if( check->flag[BUTTON_ATTACK1] || check->flag[BUTTON_ATTACK2] || check->flag[BUTTON_ATTACK3] || check->flag[BUTTON_ATTACK4] || check->flag[BUTTON_ATTACK5] || check->flag[BUTTON_ATTACK6] ){		//�U���{�^���v�f�����邩�H
					if( check->release ){
						int any_need_count = 0;	//�K�v��
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
							//�{�^���s��v��true
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
						//�K�v��
						int need_count = 1;
						if( check->any_attack_double )need_count = 2;
						if( check->any_attack_triple )need_count = 3;
						
						//������Ă���{�^����
						int checkcount = 0;
						for( int i=INPUT_LABEL::BUTTON_ATTACK1 ; i<=INPUT_LABEL::BUTTON_ATTACK6 ; i++ ){
							if( pointer[bufferlength-bufferIndex-1].flag[i] ){
								if( check->flag[i] ){
									checkcount++;
									if( checkcount >= need_count ){	//�������[�V�����ŕ�����p
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
						//�`�F�b�N
						if( need_count > 0 && checkcount >= need_count ){
							button_match = true;
						}
					}else{
						//�K�v��
						int need_count = 0;
						for( int i=INPUT_LABEL::BUTTON_ATTACK1 ; i<=INPUT_LABEL::BUTTON_ATTACK6 ; i++ ){
							if( check->flag[i] ){
								need_count++;
							}
						}
						//������Ă���{�^����
						int checkcount = 0;
						for( int i=INPUT_LABEL::BUTTON_ATTACK1 ; i<=INPUT_LABEL::BUTTON_ATTACK6 ; i++ ){
							if( pointer[bufferlength-bufferIndex-1].flag[i] ){
								if( check->flag[i] ){
									checkcount++;
								}
							}
						}
						//�`�F�b�N
						if( need_count > 0 && checkcount >= need_count ){
							button_match = true;
							//if( check->flag[BUTTON_ATTACK1] && check->flag[BUTTON_ATTACK2] ){	//EX�Z�@��Ζ�肠��̂Œ���
							if( need_count >= 2 ){	//���v�H
								*strength_check = COMMAND_STRENGTH_CHECK_EX;
							}
						}
					}
				}else{
					if( !check->lever_youso ){
						//���o�[�S��v����
						if( ( check->flag[LEVER_UP] == pointer[bufferlength-bufferIndex-1].flag[LEVER_UP] ) &&
							( check->flag[LEVER_DOWN] == pointer[bufferlength-bufferIndex-1].flag[LEVER_DOWN] ) && 
							( check->flag[LEVER_LEFT] == pointer[bufferlength-bufferIndex-1].flag[LEVER_LEFT] ) && 
							( check->flag[LEVER_RIGHT] == pointer[bufferlength-bufferIndex-1].flag[LEVER_RIGHT] ) ){
								lever_match = true;
						}
					}else{
						//���o�[�v�f�܂ݔ���
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
					//�ꏏ��������A���̓��͂𒲂ׂ邽�߂ɃC���f�b�N�X�����Z
					parts_success_input = pointer[bufferlength-bufferIndex-1];
					parts_success_input_change = false;

					//bufferIndex++;
					commandIndex++;
					if( commandIndex >= commandArray.size() ){
						break;	//�����I
					}
					continue;
				}
			}
			if( button_match ){
				//�ꏏ��������A���̓��͂𒲂ׂ邽�߂ɃC���f�b�N�X�����Z
				parts_success_input = pointer[bufferlength-bufferIndex-1];
				parts_success_input_change = true;

				//bufferIndex++;
				commandIndex++;
				if( commandIndex >= commandArray.size() ){
					break;	//�����I
				}
				continue;
			}


			//���߃`�F�b�N
			if( check->tame ){
				//T�̑O�̕��������߃t���[�������͂���Ă��邩�@��F4T6a�Ȃ�4
				int tame_F = reception_time;		//���߃R�}���h�͓��͗P�\���g���@4���ߌ㑦6����Ȃ��Əo�Ȃ��̂�+5
				
				//�K�v��
				int need_tame = 0;
				for( int i=0 ; i<INPUT_LABEL_ALL ; i++ ){
					if( commandArray[commandlength-commandIndex-2].flag[i] ){
						need_tame++;
					}
				}
				if( commandArray[commandlength-commandIndex-2].any_attack )need_tame = 1;
				else if( commandArray[commandlength-commandIndex-2].any_attack_double )need_tame = 2;
				else if( commandArray[commandlength-commandIndex-2].any_attack_triple )need_tame = 3;
				
				//���ߐ����J�E���g
				int tame_OK = 0;
				for( int i=0 ; i<INPUT_LABEL_ALL ; i++ ){
					if( CheckTame( commandArray[commandlength-commandIndex-2].flag[i], tame->count_tame[i][1], tame_F ) ){
						tame_OK++;
					}
				}
			
				if( tame_OK > 0 && tame_OK >= need_tame ){
					//bufferIndex++;
					commandIndex += 2;	//'T'�̂Ԃ��
					if( commandIndex >= commandArray.size() ){
						break;	//�����I while�𔲂���
					}
				}else{
					break;	//while�𔲂���
				}
			}
		}
		
		//�o�b�t�@�̎��̏ꏊ�𒲂ׂ邽�߂ɃC���f�b�N�X�����Z
		bufferIndex++;
	}

	//�R�}���h�̃C���f�b�N�X���A�R�}���h�z��̒����Ɠ�����������R�}���h�������������ɂȂ�
	if( commandIndex == commandArray.size() ){
		//if( 
		//	valid_count == 0 ||
		//	( !command_success_key_save.match( parts_success_input ) )
		//	){
		//	valid_count = 1;
		//	command_success_key_save = parts_success_input;		//���͂�ۑ����Ă���
		//}
		//�����L�����Ԓ��ɃR�}���h��������x������������valid_count�����Z�b�g������


		if( bufferIndex <= success_bufferIndex_save ){
			valid_count = 0;
		}


		if( valid_count > valid_time ){	//�R�}���h������̗L�����Ԃ��`�F�b�N
			return false;
		}

		//�n��������Ŕ��肷��ƁA�R�}���h���͂����������Ƃ��̏�ԂŐ���/���s�𔻒肵�Ă��܂�
		//switch(success_state){
		//case COMMAND_SUCCESS_STATE_GROUND:	//�n�サ���o���Ȃ�
		//	if(y_pos + dy > ground)return false;
		//	break;
		//case COMMAND_SUCCESS_STATE_AIR:		//�󒆂����o���Ȃ�
		//	if(y_pos <= ground)return false;
		//	break;
		//case COMMAND_SUCCESS_STATE_LOCK:	//�f�o�b�O�p�@���b�N
		//	return false;
		//	break;
		//}
		valid_count++;

		if( commandArray[commandIndex-1].any_attack ){
			*strength_check = st_check_buf;
		}


		success_bufferIndex_save = bufferIndex;

		//�R�}���h���������Ă�����Atrue ��Ԃ�
		return true;
	}
	valid_count = success_bufferIndex_save = 0;	//�O��
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

//���ߓ���
void Command::InputTame( bool press, int* count_tame, bool isLR ){

	if( isLR ){	//���E�̂Ƃ�
		if( before_chara_direction != chara_direction ){	//�������ς������N���A	����ɒǂ��z���ꂽ���ɖ\�����Ȃ��悤��
			count_tame[0] = 0;
			count_tame[1] = 0;
			count_tame[2] = 0;
		}
	}
	

	if( press ){
		count_tame[0]++;
	}else{
		if( count_tame[0] > count_tame[1] ){
			count_tame[1] = count_tame[0];		//�J�E���g��ێ�
			count_tame[2] = tame_clear_count;	//���Ń^�C�}�[�Z�b�g
			count_tame[0] = 0;					//�J�E���g�����Z�b�g
		}
	}
	count_tame[2]--;
	if( count_tame[2] <= 0 ){
		count_tame[1] = 0;		//�ێ����Ă����J�E���g���N���A
	}

}

void Command::InputStatus( BUTTON button, int* tamaID, bool isAI ){
	if( !isAI ){
		for( int i=0 ; i<COMMAND_SUCCESS_MOTION_NAME_ALL ; i++ ){		//���t���[���N���A�@�q�b�g�X�g�b�v��Ó]��������
			commandname[i] = NULL;
			commandpriority[i] = INVALID_VAL;
		}
	}

	ALL_INPUT button_input_buffer;	//�o�b�t�@�ɓ����p


	bool left_save = false;
	bool right_save = false;
	if( chara_direction == DIRECTION_RIGHT ){	//�������̎��R�}���h�̉E�ƍ��𔽓]
		left_save = button.press.flag[LEVER_RIGHT];
		right_save = button.press.flag[LEVER_LEFT];
	}else{
		left_save = button.press.flag[LEVER_LEFT];
		right_save = button.press.flag[LEVER_RIGHT];
	}

	//�ړ��@���E��1P��2P���œ���ւ��
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

	
	//�U���{�^�����������J�E���g���C���N�������g
	for( int i=BUTTON_ATTACK1 ; i<=BUTTON_ATTACK6 ; i++ ){
		multipush_count[i]--;
	}

	//�U�����́@A<B<C�̏��ɗD�悵�Ă݂�
	//�U�����������@���łɓ��������J�E���g�iMULTIPUSH_DELAY�j���Z�b�g
	for( int i=BUTTON_ATTACK1 ; i<=BUTTON_ATTACK6 ; i++ ){
		if( button.push.flag[i] ){
			multipush_count[i] = MULTIPUSH_DELAY;
			button_input_buffer.flag[i] = true;
		}
	}


	//AI�̏ꍇmultipush_count��ݒ��ɕԂ�
	if( isAI ){
		return;
	}

	
	//�U����������
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

	//����
	for( int i=0 ; i<INPUT_LABEL_ALL ; i++ ){
		if( i == LEVER_LEFT ){	//���E��1P��2P���œ���ւ��̂œ���
			InputTame( left_save, tame.count_tame[LEVER_LEFT], true );
		}else if( i == LEVER_RIGHT ){
			InputTame( right_save, tame.count_tame[LEVER_RIGHT], true );
		}else{
			InputTame( button.press.flag[i], tame.count_tame[i] );
		}
	}
	before_chara_direction = chara_direction;	//������ێ�


	AddCommandBuffer( button_input_buffer );
	

	//�R�}���h�`�F�b�N
	find_command_count = 0;		//���������R�}���h�̐�
	for( int i=0 ; i<skillcommand.size() ; i++ ){
		if( skillcommand[i].CheckCommand( &command_buffer, &tame, &strength_check, player_y, player_dy ) ){
			if( !ExCodeCheck( &commandproperty[i], chara_flag, vTrg_flag, cancelOnly_flag ) ){	//����w��`�F�b�N
				continue;
			}
			if( !TamaID_Check( &commandproperty[i], tamaID ) ){	//�e�`�F�b�N
				continue;
			}

			if( skillcommand[i].valid_count == 1 ){	//���������u��
				SuccessButtonSet( find_command_count, button_input_buffer, skillcommand[i].commandArray[ skillcommand[i].commandArray.size() - 1 ] );	//�������̓��͂�ۑ�
			}

			commandname[find_command_count] = &commandproperty[i].motion_name;	//���[�V�������z��̐擪�A�h���X��n��
			commandpriority[find_command_count] = i;
			find_command_count++;

			if( find_command_count >= COMMAND_SUCCESS_MOTION_NAME_ALL ){	//����ȏア���Ȃ�
				break;
			}
			//break;		//����������甲����@���ʂȏ����ł͂Ȃ��̂ŕʂɔ����Ȃ��Ă�����
		}
	}

}

bool Command::ExCodeCheck( CommandProperty* c_property, bool* c_flag, bool Vtrg, bool cancelOnly ){
	int EXCODE[3] = { c_property->ex_code1, c_property->ex_code2, c_property->ex_code3 };
	bool rtn = true;
	//����w��`�F�b�N
	for( int i=0 ; i<3 ; i++ ){
		if( !rtn )break;	//����s���Ă���Α����s

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
	if( !pIss ){	//���ڕʌ̃t�@�C������ǂݍ��݁@�A�[�J�C�u���g��Ȃ���
		LLog::GetInstance()->SetFileName( propertydata );
		ifstream ifs( propertydata );
		if( !ifs ){
			MessageBox( 0, 0, propertydata, 0 );
			return;
		}
		ostringstream oss;
		string str;

		//������X�g���[���Ƀt�@�C���̓��e���o��
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
	while( getline( *pUseIss, str ) ){	//��s���������ǂݍ��݁A��؂蕶���ŕ����ă��X�g�ɒǉ�����
		
		str.erase( str.find_last_not_of("\r")+1 );	//���s���ލ폜

		vector<string> record;					// �P�s���̕�����̃��X�g
		istringstream streambuffer( str );		// ������X�g���[��
		string token;							// �P�Z�����̕�����
		if( table.empty() ){
			while( getline( streambuffer, token, ',' ) ){
				record.push_back( token );	// �P�Z�����̕���������X�g�ɒǉ�����
			}
		}else{
			record.resize( table[0].size() );
			for( int i=0 ; i<record.size() ; i++ ){
				if( !getline( streambuffer, token, ',' ) ){
					//break;
				}
				record[i] = token;	// �P�Z�����̕���������X�g�ɒǉ�����
			}
			if( record[1].empty() || record[1] == ""  || ( record[1][0] == 0 && record[1][1] == 0 && record[1][2] == 0 ) ){	//���[�V���������Ȃ���΃f�[�^�Ȃ��Ƃ݂Ȃ�
				continue;	//while
			}
		}
		
		table.push_back( record );	// �P�s���̕�������o�͈����̃��X�g�ɒǉ�����
	}


	for( int i=1 ; i<table.size() ; i++ ){	//��s�ڂ͐����Ȃ̂Ŕ�΂�
		if( table[i].empty() || ( table[i].size() < 3 ) ){
			continue;
		}

		if( !table[i][1].empty() ){	//���[�V����������
			CommandProperty tmp;
			string search_str;	//�����񌟍��p
			unsigned int loc;	//�����񌟍��p


			//variation
			tmp.variation = atoi( table[i][1].c_str() );

			//���[�V������
			tmp.motion_name = table[i][2];

			//�R�}���h�����������ԁi�n��j
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


			//���͗P�\
			tmp.reception_time = atoi( table[i][4].c_str() );
			//�L������
			tmp.valid_time = atoi( table[i][5].c_str() );


			//����w��P
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

			//����w��Q
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

			//����w��R
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

			//�֎~�eID
			tmp.tama_id = atoi( table[i][9].c_str() );

			//�R�}���h
			for( int j=0 ; j<COMMAND_PARTS_MAX ; j++ ){
				if( !table[i][10+j].empty() ){
					tmp.command += ( table[i][10+j] + "," );
				}
			}

			

			//�֎~�L�[
			tmp.ng_key = table[i][26];

			
			//�ǉ�
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
		MessageBox( 0, 0, "�A�[�J�C�u�t�@�C�����ǂݍ��܂�Ă��܂���", 0 );
		return;
	}

	int inMemoryFileSize = 0;
	char* inMemoryFilePointer = NULL;
	pArchive->GetFileSizeAndPointer( propertydata, &inMemoryFileSize, &inMemoryFilePointer );

	string s( inMemoryFilePointer, ( inMemoryFilePointer + inMemoryFileSize ) );
	istringstream iss( s );

	DataLoad( propertydata, &iss );
}


//�������̓��͂�ۑ�
void Command::SuccessButtonSet( int index, ALL_INPUT allInput, CommandAllButton allButton ){
	success_input[index] = allInput;
	success_button[index] = allButton;
}
//EX�ŏo�����Ƃ������Q�[�W������Ȃ������Ƃ���COMMAND_STRENGTH_CHECK��ύX
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