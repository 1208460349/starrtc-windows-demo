#pragma once
#include <string>
#include <list>
#include "ChatroomInfo.h"
#include "CGroupInfo.h"
#include "CUserManager.h"

using namespace std;
class CInterfaceUrls
{
public:
	CInterfaceUrls();
	virtual ~CInterfaceUrls();
	static void setBaseUrl(string baseUrl);
	//�������б�
	static void demoRequestMeetingList(list<ChatroomInfo>& listData, CUserManager* pUserManager);
	//С����б�
	static void demoRequestMiniClassList(list<ChatroomInfo>& listData, CUserManager* pUserManager);
	//�������б�
	static void demoRequestChatroomList(list<ChatroomInfo>& listData, CUserManager* pUserManager);
	//Ⱥ�б�
	static void demoRequestGroupList(list<CGroupInfo>& retGroupList, CUserManager* pUserManager);
	//Ⱥ��Ա�б�
	static void demoRequestGroupMembers(string groupId, CUserManager* pUserManager, list<string>& userList);
	//�����û��б�
	static void demoRequestOnlineUsers(CUserManager* pUserManager, list<string>& userList);
	//����ֱ���б�
	static void demoRequestLiveList(list<ChatroomInfo>& listData, CUserManager* pUserManager);
	//��Ƶֱ���б�
	static void demoRequestAudioLiveList(list<ChatroomInfo>& listData, CUserManager* pUserManager);
	//����ֱ��
	static void demoReportLive(string liveID, string liveName, string creatorID, CUserManager* pUserManager);
	//�ϱ�����ֱ��
	static void demoReportAudioLive(string liveID, string liveName, string creatorID, CUserManager* pUserManager);
	//�ϱ�С���
	static void demoReportMiniClass(string liveID, string liveName, string creatorID, CUserManager* pUserManager);
	//������
	static void demoReportMeeting(string liveID, string liveName, string creatorID, CUserManager* pUserManager);
	//������
	static void demoReportChatroom(string liveID, string liveName, string creatorID, CUserManager* pUserManager);
public:
	static string BASE_URL;
	//��ȡauthKey
	static string LOGIN_URL;
	//�������б�
	static string MEETING_LIST_URL;
	//ֱ���б�
	static string LIVE_LIST_URL;
	//��Ƶֱ���б�
	static string AUDIO_LIVE_LIST_URL;
	//С����б�
	static string MINI_CLASS_LIST_URL;
	//�ϱ�ֱ����ʹ�õ�������ID��ֱ�����������������һ�������ң�
	static string LIVE_SET_CHAT_URL;
	//�������б�
	static string CHATROOM_LIST_URL;
	//�Լ������Ⱥ�б�
	static string GROUP_LIST_URL;
	//Ⱥ��Ա�б�
	static string GROUP_MEMBERS_URL;
	//�����û��б�
	static string ONLINE_USER_LIST_URL;

	//�ϱ�ֱ��
	static string REPORT_LIVE_INFO_URL;
	//�ϱ�����ֱ��
	static string REPORT_AUDIO_LIVE_INFO_URL;
	//�ϱ�С���
	static string REPORT_MINI_CLASS_INFO_URL;
	//�ϱ�����
	static string REPORT_MEETING_INFO_URL;
	//�ϱ�������
	static string REPORT_CHATROOM_INFO_URL;
};

