#include "stdafx.h"
#include "CInterfaceUrls.h"
#include "HttpClient.h"
#include "json.h"

string CInterfaceUrls::BASE_URL = "";
//��ȡauthKey
string CInterfaceUrls::LOGIN_URL = "";
//�������б�
string CInterfaceUrls::MEETING_LIST_URL = "";
//ֱ���б�
string CInterfaceUrls::LIVE_LIST_URL = "";
//��Ƶֱ���б�
string CInterfaceUrls::AUDIO_LIVE_LIST_URL = "";
//С����б�
string CInterfaceUrls::MINI_CLASS_LIST_URL = "";
//�ϱ�ֱ����ʹ�õ�������ID��ֱ�����������������һ�������ң�
string CInterfaceUrls::LIVE_SET_CHAT_URL = "";
//�������б�
string CInterfaceUrls::CHATROOM_LIST_URL = "";
//�Լ������Ⱥ�б�
string CInterfaceUrls::GROUP_LIST_URL = "";
//Ⱥ��Ա�б�
string CInterfaceUrls::GROUP_MEMBERS_URL = "";
//�����û��б�
string CInterfaceUrls::ONLINE_USER_LIST_URL = "";

//�ϱ�ֱ��
string CInterfaceUrls::REPORT_LIVE_INFO_URL = "";
//�ϱ�����ֱ��
string CInterfaceUrls::REPORT_AUDIO_LIVE_INFO_URL = "";
//�ϱ�С���
string CInterfaceUrls::REPORT_MINI_CLASS_INFO_URL = "";
//�ϱ�����
string CInterfaceUrls::REPORT_MEETING_INFO_URL = "";
//�ϱ�������
string CInterfaceUrls::REPORT_CHATROOM_INFO_URL = "";


//UTF8תANSI
string CInterfaceUrls::UTF8toANSI(string strUTF8)
{
	string retStr = "";
	//��ȡת��Ϊ���ֽں���Ҫ�Ļ�������С���������ֽڻ�����
	UINT nLen = MultiByteToWideChar(CP_UTF8, NULL, strUTF8.c_str(), -1, NULL, NULL);
	WCHAR *wszBuffer = new WCHAR[nLen + 1];
	nLen = MultiByteToWideChar(CP_UTF8, NULL, strUTF8.c_str(), -1, wszBuffer, nLen);
	wszBuffer[nLen] = 0;

	nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
	CHAR *szBuffer = new CHAR[nLen + 1];
	nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL);
	szBuffer[nLen] = 0;

	retStr = szBuffer;
	//�����ڴ�
	delete[]szBuffer;
	delete[]wszBuffer;
	return retStr;
}
//ANSIתUTF8
string CInterfaceUrls::ANSItoUTF8(string strAnsi)
{
	string retStr = "";
	//��ȡת��Ϊ���ֽں���Ҫ�Ļ�������С���������ֽڻ�������936Ϊ��������GB2312����ҳ
	UINT nLen = MultiByteToWideChar(936, NULL, strAnsi.c_str(), -1, NULL, NULL);
	WCHAR *wszBuffer = new WCHAR[nLen + 1];
	nLen = MultiByteToWideChar(936, NULL, strAnsi.c_str(), -1, wszBuffer, nLen);
	wszBuffer[nLen] = 0;
	//��ȡתΪUTF8���ֽں���Ҫ�Ļ�������С���������ֽڻ�����
	nLen = WideCharToMultiByte(CP_UTF8, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
	CHAR *szBuffer = new CHAR[nLen + 1];
	nLen = WideCharToMultiByte(CP_UTF8, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL);
	szBuffer[nLen] = 0;

	retStr = szBuffer;
	//�ڴ�����
	delete[]wszBuffer;
	delete[]szBuffer;
	return retStr;
}

CInterfaceUrls::CInterfaceUrls()
{
}


CInterfaceUrls::~CInterfaceUrls()
{
}

unsigned char CInterfaceUrls::ToHex(unsigned char x)
{
	return  x > 9 ? x + 55 : x + 48;
}

unsigned char CInterfaceUrls::FromHex(unsigned char x)
{
	unsigned char y;
	if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
	else if (x >= '0' && x <= '9') y = x - '0';
	else
	{
	}
	return y;
}

std::string CInterfaceUrls::UrlEncode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (isalnum((unsigned char)str[i]) ||
			(str[i] == '-') ||
			(str[i] == '_') ||
			(str[i] == '.') ||
			(str[i] == '~'))
			strTemp += str[i];
		else if (str[i] == ' ')
			strTemp += "+";
		else
		{
			strTemp += '%';
			strTemp += ToHex((unsigned char)str[i] >> 4);
			strTemp += ToHex((unsigned char)str[i] % 16);
		}
	}
	return strTemp;
}

