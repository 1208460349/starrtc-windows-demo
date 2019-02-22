#pragma once
#include<string>
using namespace std;
#include "CUserManager.h"
class CLogin
{
public:
	CLogin(CUserManager* pUserManager);

	~CLogin();

	bool readConfig();
	bool writeConfig();
	string getServiceParam();

	/*
	 * ��¼
	 */
	bool logIn();

	/*
	 * ��ȡauthKey
	 */
	bool getAuthKey(string userId);

	/*
	 * ��ȡToken
	 */
	bool getToken(string userId, string agentId, string authKey);

	/*
	 * ͨ�����Ȼ�ȡIM�����ַ
	 */
	bool getIMServerAddr(string userId, string agentId);

	/*
	 * ����IM����
	 */
	bool startIMServer(string strIP, int nPort, string userId, string agentId, string strToken);

	/*
	 * ����IM����
	 */
	bool stopIMServer();

	/*
	 * ����IM����
	 */
	string getUserManagerInfo();
private:
	CUserManager* m_pUserManager;
};

