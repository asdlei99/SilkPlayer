#pragma once

#include <Windows.h>
#include <atlstr.h>
#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE    1
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Define codec specific settings should be moved to h file */
#define MAX_BYTES_PER_FRAME     1024
#define MAX_INPUT_FRAMES        5
#define MAX_FRAME_LENGTH        480
#define FRAME_LENGTH_MS         20
#define MAX_API_FS_KHZ          48
#define MAX_LBRR_DELAY          2


extern "C"
{

#include "SKP_Silk_SDK_API.h"
#include "SKP_Silk_SigProc_FLP.h"
}

class SILKFileDecoder
{
public:
    SILKFileDecoder(void);
    SILKFileDecoder(LPCTSTR lpszFile);
    virtual ~SILKFileDecoder(void);

private: // ���ο������캯���͸�ֵ����
    SILKFileDecoder(const SILKFileDecoder& )
    {
        ATLASSERT(FALSE);
    }
    SILKFileDecoder& operator=(const SILKFileDecoder&)
    {
        ATLASSERT(FALSE);
        return *this;
    }
	bool initDeCoder();
public:
    /// ����������ļ�·��
    virtual void SetFilePathName(LPCTSTR lpszFile);
    /// ��ȡ��ʱ�䳤�ȣ���λms
    virtual ULONGLONG GetTimeLength();
    /// ��ȡ�����Ĳ��θ�ʽ
    virtual WAVEFORMATEX GetWaveFromatX();
    /// ��ʼ���룬��ʼ��������
    virtual BOOL BeginDecode();
    /// ���룬ÿ����һ֡���α��������һ֡,���ؽ�����֡��С����������Ĳ�������
    virtual DWORD Decode(LPSTR& pData);
    /// �ж��Ƿ�������
    virtual bool IsEOF();
	DWORD decodeLastPacket(LPSTR& pData);
	/// �������룬���ٽ�����
    virtual void EndDecode();
    /// �жϽ������Ƿ�����
    virtual bool IsVaild();
    /// ��ȡ�����Ĳ������ݴ�С����λbyte
    virtual DWORD GetDecodedMaxSize();
    /// ��ȡ�����Ĳ�������֡��С����λbyte
    virtual DWORD GetDecodedFrameMaxSize();

private:
    DWORD GetFrameCount();

private:
    FILE                          *m_pbitInFile;
    CString                       m_sFilePathName;        // �����ļ�·��
	SKP_SILK_SDK_DecControlStruct m_DecControl;
	void                          *m_psDec;//������
	size_t                        m_counter;//�ļ���ǰ��λ��
	SKP_uint8                     m_payload[MAX_BYTES_PER_FRAME * MAX_INPUT_FRAMES * (MAX_LBRR_DELAY + 1)];
	SKP_uint8                     *m_pPayloadEnd , *m_pPayloadToDec ;
	SKP_uint8                     m_FECpayload[MAX_BYTES_PER_FRAME * MAX_INPUT_FRAMES], *payloadPtr;
	SKP_int16                     m_nBytesPerPacket[MAX_LBRR_DELAY + 1], totBytes;
	SKP_int16                     m_OutBuf[((FRAME_LENGTH_MS * MAX_API_FS_KHZ) << 1) * MAX_INPUT_FRAMES], *outPtr;	
	bool                          m_bEnd;
	DWORD                         m_FrameCount;
};