std::string CInterfaceUrls::UrlDecode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (str[i] == '+') strTemp += ' ';
		else if (str[i] == '%')
		{
			unsigned char high = FromHex((unsigned char)str[++i]);
			unsigned char low = FromHex((unsigned char)str[++i]);
			strTemp += high * 16 + low;
		}
		else strTemp += str[i];
	}
	return strTemp;
}

void CInterfaceUrls::demoSaveToList(string userId, int listType, string id, string data)
{
	string url = "http://www.starrtc.com/aec/list/save.php";
	url = url + "?userId=" + userId + "&listType=";
	char buf[256] = { 0 };
	sprintf_s(buf, "%d", listType);
	url = url + buf;
	url = url + "&roomId=" + id;

	data = CInterfaceUrls::ANSItoUTF8(data);
	data = CInterfaceUrls::UrlEncode(data);

	url = url + "&data=" + data;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";
	string str_json = "";
	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
}

void CInterfaceUrls::demoDeleteFromList(string userId, int listType, string id)
{
	string url = "http://www.starrtc.com/aec/list/del.php";
	url = url + "?userId=" + userId + "&listType=";
	char buf[256] = { 0 };
	sprintf_s(buf, "%d", listType);
	url = url + buf;
	url = url + "&roomId=" + id;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";
	string str_json = "";
	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
}

void CInterfaceUrls::demoQueryList(string listType, list<ChatroomInfo>& listData)
{
	string url = "http://www.starrtc.com/aec/list/query.php";

	string strData = "listTypes=";
	strData = strData + listType;


	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);

	string str_json = strContent.GetBuffer(0);

	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��   
	{
		std::cout << "========================[Dispatch]========================" << std::endl;
		if (root.isMember("status") && root["status"].asInt() == 1)
		{
			if (root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				int nSize = data.size();
				for (int i = 0; i < nSize; i++)
				{
					if (data[i].isMember("data"))
					{
						string strVal = data[i].get("data", "").asCString();
						

						strVal = CInterfaceUrls::UrlDecode(strVal);
						strVal = CInterfaceUrls::UTF8toANSI(strVal);
						Json::Reader reader1;
						Json::Value root1;
						if (strVal != "" && reader1.parse(strVal, root1))
						{
							ChatroomInfo chatroomInfo;
							if (root1.isMember("id"))
							{
								chatroomInfo.m_strRoomId = root1["id"].asCString();
							}
							if (root1.isMember("name"))
							{
								chatroomInfo.m_strName = root1["name"].asCString();
							}
							if (root1.isMember("creator"))
							{
								chatroomInfo.m_strCreaterId = root1["creator"].asCString();
							}
							listData.push_back(chatroomInfo);
						}
					}
				}
			}
		}
	}
}

void CInterfaceUrls::demoQueryImGroupList(string userId, list<CGroupInfo>& groupInfoList)
{
	string url = "http://www.starrtc.com/aec/group/list.php";

	string strData = "userId=";
	strData = strData + userId;


	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);

	string str_json = strContent.GetBuffer(0);

	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��   
	{
		//{"status":1,"data":[{"groupName":"\u5403\u918b","creator":"448999","groupId":"100391"}]}
		if (root.isMember("status") && root["status"].asInt() == 1)
		{
			if (root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				int nSize = data.size();
				for (int i = 0; i < nSize; i++)
				{
					CGroupInfo groupInfo;
					if (data[i].isMember("groupName"))
					{
						groupInfo.m_strName = CInterfaceUrls::UrlDecode(data[i]["groupName"].asCString());
					}

					if (data[i].isMember("groupId"))
					{
						groupInfo.m_strId = data[i]["groupId"].asCString();
					}

					if (data[i].isMember("creator"))
					{
						groupInfo.m_strCreaterId = data[i]["creator"].asCString();
					}
					groupInfoList.push_back(groupInfo);
				}
			}
		}
	}
}

