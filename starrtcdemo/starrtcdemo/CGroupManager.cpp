#include "stdafx.h"
#include "CGroupManager.h"
#include "StarIMMessageBuilder.h"
#include "HttpClient.h"
#include "json.h"
IGroupGetListListener* CGroupManager::m_pGroupGetListListener = NULL;
CGroupManager::CGroupManager(CUserManager* pUserManager)
{
	m_pUserManager = pUserManager;
	m_pGroupManagerListener = NULL;
	m_pStarRtcCore = StarRtcCore::getStarRtcCoreInstance();
	m_pStarRtcCore->addGroupListener(this);
}


CGroupManager::~CGroupManager()
{
	m_pGroupManagerListener = NULL;
	m_pStarRtcCore->addGroupListener(NULL);
}

void CGroupManager::addGroupGetListListener(IGroupGetListListener* pGroupGetListListener)
{
	m_pGroupGetListListener = pGroupGetListListener;
}

void CGroupManager::getGroupList(CUserManager* pUserManager)
{
	if (pUserManager->m_bUserDispatch)
	{
		list<CGroupInfo> retGroupList;
		CString stUrl = "";
		stUrl.Format(_T("%s/group/list_all?userid=%s&appid=%s"), pUserManager->m_ServiceParam.m_strRequestListAddr.c_str(), pUserManager->m_ServiceParam.m_strUserId.c_str(), pUserManager->m_ServiceParam.m_strAgentId.c_str());

		char* data = "";

		CString strPara = _T("");
		CString strContent;

		CHttpClient httpClient;
		int nRet = httpClient.HttpPost(stUrl, strPara, strContent);

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
		if (m_pGroupGetListListener != NULL)
		{
			m_pGroupGetListListener->applyGetGroupListFin(retGroupList);
		}	
	}
	else
	{
		StarRtcCore::getStarRtcCoreInstance()->applyGetGroupList();
	}
	
}

void CGroupManager::getUserList(CUserManager* pUserManager, string strGroupId)
{
	if (pUserManager->m_bUserDispatch)
	{
		list<string> userList;

		CString stUrl = "";
		stUrl.Format(_T("%s/group/members?groupId=%s&appid=%s"), pUserManager->m_ServiceParam.m_strRequestListAddr.c_str(), strGroupId.c_str(), pUserManager->m_ServiceParam.m_strAgentId.c_str());

		char* data = "";

		CString strPara = _T("");
		CString strContent;

		CHttpClient httpClient;
		int nRet = httpClient.HttpPost(stUrl, strPara, strContent);

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
		if (m_pGroupGetListListener != NULL)
		{
			m_pGroupGetListListener->applyGetUserListFin(userList);
		}
	}
	else
	{
		StarRtcCore::getStarRtcCoreInstance()->applyGetUserList((char*)strGroupId.c_str());
	}
	
}

/**
 * ��Ӽ���
 * @param groupManagerListener
 */
void CGroupManager::addListener(IGroupManagerListener* pGroupManagerListener)
{
	m_pGroupManagerListener = pGroupManagerListener;
}

/**
 * ����Ⱥ
 * @param groupName
 * @param callback
 */
bool CGroupManager::createGroup(string groupName)
{
	if (m_pStarRtcCore != NULL)
	{
		int nret = m_pStarRtcCore->applyCreateGroup("", (char*)groupName.c_str());
	}	
	return true;
}

/**
 * ɾ��Ⱥ
 * @param groupID
 */
bool CGroupManager::deleteGroup(string groupID)
{
	if (m_pStarRtcCore != NULL)
	{
		m_pStarRtcCore->applyDelGroup((char*)groupID.c_str());
	}
	return true;
}

/**
 * ���Ⱥ��Ա
 * @param groupID
 * @param memberIDs
 */
void CGroupManager::addGroupMembers(string groupID, list<string> memberIDs)
{
	if (memberIDs.size() <= 0)
	{
		return;
	}
	string strIds = "";
	list<string>::iterator iter = memberIDs.begin();
	for (; iter != memberIDs.end(); iter++)
	{
		if (strIds != "")
		{
			strIds = "," + strIds;
		}
		strIds = strIds + *iter;
	}
	if (m_pStarRtcCore != NULL)
	{
		m_pStarRtcCore->applyAddUserToGroup((char*)groupID.c_str(), (char*)strIds.c_str(), "");
	}
}

/**
 * ɾ��Ⱥ��Ա
 * @param groupID
 * @param memberIDs
 */
