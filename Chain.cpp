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
		
		if( str.find_last_not_of("\r") != string::npos ){
			str.erase( str.find_last_not_of("\r")+1 );	//���s���ލ폜
		}else{
			break;
		}

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

		if( !table[i][1].empty() ){	//ID����
			ChainProperty tmp;
			string search_str;	//�����񌟍��p
			unsigned int loc;	//�����񌟍��p

			//frame
			tmp.frame = atoi( table[i][1].c_str() );

			//ID
			tmp.id = atoi( table[i][2].c_str() );
			//group
			tmp.group = atoi( table[i][3].c_str() );
			//�J�n���[�V������
			tmp.start_motion_name = table[i][4];
			//�������
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

			//�R�}���h
			for( int j=0 ; j<6 ; j++ ){
				ChainParts tmp2;
				string strtmp0 = table[i][6+ 5*j + 0];
				string strtmp1 = table[i][6+ 5*j + 1];
				string strtmp2 = table[i][6+ 5*j + 2];

				string strtmp3 = table[i][6+ 5*j + 3];
				string strtmp4 = table[i][6+ 5*j + 4];


				if( strtmp0.empty() && strtmp1.empty() && strtmp2.empty() ){	//3�̃Z������
					goto PARTS_PUSH_BACK_LABEL;
				}else{
					tmp2.empty_flg = false;	//��̃f�[�^�ł͂Ȃ�
				}
				//======================= ���o�[�A���R�[�h�w�� =======================
				if( !strtmp0.empty() ){		//���o�[�A���R�[�h�w��
					if( strtmp0 == "END" ){	//�I���w��
						//break;
						tmp2.end_flg = true;
						goto PARTS_PUSH_BACK_LABEL;
					}else if( strtmp0 == "SKIP" ){	//�X�L�b�v�w��
						tmp2.skip_chain_route_id	= atoi( strtmp1.c_str() );
						tmp2.skip_chain_count		= atoi( strtmp2.c_str() );
						goto PARTS_PUSH_BACK_LABEL;
					}else if( strtmp0 == "INC" ){	//�J�E���g���C���N�������g����@�h���������Ȃ��Ƃ��Ɏg��
						tmp2.skip_chain_count++;
						goto PARTS_PUSH_BACK_LABEL;
					}else{
						tmp2.SetChainLever( strtmp0 );	//���o�[�w��
					}
				}

				//======================= �{�^���A���w��q������ =======================
				if( !strtmp1.empty() ){		//�{�^���A���w��q������
					if(0){
					}else{
						tmp2.SetChainButton( strtmp1 );
					}
				}

				//======================= ���[�V�������A���w��q������ =======================
				if( !strtmp2.empty() ){		//���[�V�������A���w��q������
					if(0){
					}else{
						tmp2.success_motion_name = strtmp2;
					}
				}



				//======================= �J�nF =======================
				if( !strtmp3.empty() ){
					if(0){
						tmp2.start_frame = -1;
					}else{
						tmp2.start_frame = atoi( strtmp3.c_str() );
					}
				}

				//======================= �I��F =======================
				if( !strtmp4.empty() ){
					if(0){
						tmp2.end_frame = -1;
					}else{
						tmp2.end_frame = atoi( strtmp4.c_str() );
					}
				}


				
				//======================= �p�[�c�ǉ� =======================
PARTS_PUSH_BACK_LABEL:
				tmp.parts.push_back( tmp2 );
			}

			//�ǉ�
			chaindata.push_back( tmp );
		}
	}

}

