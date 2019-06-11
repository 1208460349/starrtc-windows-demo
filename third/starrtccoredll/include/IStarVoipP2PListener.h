#pragma once
#include <string>
#include "CIMMessage.h"
using namespace std;

class IStarVoipP2PListener 
{
public:
	/**
	 * ����
	 */
	virtual void onError(string code) = 0;

	/**
	 * �ѹر�
	 */
	virtual void onStop(string code) = 0;

	/**
	 * �յ�ʵʱ����
	 */
	virtual void onRevRealtimeData(uint8_t* bytes, int length) = 0;

	virtual void onP2PConnectSuccess() = 0;
	virtual void onP2PConnectFailed() = 0;

	/**
	 * �յ���Ϣ
	 * @param message
	 */
	virtual void onReceiveMessage(CIMMessage* pMessage) = 0;
};