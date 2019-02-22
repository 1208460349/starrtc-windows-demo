#pragma once

#ifndef MATH_API
#define MATH_API _declspec(dllexport)
#endif


#include "CUserManager.h"
#include "IStarIMC2CListener.h"
#include "IStarIMChatroomListener.h"
#include "IVdnListener.h"
#include "ISrcListener.h"
#include "IGroupListener.h"


class MATH_API StarRtcCore
{
private:
	StarRtcCore(CUserManager* pUserManager);
	
public:
	static StarRtcCore* getStarRtcCoreInstance(CUserManager* pUserManager);
	
	~StarRtcCore();

	void registerCallback();

	/**
	 * ���C2C��Ϣ����
	 * @param listener
	 */
	void addC2CListener(IStarIMC2CListener* listener);

	/**
	 * ���group��Ϣ����
	 * @param listener
	 */
	void addGroupListener(IGroupListener* listener);

	/**
	 * ���StarIMChatroom��Ϣ����
	 * @param listener
	 */
	void addStarIMChatroomListener(IStarIMChatroomListener* listener);

	/**
	 * ���Vdn��Ϣ����
	 * @param listener
	 */
	void addVdnListener(IVdnListener* pVdnListener);

	/**
	 * ���Src��Ϣ����
	 * @param listener
	 */
	void addSrcListener(ISrcListener* pSrcListener);
	
	/**
	 * ����IM����
	 */
	bool startIMServer();

	/**
	 * ֹͣIM����
	 */
	bool stopIMServer();

	/**
	 * ������Ϣ
	 */
	bool sendMessage(CIMMessage* pIMMessage);

	/**
	 * ����������Ϣ
	 */
	bool sendOnlineMessage(CIMMessage* pIMMessage);

	/**
	 * ����Ⱥ����Ϣ
	 */
	int sendGroupMsg(CIMMessage* pIMMessage);
	
	/**
	 * ���봴��Ⱥ��
	 */
	int applyCreateGroup(char* addUsers, char* userDefineData);
	
	/**
	 * ����ɾ��
	 */
	int applyDelGroup(char* groupId);

	/**
	 * ������Ⱥ������û�
	 */
	int applyAddUserToGroup(char* groupId, char* addUsers, char* userDefineData);
	
	/**
	 * �����Ƴ�Ⱥ���û�
	 */
	int applyRemoveUserToGroup(char* groupId, char* removeUsers);
	
	/**
	 * ����ϵͳ��Ϣ��ָ���û�
	 */
	int sendSystemMsgToUser(char* sendUsers, int msgDataType, char* msgStr, char* msgDigest);
	
	/**
	 * ����ϵͳ��Ϣ��Ⱥ��
	 */
	int sendSystemGroupMsg(char* groupId, int msgDataType, char* msgStr, char* msgDigest);
	
	/**
	 * �������Ⱥ����Ϣ
	 */
	int applySetGroupPushIgnore(char* groupId);
	
	/**
	 * ����ȡ������Ⱥ����Ϣ
	 */
	int applyUnsetGroupPushIgnore(char* groupId);
	
	/**
	 * ��������ģʽ
	 */
	int setPushMode(char* pushMode);
	
	/**
	 * ��ȡ����ģʽ
	 */
	int getPushMode();

	/*
	 * ����ChatRoom
	 */
	bool createChatRoom(string serverIp, int serverPort, string strName, int chatroomType);

	/*
	 * ����ChatRoom
	 */
	bool joinChatRoom(string serverIp, int serverPort, string strChatroomId);
	/*
	 * ��ѯchatroom��������
	 */
	bool getOnlineNumber(string strChatroomId);

	bool banToSendMsg(char* banUserId, int banTime);
	bool kickOutUser(char* kickOutUserId);
	bool sendChat(CIMMessage* pIMMessage);
	bool sendPrivateChat(char* toUserId, char* msgData);
	bool deleteChatRoom();

	/*
	 *  ��ChatRoom�Ͽ�����
	 */
	bool stopChatRoomConnect();

	/*
	 * Channel ��������
	 */
	bool applyDownload(string serverIp, int port, string channelId);

	/*
	 * Channel ֹͣ����
	 */
	bool stopDownload();

	/*
	 * ��������������
	 */
	bool setStreamConfig(int* sendBuf, int length);

	void setGlobalSetting(int videoEnable, int audioEnable,
		int videoBigIsHw,
		int videoBigWidth, int videoBigHeight, int videoBigFps, int videoBigBitrate,
		int videoSmallWidth, int videoSmallHeight, int videoSmallFps, int videoSmallBitrate,
		int openGLESEnable, int dynamicBitrateAndFpsEnable, int voipP2PEnable);


