#pragma once
#include "CIMMessage.h"
#include "ChatroomInfo.h"
#include <list>
using namespace std;
class IStarIMChatroomListener
{
public:
	//�����Ҵ����ɹ�
	virtual void chatroomCreateOK(string roomId, int maxContentLen) = 0;
	//�����Ҽ���ɹ�
	virtual void chatroomJoinOK(string roomId, int maxContentLen) = 0;
	//�����Ҵ���ʧ��
	virtual void chatroomCreateFailed(string errString) = 0;
	//�����Ҽ���ʧ��
	virtual void chatroomJoinFailed(string roomId, string errString) = 0;
	//�����ұ���
	virtual void chatRoomErr(string errString) = 0;
	//�����ҹرճɹ�
	virtual void chatroomStopOK() = 0;
	//��ѯ�������б�ص�
	virtual int chatroomQueryAllListOK(list<ChatroomInfo>& chatRoomInfoList) = 0;
	//������ɾ���ɹ�
	virtual void chatroomDeleteOK(string roomId) = 0;
	//������ɾ��ʧ��
	virtual void chatroomDeleteFailed(string roomId, string errString) = 0;
	//�����ҽ��Գɹ�
	virtual void chatroomBanToSendMsgOK(string banUserId, int banTime) = 0;
	//�����ҽ���ʧ��
	virtual void chatroomBanToSendMsgFailed(string banUserId, int banTime, string errString) = 0;
	//���������˳ɹ�
	virtual void chatroomKickOutOK(string kickOutUserId) = 0;
	//��������
	virtual void chatroomSendMsgNoFee() = 0;
	//����������ʧ��
	virtual void chatroomKickOutFailed(string kickOutUserId, string errString) = 0;
	//������ �Լ�������
	virtual void chatroomSendMsgBanned(int remainTimeSec) = 0;
	//������ �Լ����߳�
	virtual void chatroomKickedOut() = 0;
	//������ �յ���Ϣ
	virtual void chatroomGetNewMsg(CIMMessage* pMsg) = 0;
	//������ �յ�˽����Ϣ
	virtual void chatroomGetNewPrivateMsg(CIMMessage* pMsg) = 0;
	//��������������
	virtual void getRoomOnlineNumber(string roomId, int number) = 0;
	//��������������
	virtual void sendMessageSuccess(int msgIndx) = 0;
	//��������������
	virtual void sendMessageFailed(int msgIndx) = 0;
	//�յ�������Ϣ
	virtual void revControlMessage(string fromID, int code) = 0;
};