void CInterfaceUrls::demoQueryImGroupInfo(string userId, string groupId, CGroupMemoryInfo& userList)
{
	string url = "http://www.starrtc.com/aec/group/members.php";

	string strData = "userId=";
	strData = strData + userId+ "&groupId=" + groupId;


	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);

	string str_json = strContent.GetBuffer(0);

	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��   
	{
		//{"status":1,"data":{"userIdList":"448999","isIgnore":"0"}}
		if (root.isMember("status") && root["status"].asInt() == 1)
		{
			if (root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				if (data.isMember("userIdList"))
				{
					string strUserIdList = data["userIdList"].asCString();
					while (strUserIdList != "")
					{
						string strInfo = strUserIdList;
						int pos = strUserIdList.find(",");
						if (pos > 0)
						{
							strInfo = strUserIdList.substr(0, pos);
							strUserIdList = strUserIdList.substr(pos + 1, strUserIdList.length() - pos - 1);
						}
						else
						{
							strUserIdList = "";
						}
						userList.m_UserIdList.push_back(strInfo);
					}
				}
				if (data.isMember("isIgnore"))
				{
					string strIngore = data["isIgnore"].asCString();
					if (strIngore == "1")
					{
						userList.m_bIgnore = true;
					}
					else
					{
						userList.m_bIgnore = false;
					}
				}
				
			}
		}
	}
}

void CInterfaceUrls::setBaseUrl(string baseUrl)
{
	BASE_URL = baseUrl;
	LOGIN_URL = BASE_URL + "/authKey";
	MEETING_LIST_URL = BASE_URL + "/meeting/list";
	LIVE_LIST_URL = BASE_URL + "/live/list";
	AUDIO_LIVE_LIST_URL = BASE_URL + "/audio/list";
	MINI_CLASS_LIST_URL = BASE_URL + "/class/list";
	LIVE_SET_CHAT_URL = BASE_URL + "/live/set_chat";
	CHATROOM_LIST_URL = BASE_URL + "/chat/list";
	GROUP_LIST_URL = BASE_URL + "/group/list_all";
	ONLINE_USER_LIST_URL = BASE_URL + "/user/list";
	GROUP_MEMBERS_URL = BASE_URL + "/group/members";
	REPORT_LIVE_INFO_URL = BASE_URL + "/live/store";
	REPORT_AUDIO_LIVE_INFO_URL = BASE_URL + "/audio/store";
	REPORT_MINI_CLASS_INFO_URL = BASE_URL + "/class/store";
	REPORT_MEETING_INFO_URL = BASE_URL + "/meeting/store";
	REPORT_CHATROOM_INFO_URL = BASE_URL + "/chat/store";
}

void CInterfaceUrls::demoRequestMeetingList(list<ChatroomInfo>& listData, CUserManager* pUserManager)
{
	listData.clear();
	string strData = "appid=";
	strData = strData + pUserManager->m_ServiceParam.m_strAgentId.c_str();

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(MEETING_LIST_URL.c_str(), strData.c_str(), strContent);

	string str_json = strContent.GetBuffer(0);

	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��   
	{
		std::cout << "========================[Dispatch]========================" << std::endl;
		if (root.isMember("status") && root["status"].asInt() == 1)
		{
			if (root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				int nSize = data.size();
				for (int i = 0; i < nSize; i++)
				{
					ChatroomInfo chatroomInfo;
					if (data[i].isMember("Name"))
					{
						chatroomInfo.m_strName = data[i]["Name"].asCString();
					}

					if (data[i].isMember("ID"))
					{
						chatroomInfo.m_strRoomId = data[i]["ID"].asCString();
					}

					if (data[i].isMember("Creator"))
					{
						chatroomInfo.m_strCreaterId = data[i]["Creator"].asCString();
					}
					listData.push_back(chatroomInfo);
				}
			}
		}
	}
}
void CInterfaceUrls::demoRequestMiniClassList(list<ChatroomInfo>& listData, CUserManager* pUserManager)
{
	listData.clear();
	string strData = "appid=";
	strData = strData + "stargWeHN8Y7";

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(MINI_CLASS_LIST_URL.c_str(), strData.c_str(), strContent);
	string str_json = strContent.GetBuffer(0);

	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��   
	{
		std::cout << "========================[Dispatch]========================" << std::endl;
		if (root.isMember("status") && root["status"].asInt() == 1)
		{
			if (root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				int nSize = data.size();
				for (int i = 0; i < nSize; i++)
				{
					ChatroomInfo chatroomInfo;
					if (data[i].isMember("Name"))
					{
						chatroomInfo.m_strName = data[i]["Name"].asCString();
					}

					if (data[i].isMember("ID"))
					{
						chatroomInfo.m_strRoomId = data[i]["ID"].asCString();
					}

					if (data[i].isMember("Creator"))
					{
						chatroomInfo.m_strCreaterId = data[i]["Creator"].asCString();
					}
					listData.push_back(chatroomInfo);
				}
			}
		}
	}
}