	/*
	 * ����Channel
	 */
	bool createPublicChannel(string strServerIp, int port, string strName, int channelType, string strChatroomId);
	int startLiveSrcEncoder(int audioSampleRateInHz, int audioChannels, int audioBitRate, int rotation);
	int startUploadSrcServer(char* servAddr, int servPort, char* agentId, char* userId, char* starToken, char* channelId/* ,int maxAudioPacketNum,int maxVideoPacketNum */);
	int stopUploadSrcServer();
	int stopLiveSrcCodec();

	//=========================================================================
	//===========================    Msg�ص�    ===========================
	//=========================================================================
	/**
	 * msgServer����,������������̵߳���
	 */
	static int msgErr(char* errString, void* userData);

	/**
	 * ���Զ�κ��Բ������ӵ�msgServer�����û���������stop��ص�
	 */
	static int stop(void* userData);

	/**
	 * msgServer��������״̬
	 */
	static int online(int maxContentLen, void* userData);

	/**
	 * msgServer�ж�״̬
	 */
	static int offline(void* userData);

	/**
	 * ������Ϣ��Ⱥ��Ϣ��δͬ����ɣ��ȴ�5������
	 */
	static int groupIsSyncing(char* groupId, void* userData);

	/**
	 * �յ�������Ϣ���ͳɹ�����
	 */
	static int sendMsgFin(int msgIndex, char* toUserId, uint32_t time, void* userData);

	/**
	 * �յ�������Ϣ
	 */
	static int getNewMsg(char* fromUserId, uint32_t time, char* msgData, void* userData);

	/**
	 * �յ�Ⱥ��Ϣ
	 */
	static int getNewGroupMsg(char* groupId, char* fromUserId, uint32_t time, char* msgData, void* userData);

	/**
	 * �յ�Ⱥ������Ϣ
	 */
	static int getGroupSystemMsg(char* groupId, uint32_t time, char* msgData, void* userData);

	/**
	 * �յ�ϵͳ������Ϣ
	 */
	static int getSystemMsg(uint32_t time, char* msgData, void* userData);

	/**
	 * ���漸��������status����Ϊ����״̬��
	 * status�����ִ�:
	 * AECERRID_AEC_AUTH_FAILED, //AEC��Ȩʧ��
	 * AECERRID_AEC_URL_CONNECT_FAILED, //AEC url����ʧ��
	 * AECERRID_AEC_RESPONSE_JSON_PARSE_ERR, //AEC���ص�json��ʽ��������
	 * GROUPPUSH_ERRID_GROUPID_IS_SYNCING
	 * GROUPPUSH_ERRID_USERID_IS_NOT_IN_GROUP, //���û�����ָ����Ⱥ��
	 * �յ�Ⱥ��Ϣ���ͳɹ�����
	 */
	static int sendGroupMsgFin(char* status, int groupMsgIndex, char* groupId, uint32_t time, void* userData);
	static int applyCreateGroupFin(char* status, int reqIndex, char* groupId, void* userData);
	static int applyDelGroupFin(char* status, int reqIndex, char* groupId, void* userData);
	static int applyAddUserToGroupFin(char* status, int reqIndex, char* groupId, void* userData);
	static int applyRemoveUserFromGroupFin(char* status, int reqIndex, char* groupId, void* userData);
	static int sendSystemMsgToUserFin(char* status, int reqIndex, void* userData);
	static int sendSystemGroupMsgFin(char* status, int reqIndex, char* groupId, void* userData);
	static int setPushModeOK(void* userData);
	static int setPushModeFailed(void* userData);
	static int getPushMode(char* pushMode, void* userData);
	static int setPushIgnoreFin(char* status, char* groupId, void* userData);
	static int unsetPushIgnoreFin(char* status, char* groupId, void* userData);

	//=========================================================================
	//===========================    live chatroom�ص�    ===========================
	//=========================================================================
	static int createChatroomOK(char* roomId, int maxContentLen, void* userData);

	static int createChatroomFailed(void* userData, char* errString);

	static int joinChatroomOK(char* roomId, int maxContentLen, void* userData);

	static int joinChatroomFailed(char* roomId, char* errString, void* userData);

	static int chatroomError(char* errString, void* userData);

	static int chatroomStop(void* userData);

	static int deleteChatroomOK(char* roomId, void* userData);
	static int deleteChatroomFailed(char* roomId, char* errString, void* userData);

