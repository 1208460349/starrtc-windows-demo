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

CInterfaceUrls::CInterfaceUrls()
{
}


CInterfaceUrls::~CInterfaceUrls()
{
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
	strData = strData + pUserManager->m_ServiceParam.m_strAgentId.c_str();

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
	string url = REPORT_MINI_CLASS_INFO_URL + "?ID=" + liveID + "&Name=" + liveName + "&Creator=" + creatorID + "&appid=" + pUserManager->m_ServiceParam.m_strAgentId;
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
