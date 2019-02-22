#pragma once
#include "IVdnManagerListener.h"
#include "CUserManager.h"
#include "CChatroomManager.h"
#include "ILiveInterface.h"
#include "ISrcManagerListener.h"

enum LIVE_VIDEO_TYPE
{
	LIVE_VIDEO_TYPE_GLOBAL_PUBLIC,		// �����¼����֤
	LIVE_VIDEO_TYPE_LOGIN_PUBLIC,		// ��Ҫ��¼��������֤
	LIVE_VIDEO_TYPE_LOGIN_SPECIFY		// ��Ҫ��¼����֤
};

enum MEETING_TYPE
{
	MEETING_TYPE_GLOBAL_PUBLIC,	// �����¼����֤
	MEETING_TYPE_LOGIN_PUBLIC,	// ��Ҫ��¼��������֤
	MEETING_TYPE_LOGIN_SPECIFY	// ��Ҫ��¼����֤
};

class CLiveManager
{
public:
	CLiveManager(CUserManager* pUserManager, IChatroomManagerListener* pChatroomManagerListener, IVdnManagerListener* pVdnManagerListener, ISrcManagerListener* pSrcManagerListener);
	virtual ~CLiveManager();
	bool createLiveAndJoin(string strName, int chatroomType, int channelType);

	/*
	 * �ϱ�chatroom �� channelID
	 */
	bool reportChatRoomAndChannel(string strName, string strChatroomId, string strChannelId);

	bool joinLive(string strChatroomId, string strChannelId, bool bSelfCreate);

	/*
	 * ��������������
	 */
	bool setStreamConfig(int* sendBuf, int length);
	bool closeLive();
	
public:
	IVdnManagerListener* m_pVdnManagerListener;
	ISrcManagerListener* m_pSrcManagerListener;
	CUserManager* m_pUserManager;
	CChatroomManager* m_pChatroomManager;
	ILiveInterface* m_pLiveInterface;
};

