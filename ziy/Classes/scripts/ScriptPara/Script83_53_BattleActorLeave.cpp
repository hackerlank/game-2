﻿#include "Common.h"
#include "Scripts.h"
#include "WinConditionTool.h"
void ScriptBattleActorLeave::getActorList()
{
	int i,j;
	HistoryActorPtr actor = NULL; 
	for(i = left_top_y;i<=right_bottom_y;i++)
	{
		for(j = left_top_x;j<=right_bottom_x;j++)
		{
			actor = history->FindActorPosition(j,i);
			if(actor!=NULL)
			{
				switch(relation)
				{
				case 0:
					if(actor->relation == 0)
					{
						actor_id_list[actor_num++] = actor->actor_id;
					}
					break;
				case 1:
					if(actor->relation == 1)
					{
						actor_id_list[actor_num++] = actor->actor_id;
					}
					break;
				case 2:
					if(actor->relation == 2)
					{
						actor_id_list[actor_num++] = actor->actor_id;
					}
					break;
				case 3:
					break;
				case 4:
					if(actor->relation == 0||actor->relation == 1)
					{
						actor_id_list[actor_num++] = actor->actor_id;
					}
					break;
				case 5:
					if(actor->relation == 2)
					{
						actor_id_list[actor_num++] = actor->actor_id;
					}
					break;
				case 6:
					actor_id_list[actor_num++] = actor->actor_id;
					break;
				}
			}
		}
	}
}
int ScriptBattleActorLeave::HandleScript(){
	BattleActorPtr battle_actor;
	if(frame == 0)
	{
		actor_num = 0;
		actor_index= 0;
		if(which_index <= 0)
		{
			actor_id_list[actor_num++] = actor_id;
		}
		else
		{
			getActorList();
		}
		need_frame = 0;
	}
	if(frame == need_frame)
	{
		if(actor_index!=actor_num)
		{
			int iActorId = actor_id_list[actor_index++];
			if (history->actors[iActorId].GetCurHp() > 0)
				WinConditionTool::getInstance()->ActorRetreatCondition(iActorId);

			frame = 0;
			battle_actor = BattleControler::getBattleActor(iActorId);

			if (battle_actor)
			{
				if (which_index > 0)
				{
					need_frame = battle_actor->setState(ACTOR_STATE_LEAVE_HIDE);
				}
				else if (is_leave)
				{
					need_frame = battle_actor->setState(ACTOR_STATE_LEAVE_DEAD);
				}
				else
				{
					need_frame = battle_actor->setState(ACTOR_STATE_LEAVE_NORMAL);
				}
			}
		}
	}
	return need_frame - frame++;
}

int ScriptBattleActorLeave::initPara(char*SceneData,int index){
	unkown1 =  bytesToShort(SceneData, index);
	index += SHORT_NUM_LEN;
	which_index =  bytesToShort(SceneData, index);
	index += SHORT_NUM_LEN;
	unkown2 =  bytesToShort(SceneData, index);
	index += SHORT_NUM_LEN;
	actor_id =  bytesToShort(SceneData, index);
	index += SHORT_NUM_LEN;	
	unkown3 =  bytesToShort(SceneData, index);
	index += SHORT_NUM_LEN;
	left_top_x =  bytesToShort(SceneData, index);
	index += INT_NUM_LEN;	
	unkown4 =  bytesToShort(SceneData, index);
	index += SHORT_NUM_LEN;
	left_top_y =  bytesToShort(SceneData, index);
	index += INT_NUM_LEN;	
	unkown5 =  bytesToShort(SceneData, index);
	index += SHORT_NUM_LEN;
	right_bottom_x =  bytesToShort(SceneData, index);
	index += INT_NUM_LEN;	
	unkown6 =  bytesToShort(SceneData, index);
	index += SHORT_NUM_LEN;
	right_bottom_y =  bytesToShort(SceneData, index);
	index += INT_NUM_LEN;	
	unkown7 =  bytesToShort(SceneData, index);
	index += SHORT_NUM_LEN;
	relation =  bytesToShort(SceneData, index);
	index += SHORT_NUM_LEN;
	unkown8 =  bytesToShort(SceneData, index);
	index += SHORT_NUM_LEN;
	is_leave =  bytesToShort(SceneData, index);
	index += SHORT_NUM_LEN;	
	return index;
}