void Chain::DataLoadFromFileInMemory( char propertydata[64], CArchive* pArchive ){
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


void ChainParts::SetChainButton( string parts ){
	button_empty_flg = false;
	//button�̌^��CommandAllButton�Ȃ̂ōׂ����w�肪�\
	//�U���{�^��
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

	//���QP
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
	//���QK
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

	//�c�Q
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

	//���R
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

	//�U���{�^���v�f
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


	//�I�[�g
	if( parts == "AUTO" ){
		return;
	}

	button_empty_flg = true;
}

void ChainParts::SetChainLever( string parts ){
	lever_empty_flg = false;
	//button�̌^��CommandAllButton�Ȃ̂ōׂ����w�肪�\
	//���o�[�v�f
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

	//���o�[
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
		return;		//�`�F�[���̍Œ��Ȃ̂ōĐݒ�͂ł��Ȃ��@��������
	}

	for( int i=0 ; i<chaindata.size() ; i++ ){
		if( chaindata[i].start_motion_name == (*motion_name) ){	//�J�n���[�V�����ƈ�v
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
	ChainEnd();		//��U�N���A
	chain_route_id = skipID;
	chain_count = skipCount;
}

void Chain::ChainCountInc(){
	chainname = NULL;

	////�I��
	//if( chaindata[chain_route_id].parts[chain_count].end_flg ){
	//	ChainEnd();
	//	return;
	//}

	chain_count++;
}

void Chain::InputStatus( BUTTON button, int* pMultipush, string* motion_name, int fgtFrame, bool hitFlg, float y_pos ){
	BUTTON button_save = button;
	if( chara_direction == DIRECTION_RIGHT ){	//�������̎��R�}���h�̉E�ƍ��𔽓]
		button.press.flag[LEVER_LEFT]	= button_save.press.flag[LEVER_RIGHT];
		button.push.flag[LEVER_LEFT]	= button_save.push.flag[LEVER_RIGHT];
		button.press.flag[LEVER_RIGHT]	= button_save.press.flag[LEVER_LEFT];
		button.push.flag[LEVER_RIGHT]	= button_save.push.flag[LEVER_LEFT];
	}

	if( chain_route_id == INVALID_VAL )return;
	if( chain_count == INVALID_VAL )return;

	if( chain_count == 0 ){
		if( chaindata[chain_route_id].start_motion_name != (*motion_name) ){	//�L�����̃��[�V�����ƃ`�F�[���J�n���[�V���������Ⴄ
			//return;
		}
	}else if( chain_count > 0 ){
		if( chaindata[chain_route_id].parts[chain_count-1].success_motion_name != (*motion_name) ){	//�L�����̃��[�V�����ƈ�O�̃`�F�[�����[�V���������Ⴄ
			//return;
		}
	}

	//�`�F�[���X�L�b�v
	int ID = chaindata[chain_route_id].parts[chain_count].skip_chain_route_id;
	int Count = chaindata[chain_route_id].parts[chain_count].skip_chain_count;
	if( ID != INVALID_VAL && Count != INVALID_VAL ){
		ChainSkip( ID, Count );
		return;
	}

	if( chaindata[chain_route_id].parts[chain_count].end_flg ){	//���ݎw�蒆�̃`�F�[��ID�̎��̃p�[�c��END�w��̂Ƃ��͂���ȏ�i�߂Ȃ����h���ł��Ȃ�
		return;
	}


	//���̃p�[�c���������Ă��邩���ׂ�i�h�����܂�
	int group_no = chaindata[chain_route_id].group;	//�O���[�v�ԍ�
	for( int i=0 ; i<chaindata.size() ; i++ ){	//�����O���[�v�ԍ��̃f�[�^�����邩��������Œ��ׂ�
		
		if( chaindata[i].group == group_no ){		//�O���[�v�ԍ�����v

			////�x�N�^�̗v�f�����z�����@�z��O���Q�Ƃ��Ă͂����Ȃ��̂ōŗD��
			//if( chaindata[i].parts.size() >= chain_count ){
			//	continue;
			//}


			//�󔒂̃f�[�^�ł���
			if( chaindata[i].parts[chain_count].empty_flg ){
				continue;
			}

			//�I���f�[�^�ł���
			if( chaindata[i].parts[chain_count].end_flg ){
				continue;
			}

			//������Ԕ���
			switch( chaindata[i].success_state ){
			case COMMAND_SUCCESS_STATE_GROUND:	//�n�サ���o���Ȃ�
				if( y_pos > ground ){
					continue;
				}
				break;
			case COMMAND_SUCCESS_STATE_AIR:		//�󒆂����o���Ȃ�
				if( y_pos <= ground ){
					continue;
				}
				break;
			case COMMAND_SUCCESS_STATE_LOCK:	//�f�o�b�O�p�@���b�N
				continue;
				break;
			}

			//���o�[���{�^������
			if( !CommandCheck( button, chaindata[i].parts[chain_count].button, pMultipush ) ){
				continue;
			}

			if( fgtFrame < 2 ){
				continue;
			}
			if( chaindata[i].id >= 200 ){
				//��`�F�[���\
			}else{
				if( !hitFlg ){
					continue;
				}
			}

			//�����܂ł����琬��
			chainname = &chaindata[i].parts[chain_count].success_motion_name;
			chain_route_id = i;		//�`�F�[��ID�X�V
			//chain_count++;	//�`�F�[���J�E���g�͌Ăяo�����Ŗ{���ɐ����������m�F������ɐi�߂�
			break;		//�������攲����
		}
	}

}

bool Chain::CommandCheck( BUTTON button, CommandAllButton chain_button, int* multipush_count ){

	for( int i=0 ; i<INPUT_LABEL_ALL ; i++ ){
		if( i <= LEVER_RIGHT ){
			//���o�[
			if( chaindata[chain_route_id].parts[chain_count].lever_empty_flg ){	//���o�[��̂Ƃ��͒ʂ�
				continue;
			}
			if( chain_button.lever_youso ){
				//�v�f�iUDLR�j�̂Ƃ�
				if( chain_button.flag[i] ){	//true�̂Ƃ��̂�
					if( button.press.flag[i] != chain_button.flag[i] ){
						return false;
					}
				}
			}else{
				//��Γ��́i123...�j�̂Ƃ�
				if( chain_button.flag[i] != button.press.flag[i] ){
					return false;
				}
			}
		}else{
			
			//�{�^��
			if( chain_button.any_attack ){
				//�ǂ�ł�OK
				if( chain_button.flag[BUTTON_ATTACK1] ){	//�K�v�ȓ��� P
					if( multipush_count[BUTTON_ATTACK1] <= 0 && multipush_count[BUTTON_ATTACK2] <= 0 && multipush_count[BUTTON_ATTACK3] <= 0 ){ 	//�P�\
					//if( !button.push.flag[BUTTON_ATTACK1] && !button.push.flag[BUTTON_ATTACK2] && !button.push.flag[BUTTON_ATTACK3] ){	//�P�\������
						return false;	//����������Ă��Ȃ���Ύ��s
					}
				}
				if( chain_button.flag[BUTTON_ATTACK4] ){	//�K�v�ȓ��� K
					if( multipush_count[BUTTON_ATTACK4] <= 0 && multipush_count[BUTTON_ATTACK5] <= 0 && multipush_count[BUTTON_ATTACK6] <= 0 ){ 
					//if( !button.push.flag[BUTTON_ATTACK4] && !button.push.flag[BUTTON_ATTACK5] && !button.push.flag[BUTTON_ATTACK6] ){
						return false;	//����������Ă��Ȃ���Ύ��s
					}
				}
			}else if( chain_button.multi_push ){
				//���������p
				if( chain_button.flag[i] ){	//�K�v�ȃ{�^���̂݌���
					if( multipush_count[i] <= 0 ){	//������Ă���̗P�\�͂��邩�H
						return false;	//�K�v�ȃ{�^���̗P�\���Ȃ������̂Ŏ��s
					}
				}
			}else{
				//���ʂ̎w��
				if( chain_button.flag[i] ){	//�K�v�ȓ���
					if( multipush_count[i] <= 0 ){	//�P�\
						return false;
					}

					/*if( button.push.flag[i] != chain_button.flag[i] ){	//�P�\������
						return false;
					}*/
				}
			}
		}
	}

	return true;
}


