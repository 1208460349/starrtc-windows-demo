#pragma once
#include <list>
#include "ChatroomInfo.h"
class IChatroomGetListListener
{
public:
	/**
	 * ��ѯ�������б�ص�
	 */
	virtual int chatroomQueryAllListOK(list<ChatroomInfo>& listData) = 0;
};

