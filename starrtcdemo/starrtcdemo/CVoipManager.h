#pragma once
#include "IStarVoipListener.h"
#include "IVoipManagerListener.h"
#include "IRecvDataListener.h"
#include "IResultCallback.h"
#include "CCodecManager.h"
#include "CChatManager.h"

class CVoipManager : public IStarVoipListener, public IRecvDataListener, public IStarIMC2CListener
{
public:
	CVoipManager(CUserManager* pUserManager, IVoipManagerListener* pVoipManagerListener);
	virtual ~CVoipManager();
public:
	int init();
	void stopVoip(int isActive);
	/**
	 * ���з�����
	 * ����ͨ��
	 * @param toID
	 * @param callback
	 */
	bool call(string strTargetId);

	/**
	* ���з�����
	* �Է�������ܾ�ǰ ���з�����ȡ������
	*/
	void cancel();

	/**
	 * ���з�����
	 * ͬ������з�ͨ��
	 * @param fromID
	 */
	void accept(string fromID);

	/**
	 * ���з�����
	 * �ܾ������з�ͨ��
	 */
	void refuse();

	/**
	 * ˫�����ɵ���
	 * �Ҷ�
	 */
	void hangup(int isActive);
	void sendMsg(string toId, string msg);
	void sendControlMsg(int msgType);
	virtual void voipStopOK(int stopType);
	//������յ�calling���󣬴�ʱ�ͻ��˿���ͨ����Ϣϵͳ֪ͨ�Է�
	virtual void voipCallingAck();
	//callingʧ��
	virtual void voipCallingFailed(char* errString);
	//���շ�׼���ã����Կ�ʼ��������
	virtual void voipResponseOk();
	//responseʧ��
	virtual void voipResponseFailed(char* errString);
	//���ͷ�׼���ã����Կ�ʼ��������
	virtual void voipCallingOk();
	virtual int voipError(char* errString);
	virtual int voipSpeedTestFinish(char* userIp, int uploadVariance, int uploadSpeed, int downloadVariance, int downSpeed);
	virtual int voipEchoTestFinish(int index, int len, int timeCost);
	virtual int voipGetRealtimeData(uint8_t* data, int len);
	virtual int reportVoipTransState(int state);
	void insertAudioRaw(uint8_t* audioData, int dataLen);
	//videoData���ͷ��ɴ˺�������
	void insertVideoNalu(uint8_t* videoData, int dataLen);
	//videoData���ͷ��ɴ˺�������
	void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);
	virtual int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen);

	// msg callback
	virtual void onNewMessage(CIMMessage* var1);
	virtual void onSendMessageSuccess(int msgIndex);
	virtual void onSendMessageFailed(int msgIndex);

	void querySoundData(uint8_t** pData, int* nLength);
private:
	IVoipManagerListener* m_pVoipManagerListener;
	CChatManager* m_pChatManager;
	CCodecManager* m_pCodecManager;
	CUserManager* m_pUserManager;
	IResultCallback* m_pResultCallback;
	string m_strTargetId;
	map<string, string> m_RecvControlMsg;
	static bool m_bCalling;
	bool m_bInit;
	int m_nServerPort;
};

