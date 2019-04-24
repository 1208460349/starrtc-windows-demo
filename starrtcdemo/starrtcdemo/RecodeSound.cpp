#include "stdafx.h"
#include "RecodeSound.h"
// CRecodeSound
IMPLEMENT_DYNCREATE(CRecodeSound, CWinThread)

CRecodeSound::CRecodeSound(CDialog *pDlg)
{
	m_IsRecoding = FALSE; //��ʼ��δ��ʼ¼��
	m_IsAllocated = 0;//��ʼ��δ����buffer

	PreCreateHeader();  //����buffer

	memset(&m_WaveFormatEx, 0, sizeof(m_WaveFormatEx));
	m_WaveFormatEx.wFormatTag = WAVE_FORMAT_PCM;//������ʽΪPCM		
	m_WaveFormatEx.nChannels = 1;	//���������������ڵ�������Ƶ����Ϊ1������������Ϊ2
	m_WaveFormatEx.wBitsPerSample = 16;//��������  8bits/��
	m_WaveFormatEx.cbSize = 0;//һ��Ϊ0
	m_WaveFormatEx.nSamplesPerSec = 16000; //������ 16000 ��/��
	m_WaveFormatEx.nBlockAlign = 2; //һ����Ĵ�С������bit���ֽ�������������
	m_WaveFormatEx.nAvgBytesPerSec = 32000; //ÿ��������ʣ�����ÿ���ܲɼ������ֽڵ�����
}
CRecodeSound::~CRecodeSound()
{
	m_pCallback = NULL;
}
void CRecodeSound::setCallback(ISoundCallback* pCallback)
{
	m_pCallback = pCallback;
}
BOOL CRecodeSound::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CRecodeSound::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}


void CRecodeSound::PreCreateHeader()
{
	for(int i=0;i<MAXRECBUFFER;i++)
		m_RecHead[i]=CreateWaveHeader();
	m_IsAllocated = 1;
}

LPWAVEHDR  CRecodeSound::CreateWaveHeader()
{
	LPWAVEHDR lpHdr = new WAVEHDR;

	if(lpHdr==NULL)
	{
		return NULL;
	}

	ZeroMemory(lpHdr, sizeof(WAVEHDR));
	char* lpByte = new char[RECBUFFER];//m_WaveFormatEx.nBlockAlign*SOUNDSAMPLES)];

	if(lpByte==NULL)
	{
		return NULL;
	}
	lpHdr->lpData =  lpByte;
	lpHdr->dwBufferLength =RECBUFFER;   // (m_WaveFormatEx.nBlockAlign*SOUNDSAMPLES);
	return lpHdr;

}
void CRecodeSound::OnStartRecording(WPARAM wParam, LPARAM lParam)
{
	if(m_IsRecoding) //����Ѿ������ɼ�����ֱ�ӷ���
		return ;//FALSE;

	//������Ƶ�ɼ�
	MMRESULT mmReturn = ::waveInOpen( &m_hRecord, WAVE_MAPPER,
		&m_WaveFormatEx, ::GetCurrentThreadId(), 0, CALLBACK_THREAD);

	//Error has occured while opening device

	if(mmReturn != MMSYSERR_NOERROR ) //�򿪲ɼ�ʧ��
	{
		displayError(mmReturn,"Open");
		return ;//FALSE;
	}		

	if(mmReturn == MMSYSERR_NOERROR )
	{
		//��׼���õ�buffer�ṩ����Ƶ�����豸
		for(int i=0; i < MAXRECBUFFER ; i++)
		{
			//׼��һ��bufrer�������豸
			mmReturn = ::waveInPrepareHeader(m_hRecord,m_RecHead[i], sizeof(WAVEHDR));
			//����һ��buffer��ָ���������豸����buffer��������֪ͨ����
			mmReturn = ::waveInAddBuffer(m_hRecord, m_RecHead[i], sizeof(WAVEHDR));
		}
		//����ָ��������ɼ��豸
		mmReturn = ::waveInStart(m_hRecord);

		if(mmReturn!=MMSYSERR_NOERROR )  //��ʼ�ɼ�ʧ��
			displayError(mmReturn,"Start");
		else
			m_IsRecoding = TRUE;
	}
}

void CRecodeSound::OnStopRecording(WPARAM wParam, LPARAM lParam)
{
	MMRESULT mmReturn = 0;

	if(!m_IsRecoding) //FALSE
		return ;

	//ֹͣ��Ƶ�ɼ�
	mmReturn = ::waveInStop(m_hRecord);

	//To get the remaining sound data from buffer
	//Reset will call OnSoundData function	

	if(!mmReturn) //ֹͣ�ɼ��ɹ������������豸,�����豸���ᵼ�����е�buffer����������
	{
		m_IsRecoding = FALSE;
		mmReturn = ::waveInReset(m_hRecord);  //�����豸
	}

	Sleep(500); //�ȴ�һ��ʱ�䣬ʹbuffer�������

	if(!mmReturn) //�����豸�ɹ��������ر��豸
		mmReturn = ::waveInClose(m_hRecord); //�ر��豸

	return ;//mmReturn;

}

void CRecodeSound::OnSoundData(WPARAM wParam, LPARAM lParam)
{
	if(m_IsRecoding==FALSE) //�����ǰ���ڲɼ�״̬
		return ;//FALSE;

	LPWAVEHDR lpHdr = (LPWAVEHDR) lParam;

	if(lpHdr->dwBytesRecorded==0 || lpHdr==NULL)
		return ;//ERROR_SUCCESS;

	//ʹ�ɼ����̣�֪����buffer�Ѿ�մ�������������
	::waveInUnprepareHeader(m_hRecord, lpHdr, sizeof(WAVEHDR));

	//���ɼ������������͸������߳�
	if (m_pCallback != NULL)
	{
		m_pCallback->getLocalSoundData(lpHdr->lpData, lpHdr->dwBytesRecorded);
	}

	if(m_IsRecoding)
	{
		//���½�buffer�ָ���׼�����״̬
		::waveInPrepareHeader(m_hRecord, lpHdr, sizeof(WAVEHDR));
		::waveInAddBuffer(m_hRecord, lpHdr, sizeof(WAVEHDR));
	}
}

void CRecodeSound::OnEndThread(WPARAM wParam, LPARAM lParam)
{
	if(m_IsRecoding)
		OnStopRecording(0,0);

	::PostQuitMessage(0);
	return ;//TRUE;
}

void CRecodeSound::displayError(int mmReturn,char errmsg[])
{
	TCHAR errorbuffer[MAX_PATH];
	TCHAR errorbuffer1[MAX_PATH];

	waveInGetErrorText(mmReturn, errorbuffer, MAX_PATH);
	wsprintf(errorbuffer1, TEXT("RECORD: %s : %x : %s") ,errmsg, mmReturn, errorbuffer);
	AfxMessageBox(errorbuffer1);  
}

BEGIN_MESSAGE_MAP(CRecodeSound, CWinThread)
	ON_THREAD_MESSAGE(MM_WIM_DATA, OnSoundData)
	ON_THREAD_MESSAGE(WM_RECORDSOUND_STARTRECORDING, OnStartRecording)
	ON_THREAD_MESSAGE(WM_RECORDSOUND_STOPRECORDING, OnStopRecording)
	ON_THREAD_MESSAGE(WM_RECORDSOUND_ENDTHREAD, OnEndThread)
END_MESSAGE_MAP()


// CRecodeSound ��Ϣ�������
