#pragma once


enum WHITE_PANEL_ACTION {
	WHITE_PANEL_EMPTY,          //0 ��
	WHITE_PANEL_START,          //1 �ʻ����
	WHITE_PANEL_MOVE,           //2 �ʻ��ƶ�
	WHITE_PANEL_END,            //3 �ʻ��յ�
	WHITE_PANEL_REVOKE,         //4 ����
	WHITE_PANEL_SERIAL,         //5
	WHITE_PANEL_CLEAR,          //6 ���
	WHITE_PANEL_CLEAR_ACK,      //7 �������
	WHITE_PANEL_SYNC_REQUEST,   //8 ͬ������
	WHITE_PANEL_SYNC,           //9 ͬ��
	WHITE_PANEL_SYNC_PREPARE,   //10 ͬ��׼��
	WHITE_PANEL_SYNC_PREPARE_ACK,//11 ͬ��׼������
	WHITE_PANEL_LASER_PEN,      //12 �����
	WHITE_PANEL_LASER_PEN_END,  //13 ����ʽ���
	WHITE_PANEL_FILE            //14 �ļ�
};
