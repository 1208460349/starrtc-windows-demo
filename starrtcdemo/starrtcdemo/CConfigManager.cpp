#pragma once
#include "stdafx.h"
#include "CConfigManager.h"
#include <string>
using namespace std;

CConfigManager::CConfigManager()
{
	readConfig();
}
CConfigManager::~CConfigManager()
{
}

bool CConfigManager::readConfig()
{
	//��D��д��������ݿ�����ini�ļ���Ϣ��Ĭ����������
	string strPath = ".\\param.ini";
	//CFileFind finder;   //�����Ƿ����ini�ļ����������ڣ�������һ���µ�Ĭ�����õ�ini�ļ��������ͱ�֤�����Ǹ��ĺ������ÿ�ζ�����
	//BOOL ifFind = finder.FindFile(strPath);
	if (true)
	{

		char buf[256] = { 0 };
		::GetPrivateProfileString("param", "AEventCenterEnable", "", buf, sizeof(buf), strPath.c_str());
		int nAEventCenterEnable = atoi(buf);
		if (nAEventCenterEnable == 0)
		{
			m_bAEventCenterEnable = false;
		}
		else
		{
			m_bAEventCenterEnable = true;
		}
	}
	return true;
}
