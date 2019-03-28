#pragma once
#include "ISrcManagerListener.h"
#include "IMeetingManagerListener.h"
#include "CUserManager.h"
#include "CChatroomManager.h"
#include "CSrcManager.h"
enum MEETING_TYPE
{
	MEETING_TYPE_GLOBAL_PUBLIC,	// �����¼����֤
	MEETING_TYPE_LOGIN_PUBLIC,	// ��Ҫ��¼��������֤
	MEETING_TYPE_LOGIN_SPECIFY	// ��Ҫ��¼����֤
};

class CMeetingManager: public IChatroomManagerListener, public ISrcManagerListener
{
public:
	CMeetingManager(CUserManager* pUserManager, IMeetingManagerListener* pListener);
	virtual ~CMeetingManager();
public:
	static void addChatroomGetListListener(IChatroomGetListListener* pChatroomGetListListener);
	static void getMeetingList(CUserManager* pUserManager);
	bool createAndJoin(string strName, int chatroomType, int channelType, int* streamConfig, int length);
	void insertVideoNalu(uint8_t* videoData, int dataLen);
	void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);

	/*
	 * �ϱ�chatroom �� channelID
	 */
	bool reportChatRoomAndChannel(string strName, string strChatroomId, string strChannelId);
	bool joinChatroom(string strChatroomId);
	bool join(string strChatroomId, string strChannelId, int* streamConfig, int length);

	/*
	 * ��������������
	 */
	bool setStreamConfig(int* sendBuf, int length);

	bool closeChatroom();

	bool closeLive();

	bool close();

	bool applyToBroadcaster(string chatroomId, string channelId, string toId);

	void agreeApplyToBroadcaster(string toId);

	void refuseApplyToBroadcaster(string toId);

	void inviteToBroadcaster(string toId);

	void agreeInviteToBroadcaster(string toId);

	void refuseInviteToBroadcaster(string toId);
public:
	/**
	 * �����ҳ�Ա���仯
	 * @param number
	 */
	virtual void onMembersUpdated(int number);

	/**
	 * �Լ����߳�������
	 */
	virtual void onSelfKicked();

	/**
	 * �Լ����߳�������
	 */
	virtual void onSelfMuted(int seconds);

	/**
	 * �������ѹر�
	 */
	virtual void onClosed();

	/**
	 * �յ���Ϣ
	 * @param message
	 */
	virtual void onReceivedMessage(CIMMessage* pMessage);

	/**
	 * �յ�˽����Ϣ
	 * @param message
	 */
	virtual void onReceivePrivateMessage(CIMMessage* pMessage);
public:
	//src
	virtual int uploaderAddSrc(char* upUserId, int upId);
	virtual int uploaderRemoveSrc(char* upUserId, int upId);
	virtual int getRealtimeDataSrc(int upId, uint8_t* data, int len);
	virtual int getVideoRawSrc(int upId, int w, int h, uint8_t* videoData, int videoDataLen);

	virtual int deleteChannel(char* channelId);
	virtual int stopOK();
	virtual int srcError(char* errString);

public:
	static IChatroomGetListListener* m_pChatroomGetListListener;
	IMeetingManagerListener* m_pMeetingManagerListener;
	CUserManager* m_pUserManager;
	CChatroomManager* m_pChatroomManager;
	CSrcManager* m_pSrcManager;
	int m_configArr[7];
};

