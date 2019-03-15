#pragma once
#include "IChatroomManagerListener.h"
#include "IStarIMChatroomListener.h"
#include "CUserManager.h"
#include <string>
using namespace std;

enum CHATROOM_TYPE
{
	CHATROOM_TYPE_UNABLE,	// ռλ
	CHATROOM_TYPE_PUBLIC,	// �����¼����֤
	CHATROOM_TYPE_LOGIN		// ��Ҫ��¼��������֤
};

class CChatroomManager : public IStarIMChatroomListener
{
public:
	CChatroomManager(CUserManager* pUserManager, IChatroomManagerListener* pChatroomManagerListener);
	~CChatroomManager();
public:
	void resetReturnVal();
	/*
	 * ����chatroom id
	 */
	void setChatroomId(string chatRoomId);

	/*
	 * ͨ�����Ȼ�ȡChatRoom�����ַ
	 */
	bool getChatRoomServerAddr();

	/*
	 * ����ChatRoom
	 */
	bool createChatRoom(string strName, int chatroomType);

	/*
	 * ����ChatRoom
	 */
	bool joinChatRoom();
	/*
	 * ��ѯchatroom��������
	 */
	bool getOnlineNumber(string strChatroomId);

	bool banToSendMsg(char* banUserId, int banTime);
	bool kickOutUser(char* kickOutUserId);
	bool sendChat(CIMMessage* pIMMessage);
	bool sendPrivateChat(string toUserId, char* msgData);
	bool sendChatroomPrivateControlMessage(string targetId, int code);
	bool deleteChatRoom();

	bool reportChatroom(string strName, string strRoomId);

	/*
	 *  ��ChatRoom�Ͽ�����
	 */
	bool stopChatRoomConnect();

	bool exit();

public:
	/**
	 * �����Ҵ����ɹ�
	 */
	virtual void chatroomCreateOK(string roomId, int maxContentLen);

	/**
	 * �����Ҽ���ɹ�
	 */
	virtual void chatroomJoinOK(string roomId, int maxContentLen);

	/**
	 * �����Ҵ���ʧ��
	 */
	virtual void chatroomCreateFailed(string errString);

	/**
	 * �����Ҽ���ʧ��
	 */
	virtual void chatroomJoinFailed(string roomId, string errString);

	/**
	 * �����ұ���
	 */
	virtual void chatRoomErr(string errString);

	/**
	 * �����ҹرճɹ�
	 */
	virtual void chatroomStopOK();

	/**
	 * ������ɾ���ɹ�
	 */
	virtual void chatroomDeleteOK(string roomId);

	/**
	 * ������ɾ��ʧ��
	 */
	virtual void chatroomDeleteFailed(string roomId, string errString);

	/**
	 * �����ҽ��Գɹ�
	 */
	virtual void chatroomBanToSendMsgOK(string banUserId, int banTime);

	/**
	 * �����ҽ���ʧ��
	 */
	virtual void chatroomBanToSendMsgFailed(string banUserId, int banTime, string errString);

	/**
	 * ���������˳ɹ�
	 */
	virtual void chatroomKickOutOK(string kickOutUserId);

	/**
	 * ��������
	 */
	virtual void chatroomSendMsgNoFee();

	/**
	 * ����������ʧ��
	 */
	virtual void chatroomKickOutFailed(string kickOutUserId, string errString);

	/**
	 * ������ �Լ�������
	 */
	virtual void chatroomSendMsgBanned(int remainTimeSec);

	/**
	 * ������ �Լ����߳�
	 */
	virtual void chatroomKickedOut();

	/**
	 * ������ �յ���Ϣ
	 */
	virtual void chatroomGetNewMsg(CIMMessage* pMsg);

	/**
	 * ������ �յ�˽����Ϣ
	 */
	virtual void chatroomGetNewPrivateMsg(CIMMessage* pMsg);

	/**
	 * ��������������
	 */
	virtual void getRoomOnlineNumber(string roomId, int number);

	/**
	 * ��������������
	 */
	virtual void sendMessageSuccess(int msgIndx);

	/**
	 * ��������������
	 */
	virtual void sendMessageFailed(int msgIndx);

	/**
	 * �յ�������Ϣ
	 */
	virtual void revControlMessage(string fromID, int code);

	/**
	 * �ɹ�
	 * @param data
	 */
	virtual void success();

	/**
	 * ʧ��
	 * @param errMsg
	 */
	virtual void failed(string errMsg);

	string getChatroomId();
private:
	
	CUserManager* m_pUserManager;
	IChatroomManagerListener* m_pChatroomManagerListener;
	string m_strChatRoomServerIp;
	int m_nChatRoomServerPort;

	bool m_bJoinChatRoom;

	bool m_bReturn;
	bool m_bSuccess;
	string m_strErrInfo;

	string m_ChatRoomId;
};

