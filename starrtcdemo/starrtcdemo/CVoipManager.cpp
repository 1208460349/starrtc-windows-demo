#include "stdafx.h"
#include "CVoipManager.h"
#include "StarRtcCore.h"
#include "StarIMMessageType.h"
#include "CropType.h"
#include "CUtil.h"
bool CVoipManager::m_bCalling = false;
CVoipManager::CVoipManager(CUserManager* pUserManager, IVoipManagerListener* pVoipManagerListener)
{
	m_pVoipManagerListener = pVoipManagerListener;
	m_pUserManager = pUserManager;
	m_pChatManager = new CChatManager(m_pUserManager, this);
	m_pCodecManager = new CCodecManager(pUserManager);
	StarRtcCore::getStarRtcCoreInstance()->addRecvDataListener(this);
	StarRtcCore::getStarRtcCoreInstance()->addVoipListener(this);
	m_bInit = false;
	m_nServerPort = 10086;
}

CVoipManager::~CVoipManager()
{
	if (m_bInit)
	{
		stopVoip(true);
		StarRtcCore::getStarRtcCoreInstance()->stopLiveSrcCodec();
	}
	StarRtcCore::getStarRtcCoreInstance()->addRecvDataListener(NULL);
	StarRtcCore::getStarRtcCoreInstance()->addVoipListener(NULL);
}

int CVoipManager::init()
{
	m_bInit = true;
	CPicSize bigSize;
	CPicSize smallSize;
	CropTypeInfo::getCropSize((CROP_TYPE)m_pUserManager->m_ServiceParam.m_CropType, bigSize, smallSize);
	printf("globalSetting w:%d, h:%d, \n", bigSize.m_nWidth, bigSize.m_nHeight);
	int nP2P = 0;
	if (m_pUserManager->m_bVoipP2P)
	{
		nP2P = 1;
	}
	StarRtcCore::getStarRtcCoreInstance()->setGlobalSetting(1, 1,
		0,
		bigSize.m_nWidth, bigSize.m_nHeight, 15, 1024,
		smallSize.m_nWidth, smallSize.m_nHeight, 15, 1024,
		0, 0, nP2P);
	return StarRtcCore::getStarRtcCoreInstance()->startVoipEncoder(m_pUserManager->m_AudioParam.m_nSampleRateInHz, m_pUserManager->m_AudioParam.m_nChannels, m_pUserManager->m_AudioParam.m_nBitRate, 0);
}

void CVoipManager::stopVoip(int isActive)
{
	StarRtcCore::getStarRtcCoreInstance()->stopVoip(isActive);
}
/**
 * ���з�����
 * ����ͨ��
 * @param toID
 * @param callback
 */
bool CVoipManager::call(string strTargetId)
{
	if (CVoipManager::m_bCalling == true)
	{
		return false;
	}
	m_strTargetId = strTargetId;
	CVoipManager::m_bCalling = true;
	StarRtcCore::getStarRtcCoreInstance()->voipCalling((char*)(m_pUserManager->m_ServiceParam.m_strVOIPServiceIP.c_str()),
																	m_nServerPort,
																	(char*)m_pUserManager->m_ServiceParam.m_strAgentId.c_str(),
																	(char*)m_pUserManager->m_ServiceParam.m_strUserId.c_str(),
																	(char*)m_pUserManager->m_strTokenId.c_str(),
																	(char*)strTargetId.c_str());
	return true;
}

/**
 * ���з�����
 * �Է�������ܾ�ǰ ���з�����ȡ������
 * @param callback
 */
void CVoipManager::cancel()
{
	if (CVoipManager::m_bCalling)
	{
		CVoipManager::m_bCalling = false;
		sendControlMsg(CONTROL_CODE_VOIP_HANGUP);
		stopVoip(1);
		m_strTargetId = "";
	}
}
	
	

/**
 * ���з�����
 * ͬ������з�ͨ��
 * @param fromID
 * @param callback
 */
void CVoipManager::accept(string fromID)
{
	m_strTargetId = fromID;
	CVoipManager::m_bCalling = true;
	sendControlMsg(CONTROL_CODE_VOIP_CONNECT);
	StarRtcCore::getStarRtcCoreInstance()->voipResponse((char*)m_pUserManager->m_ServiceParam.m_strVOIPServiceIP.c_str(),
																		m_nServerPort,
																		(char*)m_pUserManager->m_ServiceParam.m_strAgentId.c_str(),
																		(char*)m_pUserManager->m_ServiceParam.m_strUserId.c_str(),
																		(char*)m_pUserManager->m_strTokenId.c_str(), 
																		(char*)fromID.c_str());
}

/**
 * ���з�����
 * �ܾ������з�ͨ��
 * @param callback
 */
void CVoipManager::refuse()
{
	sendControlMsg(CONTROL_CODE_VOIP_REFUSE);
}

/**
 * ˫�����ɵ���
 * �Ҷ�
 * @param callback
 */
void CVoipManager::hangup(int isActive)
{
	if (CVoipManager::m_bCalling)
	{
		CVoipManager::m_bCalling = false;
		sendControlMsg(CONTROL_CODE_VOIP_HANGUP);
		stopVoip(isActive);
		m_strTargetId = "";
	}
}

void CVoipManager::sendMsg(string toId, string msg)
{
	m_pChatManager->sendMessage((char*)toId.c_str(), (char*)msg.c_str());
}

void CVoipManager::sendControlMsg(int msgType)
{
	string strData = "{\\\"VoIP_protocal_type\\\":\\\"TCP\\\",\\\"VoIP_server_IP\\\":\\\"";
	strData = strData + m_pUserManager->m_ServiceParam.m_strVOIPServiceIP;
	strData = strData + "\\\",";
	strData = strData + "\\\"VoIP_server_Port\\\":";
	char buf[255] = { 0 };
	_itoa_s(m_nServerPort, buf, sizeof(buf), 10);
	strData = strData + buf;

	strData = strData + ",\\\"ts\\\":";
	_i64toa_s(CUtil::getCurrentTime(), buf, sizeof(buf), 10);
	strData = strData + buf;
	strData = strData + "}";
	if (CONTROL_CODE_VOIP_CONNECT == msgType)
	{
		strData = "";
	}
	//��Է�������Ϣ��������
	m_pChatManager->sendVoipOnlineMessage((char*)m_pUserManager->m_ServiceParam.m_strUserId.c_str(),
		(char*)m_strTargetId.c_str(),
		msgType,
		(char*)strData.c_str());
}

void CVoipManager::voipStopOK(int stopType)
{
	CVoipManager::m_bCalling = false;
	
	m_bInit = false;
}

//������յ�calling���󣬴�ʱ�ͻ��˿���ͨ����Ϣϵͳ֪ͨ�Է�
void CVoipManager::voipCallingAck()
{
	if (CVoipManager::m_bCalling)
	{
		sendControlMsg(CONTROL_CODE_VOIP_CALL);
	}
}

//callingʧ��
void CVoipManager::voipCallingFailed(char* errString)
{
	CVoipManager::m_bCalling = false;
	if (m_pVoipManagerListener != NULL)
	{
		m_pVoipManagerListener->onError(errString);
	}
}

//���շ�׼���ã����Կ�ʼ��������
void CVoipManager::voipResponseOk()
{
	init();

	if (m_pVoipManagerListener != NULL)
	{
		m_pVoipManagerListener->onConnected(m_strTargetId);
	}
}

//responseʧ��
void CVoipManager::voipResponseFailed(char* errString)
{
	if (m_pVoipManagerListener != NULL)
	{
		m_pVoipManagerListener->onError(errString);
	}
}

//���ͷ�׼���ã����Կ�ʼ��������
void CVoipManager::voipCallingOk()
{
	init();

	if (m_pVoipManagerListener != NULL)
	{
		m_pVoipManagerListener->onConnected(m_strTargetId);
	}
}

int CVoipManager::voipError(char* errString)
{
	string str = "VOIP_MOONSERVER_ERRID_FAR_DISCONNECTED";
	string strErr = errString;
	CVoipManager::m_bCalling = false;
	if (m_pVoipManagerListener != NULL)
	{
		if (strErr != str)
		{
			m_pVoipManagerListener->onError(errString);
		}
		else
		{
			m_pVoipManagerListener->onHangup(m_strTargetId);
		}
	}
	return 0;
}
int CVoipManager::voipSpeedTestFinish(char* userIp, int uploadVariance, int uploadSpeed, int downloadVariance, int downSpeed)
{
	return 0;
}

int CVoipManager::voipEchoTestFinish(int index, int len, int timeCost)
{
	return 0;
}

int CVoipManager::voipGetRealtimeData(uint8_t* data, int len)
{
	return 0;
}

