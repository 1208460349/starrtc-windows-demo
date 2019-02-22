#pragma once

#include "CUserManager.h"
class ILiveInterface
{
public:
	ILiveInterface(CUserManager* pUserManager);
	virtual ~ILiveInterface();

	void setChannelId(string strChannelId);

	/*
	 * ��������������
	 */
	bool setStreamConfig(int* sendBuf, int length);

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
protected:
	CUserManager* m_pUserManager;
	string m_ChannelId;

	bool m_bReturn;
	bool m_bSuccess;
	string m_strErrInfo;
};

