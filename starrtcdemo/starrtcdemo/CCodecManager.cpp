#include "stdafx.h"
#include "CCodecManager.h"
#include "StarRtcCore.h"

CCodecManager::CCodecManager(CUserManager* pUserManager)
{
	m_pUserManager = pUserManager;
}


CCodecManager::~CCodecManager()
{
}

//videoData���ͷ��ɴ˺�������
void CCodecManager::insertVideoNalu(uint8_t* videoData, int dataLen)
{
	StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->insertVideoNalu(videoData, dataLen);
}

//videoData���ͷ��ɴ˺�������
void CCodecManager::insertVideoRaw(uint8_t* videoData, int dataLen, int isBig)
{
	StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->insertVideoRaw(videoData, dataLen, isBig);
}

int CCodecManager::cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall)
{
	return StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->cropVideoRawNV12(w, h, videoData, dataLen, yuvProcessPlan, rotation, needMirror, outVideoDataBig, outVideoDataSmall);
}