void CGroupManager::deleteGroupMembers(string groupID, list<string> memberIDs)
{
	if (memberIDs.size() <= 0)
	{
		return;
	}
	string strIds = "";
	list<string>::iterator iter = memberIDs.begin();
	for (; iter != memberIDs.end(); iter++)
	{
		if (strIds != "")
		{
			strIds = "," + strIds;
		}
		strIds = strIds + *iter;
	}
	if (m_pStarRtcCore != NULL)
	{
		m_pStarRtcCore->applyRemoveUserToGroup((char*)groupID.c_str(), (char*)strIds.c_str());
	}
}

/**
 * �������Ϳ���
 * @param groupID
 * @param enable
 * @param callback
 */
void CGroupManager::setPushEnable(string groupID, bool enable)
{

}

/**
 *������Ϣ
 * @param groupID
 * @param atUserIDs
 * @param Message
 * @param callback
 * @return ��������Ϣ
 */
CIMMessage* CGroupManager::sendMessage(string groupID, list<string> atUserIDs, string strMessage)
{
	string strAtList = "";
	list<string>::iterator iter = atUserIDs.begin();
	for (; iter != atUserIDs.end(); iter++)
	{
		if (strAtList != "")
		{
			strAtList = "," + strAtList;
		}
		strAtList = strAtList + *iter;
	}

	CIMMessage* pIMMessage = StarIMMessageBuilder::getGroupMessage(m_pUserManager->m_ServiceParam.m_strUserId, groupID, strAtList, strMessage);
	if (pIMMessage != NULL)
	{
		m_pStarRtcCore->sendGroupMsg(pIMMessage);
	}
	return pIMMessage;
}

/**
 *������Ϣ
 * @param groupID
 * @param atUserIDs
 * @param Message
 * @param callback
 * @return ��������Ϣ
 */
CIMMessage* CGroupManager::sendOnlineMessage(string groupID, list<string> atUserIDs, string strMessage)
{
	string strAtList = "";
	list<string>::iterator iter = atUserIDs.begin();
	for (; iter != atUserIDs.end(); iter++)
	{
		if (strAtList != "")
		{
			strAtList = "," + strAtList;
		}
		strAtList = strAtList + *iter;
	}

	CIMMessage* pIMMessage = StarIMMessageBuilder::getGroupMessage(m_pUserManager->m_ServiceParam.m_strUserId, groupID, strAtList, strMessage);
	if (pIMMessage != NULL)
	{
		m_pStarRtcCore->sendOnlineMessage(pIMMessage);
	}
	return pIMMessage;
}

/**
 * ��ȡgroup list�ص�����
 */
int CGroupManager::applyGetGroupListFin(list<CGroupInfo>& groupInfoList)
{
	int ret = 0;
	if (CGroupManager::m_pGroupGetListListener)
	{
		ret = CGroupManager::m_pGroupGetListListener->applyGetGroupListFin(groupInfoList);
	}
	return ret;
}

/**
 * ��ȡ�û��б�ص�����
 */
int CGroupManager::applyGetUserListFin(list<string>& userList)
{
	int ret = 0;
	if (CGroupManager::m_pGroupGetListListener)
	{
		ret = CGroupManager::m_pGroupGetListListener->applyGetUserListFin(userList);
	}
	return ret;
}

/**
 * Ⱥ��Ա�������仯
 * @param groupID
 * @param number
 */
void CGroupManager::onMembersUpdeted(string groupID, int number)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onMembersUpdeted(groupID, number);
	}
}

/**
 * �Լ����Ƴ�Ⱥ��
 * @param groupID
 */
void CGroupManager::onSelfKicked(string groupID)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onSelfKicked(groupID);
	}
}

/**
 * Ⱥ���Ѿ���ɾ��
 * @param groupID
 */
void CGroupManager::onGroupDeleted(string groupID)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onGroupDeleted(groupID);
	}
}

/**
 *  �յ���Ϣ
 * @param message
 */
void CGroupManager::onReceivedMessage(string groupId, CIMMessage* pMessage)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onReceivedMessage(groupId, pMessage);
	}
}

void CGroupManager::onApplyCreateGroupFin(string groupID)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onApplyCreateGroupFin(groupID);
	}
}

void CGroupManager::onApplyDelGroupFin(string groupID)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onApplyCreateGroupFin(groupID);
	}
}

void CGroupManager::onApplyAddUserToGroupFin(string groupID)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onApplyCreateGroupFin(groupID);
	}
}

void CGroupManager::onApplyRemoveUserFromGroupFin(string groupID)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onApplyRemoveUserFromGroupFin(groupID);
	}
}
