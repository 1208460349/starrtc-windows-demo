#pragma once
#include "CUserManager.h"
#include <stdint.h>
class CCodecManager
{
public:
	CCodecManager(CUserManager* pUserManager);
	virtual ~CCodecManager();
public:
	//videoData���ͷ��ɴ˺�������
	void insertVideoNalu(uint8_t* videoData, int dataLen);
	//videoData���ͷ��ɴ˺�������
	void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	//�ü���Ƶ������Сͼ,outVideoDataBig��outVideoDataSmall�ں�����malloc,��ios�Լ�free������Сͼ����outVideoDataSmallָ���ΪNULL
	//videoData���ں������ͷ�
	//�ɹ�����0��ʧ�ܷ���-1
	int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);
public:
	CUserManager* m_pUserManager;
};

