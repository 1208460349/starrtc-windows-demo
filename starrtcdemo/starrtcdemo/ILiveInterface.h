#pragma once

#include "CUserManager.h"
enum LIVE_TYPE
{
	LIVE_TYPE_VDN,
	LIVE_TYPE_SRC
};
class ILiveInterface
{
public:
	ILiveInterface(CUserManager* pUserManager);
	virtual ~ILiveInterface();

	void setChannelId(string strChannelId);

	void resetReturnVal();

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

	string getChannelId();
	/*
	 * ��������������
	 */
	virtual bool setStreamConfig(int* sendBuf, int length) = 0;
public:
	LIVE_TYPE m_liveType;
protected:
	CUserManager* m_pUserManager;
	string m_ChannelId;

	bool m_bReturn;
	bool m_bSuccess;
	string m_strErrInfo;
	
};

