#include "stdafx.h"
#include "CGroupManager.h"
#include "StarIMMessageBuilder.h"

CGroupManager::CGroupManager(CUserManager* pUserManager)
{
	m_pGroupManagerListener = NULL;
	m_pStarRtcCore = StarRtcCore::getStarRtcCoreInstance(pUserManager);
	m_pStarRtcCore->addGroupListener(this);
}


CGroupManager::~CGroupManager()
{
	m_pGroupManagerListener = NULL;
	m_pStarRtcCore->addGroupListener(NULL);
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

	CIMMessage* pIMMessage = StarIMMessageBuilder::getGroupMessage(m_pStarRtcCore->m_pUserManager->m_ServiceParam.m_strUserId, groupID, strAtList, strMessage);
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

	CIMMessage* pIMMessage = StarIMMessageBuilder::getGroupMessage(m_pStarRtcCore->m_pUserManager->m_ServiceParam.m_strUserId, groupID, strAtList, strMessage);
	if (pIMMessage != NULL)
	{
		m_pStarRtcCore->sendOnlineMessage(pIMMessage);
	}
	return pIMMessage;
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
