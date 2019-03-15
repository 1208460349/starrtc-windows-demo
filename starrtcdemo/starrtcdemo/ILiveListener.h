#pragma once
#include "CIMMessage.h"
class ILiveListener
{
public:
	/**
	 * �����ҳ�Ա���仯
	 * @param number
	 */
	virtual void onMembersUpdated(int number) = 0;

	/**
	 * �Լ����߳�������
	 */
	virtual void onSelfKicked() = 0;

	/**
	 * �Լ����߳�������
	 */
	virtual void onSelfMuted(int seconds) = 0;

	/**
	 * �������ѹر�
	 */
	virtual void onClosed() = 0;

	/**
	 * �յ���Ϣ
	 * @param message
	 */
	virtual void onReceivedMessage(CIMMessage* pMessage) = 0;

	/**
	 * �յ�˽����Ϣ
	 * @param message
	 */
	virtual void onReceivePrivateMessage(CIMMessage* pMessage) = 0;

	/**
	 * �����յ������û�����������
	 * @param liveID
	 * @param applyUserID
	 */
	virtual void onApplyBroadcast(string liveID, string applyUserID) = 0;

	/**
	 * ���������û��յ��Ļظ�
	 * @param liveID
	 * @param result
	 */
	virtual void onApplyResponsed(string liveID, bool bAgree) = 0;

	virtual int uploaderAdd(char* upUserId, int upId) = 0;
	virtual int uploaderRemove(char* upUserId, int upId) = 0;
	virtual int getRealtimeData(int upId, uint8_t* data, int len) = 0;
	virtual int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen) = 0;

	//src
	virtual int deleteChannel(char* channelId) = 0;
	virtual int stopOK() = 0;
	virtual int srcError(char* errString) = 0;
	//vdn
	virtual int downloadChannelClosed() = 0;
	virtual int downloadChannelLeave() = 0;
	virtual int downloadNetworkUnnormal() = 0;
	virtual int queryVDNChannelOnlineNumberFin(char* channelId, int totalOnlineNum) = 0;

};