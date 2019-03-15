#pragma once
#include <string>
using namespace std;

class IStarVoipP2PListener 
{
public:
	/**
	 * ��ʼ���ɹ�
	 */
	virtual void initComplete(bool success) = 0;

	virtual void callingOK() = 0;
	virtual void callingFailed(string error) = 0;
	virtual void responseOK() = 0;
	virtual void responseFailed(string error) = 0;

	/**
	 * ������
	 */
	virtual void onCalling(string farIP) = 0;

	/**
	 * ���ܽ�
	 */
	virtual void onRefused(string farIP) = 0;

	/**
	 * ���Ҷ�
	 */
	virtual void onHangup(string farIP) = 0;

	/**
	 * ռ��
	 */
	virtual void onBusy(string farIP) = 0;

	/**
	 * ��ͨ
	 */
	virtual void onConnect(string farIP) = 0;

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
};