int CVoipManager::reportVoipTransState(int state)
{
	if (state == 1)
	{
		AfxMessageBox("��ǰ״̬ΪP2P");
	}
	else
	{
		AfxMessageBox("��ǰ״̬Ϊ��ת");
	}
	return 0;
}
void CVoipManager::insertAudioRaw(uint8_t* audioData, int dataLen)
{
	if (m_bInit && m_pCodecManager != NULL)
	{
		uint8_t* insertData = NULL;
		StarRtcCore::getStarRtcCoreInstance()->starRTCMalloc(&insertData, dataLen);
		if (insertData != NULL)
		{
			memcpy(insertData, audioData, sizeof(uint8_t)*dataLen);
			m_pCodecManager->insertAudioRaw(insertData, dataLen);
		}
	}
}
void CVoipManager::insertVideoNalu(uint8_t* videoData, int dataLen)
{
	if (m_bInit && m_pCodecManager != NULL)
	{
		m_pCodecManager->insertVideoNalu(videoData, dataLen);
	}
}

//videoData���ͷ��ɴ˺�������
void CVoipManager::insertVideoRaw(uint8_t* videoData, int dataLen, int isBig)
{
	if (m_bInit && m_pCodecManager != NULL)
	{
		uint8_t* insertData = NULL;
		StarRtcCore::getStarRtcCoreInstance()->starRTCMalloc(&insertData, dataLen);
		if (insertData != NULL)
		{
			memcpy(insertData, videoData, sizeof(uint8_t)*dataLen);
			m_pCodecManager->insertVideoRaw(insertData, dataLen, isBig);
		}
	}
}
int CVoipManager::cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall)
{
	int nRet = 0;
	if (m_pCodecManager != NULL)
	{
		nRet = m_pCodecManager->cropVideoRawNV12(w, h, videoData, dataLen, yuvProcessPlan, rotation, needMirror, outVideoDataBig, outVideoDataSmall);
	}
	return nRet;
}

int CVoipManager::getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen)
{
	if (m_pVoipManagerListener != NULL)
	{
		m_pVoipManagerListener->getVideoRaw(upId, w, h, videoData, videoDataLen);
	}
	return 0;
}

void CVoipManager::onNewMessage(CIMMessage* var1)
{
	if (var1->m_nType == MSG_TYPE_CONTROL)
	{
		switch (var1->m_nCode)
		{
		case CONTROL_CODE_VOIP_CALL:
		{
			if (m_pVoipManagerListener != NULL)
			{
				map<string,string>::iterator iter = m_RecvControlMsg.find(var1->m_strFromId);
				if (iter != m_RecvControlMsg.end())
				{
					if (iter->second == var1->m_strContentData)
					{
						//�ظ�����
					}
					else
					{
						if (CVoipManager::m_bCalling)
						{
							sendControlMsg(CONTROL_CODE_VOIP_BUSY);
						}
						else
						{
							m_pVoipManagerListener->onCalling(var1->m_strFromId);
							iter->second = var1->m_strContentData;
						}
							
					}
				}
				else
				{
					if (CVoipManager::m_bCalling)
					{
						sendControlMsg(CONTROL_CODE_VOIP_BUSY);
					}
					else
					{
						m_pVoipManagerListener->onCalling(var1->m_strFromId);
						m_RecvControlMsg[var1->m_strFromId] = var1->m_strContentData;
					}	
				}	
			}
		}
			break;
		case CONTROL_CODE_VOIP_REFUSE:
		{
			if (m_pVoipManagerListener != NULL)
			{
				m_pVoipManagerListener->onRefused(var1->m_strFromId);
			}
		}
			break;
		case CONTROL_CODE_VOIP_HANGUP:
		{
			if (m_pVoipManagerListener != NULL)
			{
				m_pVoipManagerListener->onHangup(var1->m_strFromId);
			}
		}
			break;
		case CONTROL_CODE_VOIP_BUSY:
		{
			if (m_pVoipManagerListener != NULL)
			{
				m_pVoipManagerListener->onBusy(var1->m_strFromId);
			}
		}
			break;
		case CONTROL_CODE_VOIP_CONNECT:
		{
			CVoipManager::m_bCalling = true;
			m_strTargetId = var1->m_strFromId;
		}
			break;
		default:
			break;
		}
	}
	else
	{
		m_pVoipManagerListener->onNewMessage(var1);
	}
}

void CVoipManager::onSendMessageSuccess(int msgIndex)
{
}

void CVoipManager::onSendMessageFailed(int msgIndex)
{
}

void CVoipManager::querySoundData(uint8_t** pData, int* nLength)
{
	if (m_pCodecManager != NULL)
	{
		m_pCodecManager->querySoundData(pData, nLength);
	}
}

