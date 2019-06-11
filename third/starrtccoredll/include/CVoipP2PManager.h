#pragma once
#include "IStarVoipP2PListener.h"
#include "IVoipP2PManagerListener.h"
#include "IRecvDataListener.h"
#include "CCodecManager.h"
#include <map>
using namespace std;
class CVoipP2PManager : public IStarVoipP2PListener, public IRecvDataListener
{
public:
	CVoipP2PManager(CUserManager* pUserManager, IVoipP2PManagerListener* pVoipManagerListener);
	virtual ~CVoipP2PManager();
public:
	void setUserId(string strUserId);
	int init();
	void stopVoip();

	/**
	 * ����ý�����ͣ�����Ƶ����Ƶ����Ƶ ���ֿ�ѡ��
	 * @param mediaTypeEnum ý������
	 */
	void setRtcMediaType(int mediaTypeEnum);

	/**
	 * ��ȡý�����ͣ�����Ƶ����Ƶ����Ƶ ���ֿ�ѡ��
	 */
	int getRtcMediaType();
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
	void sendControlMsg(int msgType, string strTargetId);

	/**
	 * ����
	 */
	virtual void onError(string code);

	/**
	 * �ѹر�
	 */
	virtual void onStop(string code);

	/**
	 * �յ�ʵʱ����
	 */
	virtual void onRevRealtimeData(uint8_t* bytes, int length);

	virtual void onP2PConnectSuccess();
	virtual void onP2PConnectFailed();

	/**
	 * �յ���Ϣ
	 * @param message
	 */
	virtual void onReceiveMessage(CIMMessage* pMessage);

	virtual int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen);

	void insertAudioRaw(uint8_t* audioData, int dataLen);
	//videoData���ͷ��ɴ˺�������
	void insertVideoNalu(uint8_t* videoData, int dataLen);
	//videoData���ͷ��ɴ˺�������
	void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);
	
	void querySoundData(uint8_t** pData, int* nLength);
private:
	IVoipP2PManagerListener* m_pVoipManagerListener;
	CCodecManager* m_pCodecManager;
	CUserManager* m_pUserManager;
	string m_strTargetId;
	string m_strUserId;
	map<string, string> m_RecvControlMsg;
	bool m_bCalling;
	bool m_bBusy;
	bool m_bInit;
	int m_nServerPort;
};

