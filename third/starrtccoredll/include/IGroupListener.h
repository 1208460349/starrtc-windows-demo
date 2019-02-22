#pragma once
#include "CIMMessage.h"
#include <string>
using namespace std;

class IGroupListener
{
public:
	IGroupListener() {}
	virtual ~IGroupListener() {}
public:
	/**
	 * Ⱥ��Ա�������仯
	 * @param groupID
	 * @param number
	 */
	virtual void onMembersUpdeted(string groupID, int number) = 0;

	/**
	 * �Լ����Ƴ�Ⱥ��
	 * @param groupID
	 */
	virtual void onSelfKicked(string groupID) = 0;

	/**
	 * Ⱥ���Ѿ���ɾ��
	 * @param groupID
	 */
	virtual void onGroupDeleted(string groupID) = 0;

	/**
	 *  �յ���Ϣ
	 * @param message
	 */
	virtual void onReceivedMessage(string groupId, CIMMessage* pMessage) = 0;

	virtual void onApplyCreateGroupFin(string groupID) = 0;

	/**
	 *  ɾ��Ⱥ��ص�
	 * @param message
	 */
	virtual void onApplyDelGroupFin(string groupID) = 0;

	/**
	 *  ��ӳ�Ա�ص�
	 * @param message
	 */
	virtual void onApplyAddUserToGroupFin(string groupID) = 0;

	/**
	 *  ɾ����Ա�ص�
	 * @param message
	 */
	virtual void onApplyRemoveUserFromGroupFin(string groupID) = 0;
};

