#pragma once
#include <string>
using namespace std;

class CIMMessage
{
public:	
	long long m_Time;               //��Ϣʱ��
	int m_nMsgIndex;            //��Ϣ���
	
	int m_nType;                //��Ϣ���ͣ�  0��SDK�ڲ���Ϣ��1���û���Ϣ
	int m_nCode;                //��Ϣ����=0 ʱ��ҵ����

	string m_strFromId;           //������Ϣ����
	string m_strTargetId;         //Ŀ��id�����Ǹ��˻�Ⱥ��id��
	string m_strContentData;      //�Զ�����Ϣ����
	string m_strAtList;           // @���û�ID ����ö��ŷָ�
};