//�������б�
void CInterfaceUrls::demoRequestChatroomList(list<ChatroomInfo>& listData, CUserManager* pUserManager)
{
	listData.clear();
	string strData = "appid=";
	strData = strData + pUserManager->m_ServiceParam.m_strAgentId.c_str();

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(CHATROOM_LIST_URL.c_str(), strData.c_str(), strContent);
	string str_json = strContent.GetBuffer(0);

	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��   
	{
		std::cout << "========================[Dispatch]========================" << std::endl;
		if (root.isMember("status") && root["status"].asInt() == 1)
		{
			if (root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				int nSize = data.size();
				for (int i = 0; i < nSize; i++)
				{
					ChatroomInfo chatroomInfo;
					if (data[i].isMember("Creator"))
					{
						chatroomInfo.m_strCreaterId = data[i]["Creator"].asCString();
					}

					if (data[i].isMember("ID"))
					{
						chatroomInfo.m_strRoomId = data[i]["ID"].asCString();
					}

					if (data[i].isMember("Name"))
					{
						chatroomInfo.m_strName = data[i]["Name"].asCString();
					}
					listData.push_back(chatroomInfo);
				}
			}
		}
	}
}
//Ⱥ�б�
void CInterfaceUrls::demoRequestGroupList(list<CGroupInfo>& retGroupList, CUserManager* pUserManager)
{
	retGroupList.clear();
	string strData = "userid=";
	strData = strData + pUserManager->m_ServiceParam.m_strUserId.c_str() + "&appid=" + pUserManager->m_ServiceParam.m_strAgentId.c_str();

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(GROUP_LIST_URL.c_str(), strData.c_str(), strContent);
	string str_json = strContent.GetBuffer(0);

	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��   
	{
		std::cout << "========================[Dispatch]========================" << std::endl;
		if (root.isMember("status") && root["status"].asInt() == 1)
		{
			if (root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				int nSize = data.size();
				for (int i = 0; i < nSize; i++)
				{
					CGroupInfo groupInfo;
					if (data[i].isMember("creator"))
					{
						groupInfo.m_strCreaterId = data[i]["creator"].asCString();
					}

					if (data[i].isMember("groupId"))
					{
						groupInfo.m_strId = data[i]["groupId"].asCString();
					}

					if (data[i].isMember("groupName"))
					{
						groupInfo.m_strName = data[i]["groupName"].asCString();
					}
					retGroupList.push_back(groupInfo);
				}
			}
		}
	}
}

//Ⱥ��Ա�б�
void CInterfaceUrls::demoRequestGroupMembers(string groupId, CUserManager* pUserManager, list<string>& userList)
{
	userList.clear();
	string strData = "groupId=";
	strData = strData + groupId.c_str() + "&appid=" + pUserManager->m_ServiceParam.m_strAgentId.c_str();

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(GROUP_MEMBERS_URL.c_str(), strData.c_str(), strContent);
	string str_json = strContent.GetBuffer(0);

	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��   
	{
		std::cout << "========================[Dispatch]========================" << std::endl;
		if (root.isMember("status") && root["status"].asInt() == 1)
		{
			if (root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				int nSize = data.size();
				for (int i = 0; i < nSize; i++)
				{
					string str;
					if (data[i].isMember("userId"))
					{
						str = data[i]["userId"].asCString();
						userList.push_back(str);
					}
				}
			}
		}
	}
}
//�����û��б�
void CInterfaceUrls::demoRequestOnlineUsers(CUserManager* pUserManager, list<string>& userList)
{
	userList.clear();

	string strData = "appid=";
	strData = strData + pUserManager->m_ServiceParam.m_strAgentId.c_str();

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(ONLINE_USER_LIST_URL.c_str(), strData.c_str(), strContent);
	string str_json = strContent.GetBuffer(0);

	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��   
	{
		std::cout << "========================[Dispatch]========================" << std::endl;
		if (root.isMember("status") && root["status"].asInt() == 1)
		{
			if (root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				int nSize = data.size();
				for (int i = 0; i < nSize; i++)
				{
					string str;
					if (data[i].isMember("userId"))
					{
						str = data[i]["userId"].asCString();
						userList.push_back(str);
					}
				}
			}
		}
	}
}

