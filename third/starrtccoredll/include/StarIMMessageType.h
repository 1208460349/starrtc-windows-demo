#pragma once

#define MSG_SEND_TYPE_ON_LINE_NO_PUSH	0	//���û�������ʱ,�����͡�����⣩
#define MSG_SEND_TYPE_OFF_LINE_NO_PUSH	1	//���û�������ʱ,�����͡���⣩
#define MSG_SEND_TYPE_OFF_LINE_PUSH		2	//���û�������ʱ,���͡���⣩voipCalling
#define MSG_SEND_TYPE_ON_LINE_PUSH		3	//���û�������ʱ,���͡�����⣩

#define MSG_TYPE_CONTROL				0	//SDK�ڲ� ������Ϣ
#define MSG_TYPE_CUSTOMER				1	//�û��Զ�����Ϣ

//��Ϣ���� = MSG_TYPE_CONTROL ʱ��ҵ����
   //voip���IM���ͣ������ʹﷴ����
#define CONTROL_CODE_VOIP_CALL			1000//����ͨ��
#define CONTROL_CODE_VOIP_REFUSE		1001//�ܾ�ͨ��
#define CONTROL_CODE_VOIP_HANGUP		1002//ͨ����Ҷ�
#define CONTROL_CODE_VOIP_BUSY			1003//ռ��
#define CONTROL_CODE_VOIP_CONNECT		1004//��ͨ

 //���󻥶����chatroom���ͣ���Ҫ�ʹﷴ����
	//A�Ƿ��� B�ǹ���
	//B������������
#define CONTROL_CODE_LIVE_APPLY_LINK			2000 //B��������
#define CONTROL_CODE_LIVE_APPLY_LINK_AGREE		2002 //Aͬ������
#define CONTROL_CODE_LIVE_APPLY_LINK_DISAGREE	2004 //A��ͬ������
//A����B����
#define CONTROL_CODE_LIVE_INVITE_LINK			2100 //A��������
#define CONTROL_CODE_LIVE_INVITE_LINK_AGREE		2102 //Bͬ����������
#define CONTROL_CODE_LIVE_INVITE_START_LINK		2104 //A׼���������뿪ʼ����
#define CONTROL_CODE_LIVE_INVITE_LINK_DISAGREE	2106 //B��ͬ������
//A��Bֹͣ����
#define CONTROL_CODE_LIVE_LINK_STOP				2200 //Aֹͣ����
