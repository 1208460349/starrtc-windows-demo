#pragma once
#include "CIMMessage.h"
class IChatManagerListener
{
public:
	/**
	 * �յ���Ϣ
	 * @param message
	 */
	virtual void onReceiveMessage(CIMMessage message) = 0;
};