	static int chatroomBanToSendMsgOK(char* banUserId, int banTime, void* userData);
	static int chatroomBanToSendMsgFailed(char* banUserId, int banTime, char* errString, void* userData);

	static int chatroomKickOutOK(char* kickOutUserId, void* userData);
	static int chatroomKickOutFailed(char* kickOutUserId, char* errString, void* userData);

	//������
	static int chatroomSendMsgBanned(unsigned int remainTimeSec, void* userData);
	//���߳�����
	static int chatroomKickedOut(void* userData);
	//�յ���Ϣ
	static int chatroomGetNewMsg(char* fromUserId, char* msgData, void* userData);
	//�յ�˽����Ϣ
	static int chatroomGetNewPrivateMsg(char* fromUserId, char* msgData, void* userData);
	//�յ�����������Ϣ
	static int chatroomGetRoomOnlineNumber(char* roomId, int onlineNum, void* userData);
	//��Ϣ����ʧ�ܣ�����
	static int chatroomSendMsgNoFee(void* userData);


	//=========================================================================
	//===========================    liveVdn�ص�    ===========================
	//=========================================================================

	static int applyDownloadChannelOK(void* userData);
	static int applyDownloadChannelFailed(char* errString, void* userData);
	static int downloadChannelError(char* errString, void* userData);

	static int downloadStopOK(void* userData);
	static int downloadChannelClosed(void* userData);
	static int downloadChannelLeave(void* userData);

	static int downloadNetworkUnnormal(void* userData);
	static int queryVDNChannelOnlineNumberFin(char* channelId, int totalOnlineNum, void* userData);
	static int uploaderAdd(char* upUserId, int upId, void* userData);
	static int uploaderRemove(char* upUserId, int upId, void* userData);
	static int downloadStreamConfigOK(char* channelId, void* userData);
	static int downloadStreamConfigFailed(void* userData);
	static int getRealtimeData(int upId, uint8_t* data, int len, void* userData);

	//=========================================================================
	//===========================    liveSrc�ص�    ===========================
	//=========================================================================
	static int createChannelOK(char* channelId, void* userData);
	static int createChannelFailed(char* errString, void* userData);

	static int applyUploadChannelOK(char* channelId, void* userData);
	static int applyUploadChannelFailed(char* errString, char* channelId, void* userData);

	static int setUploaderOK(char* channelId, char* uploadUserId, void* userData);
	static int setUploaderFailed(char* errString, char* channelId, char* uploadUserId, void* userData);

	static int unsetUploaderOK(char* channelId, char* uploadUserId, void* userData);
	static int unsetUploaderFailed(char* errString, char* channelId, char* uploadUserId, void* userData);

	static int muteUploaderOK(char* channelId, char* uploadUserId, void* userData);
	static int muteUploaderFailed(char* errString, char* channelId, char* uploadUserId, void* userData);

	static int unmuteUploaderOK(char* channelId, char* uploadUserId, void* userData);
	static int unmuteUploaderFailed(char* errString, char* channelId, char* uploadUserId, void* userData);

	static int deleteChannelOK(char* channelId, void* userData);
	static int deleteChannelFailed(char* errString, char* channelId, void* userData);

	static int uploadUnseted(char* channelId, void* userData);
	static int uploadMuted(char* channelId, void* userData);
	static int uploadUnmuted(char* channelId, void* userData);

	static int setPeerStreamDownloadConfigOK(char* channelId, void* userData);
	static int setPeerStreamDownloadConfigFailed(char* channelId, void* userData);

	static int stopOK(void* userData);
	static int isRetrying(void* userData);
	static int networkUnnormal(void* userData);

	static int srcError(char* errString, void* userData);
	static int querySrcChannelOnlineNumberFin(char* channelId, int totalOnlineNum, void* userData);

	static int uploaderAddSrc(char* upUserId, int upId, void* userData);
	static int uploaderRemoveSrc(char* upUserId, int upId, void* userData);
	static int getRealtimeDataSrc(int upId, uint8_t* data, int len, void* userData);
	
	
	
	static int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen, void* userData);

public:
	CUserManager* m_pUserManager;
private:
	IStarIMC2CListener* m_pc2cMsgListener;
	IGroupListener* m_pGroupMsgListener;
	IStarIMChatroomListener *m_pStarIMChatroomListener;
	IVdnListener* m_pVdnListener;
	ISrcListener* m_pSrcListener;
//	static StarRtcCore* m_pStarRtcCore;
	int m_groupReqIndex;
};