//����ֱ���б�
void CInterfaceUrls::demoRequestLiveList(list<ChatroomInfo>& listData, CUserManager* pUserManager)
{
	listData.clear();
	string strData = "appid=";
	strData = strData + pUserManager->m_ServiceParam.m_strAgentId.c_str();
	std::string strErrInfo = "";

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(LIVE_LIST_URL.c_str(), strData.c_str(), strContent);
	string str_json = strContent.GetBuffer(0);

	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��   
	{
		std::cout << "========================[Dispatch]========================" << std::endl;
		if (root.isMember("status") && root["status"].asInt() == 1)
		{
			if (root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				int nSize = data.size();
				for (int i = 0; i < nSize; i++)
				{
					ChatroomInfo livePro;

					if (data[i].isMember("ID"))
					{
						livePro.m_strRoomId = data[i]["ID"].asCString();
					}

					if (data[i].isMember("Name"))
					{
						livePro.m_strName = data[i]["Name"].asCString();
					}

					if (data[i].isMember("Creator"))
					{
						livePro.m_strCreaterId = data[i]["Creator"].asCString();
					}

					listData.push_back(livePro);
				}
			}
		}
	}
}

//��Ƶֱ���б�
void CInterfaceUrls::demoRequestAudioLiveList(list<ChatroomInfo>& listData, CUserManager* pUserManager)
{
	listData.clear();
	string strData = "appid=";
	strData = strData + "stargWeHN8Y7";

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(AUDIO_LIVE_LIST_URL.c_str(), strData.c_str(), strContent);
	string str_json = strContent.GetBuffer(0);

	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��   
	{
		std::cout << "========================[Dispatch]========================" << std::endl;
		if (root.isMember("status") && root["status"].asInt() == 1)
		{
			if (root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				int nSize = data.size();
				for (int i = 0; i < nSize; i++)
				{
					ChatroomInfo livePro;

					if (data[i].isMember("ID"))
					{
						livePro.m_strRoomId = data[i]["ID"].asCString();
					}

					if (data[i].isMember("Name"))
					{
						livePro.m_strName = data[i]["Name"].asCString();
					}

					if (data[i].isMember("Creator"))
					{
						livePro.m_strCreaterId = data[i]["Creator"].asCString();
					}
					if (data[i].isMember("liveState"))
					{
						string strStatus = data[i]["liveState"].asCString();
						if (strStatus == "1")
						{
							livePro.m_bLive = true;
						}
						else
						{
							livePro.m_bLive = false;
						}
					}
					

					listData.push_back(livePro);
				}
			}
		}
	}
}

//����ֱ��
void CInterfaceUrls::demoReportLive(string liveID, string liveName, string creatorID, CUserManager* pUserManager)
{
	string url = REPORT_LIVE_INFO_URL + "?ID=" + liveID + "&Name=" + liveName + "&Creator=" + creatorID + "&appid=" + pUserManager->m_ServiceParam.m_strAgentId;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";
	string str_json = "";
	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
}

//�ϱ�����ֱ��
void CInterfaceUrls::demoReportAudioLive(string liveID, string liveName, string creatorID, CUserManager* pUserManager)
{
	string url = REPORT_AUDIO_LIVE_INFO_URL + "?ID=" + liveID + "&Name=" + liveName + "&Creator=" + creatorID + "&appid=" + "stargWeHN8Y7";
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";
	string str_json = "";
	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);

}
//�ϱ�С���
void CInterfaceUrls::demoReportMiniClass(string liveID, string liveName, string creatorID, CUserManager* pUserManager)
{
	string url = REPORT_MINI_CLASS_INFO_URL + "?ID=" + liveID + "&Name=" + liveName + "&Creator=" + creatorID + "&appid=" + "stargWeHN8Y7";
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";
	string str_json = "";
	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
}
//������
void CInterfaceUrls::demoReportMeeting(string liveID, string liveName, string creatorID, CUserManager* pUserManager)
{
	string url = REPORT_MEETING_INFO_URL + "?ID=" + liveID + "&Name=" + liveName + "&Creator=" + creatorID + "&appid=" + pUserManager->m_ServiceParam.m_strAgentId;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";
	string str_json = "";
	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
}
//������
void CInterfaceUrls::demoReportChatroom(string liveID, string liveName, string creatorID, CUserManager* pUserManager)
{
	string url = REPORT_CHATROOM_INFO_URL + "?ID=" + liveID + "&Name=" + liveName + "&Creator=" + creatorID + "&appid=" + pUserManager->m_ServiceParam.m_strAgentId;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";
	string str_json = "";
	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
}
