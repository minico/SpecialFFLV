/* 
 * 
 * FLV ��ʽ������
 * FLV Format Analysis
 *
 * ������ Lei Xiaohua
 * leixiaohua1020@126.com
 * �й���ý��ѧ/���ֵ��Ӽ���
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 * 
 * FLV��װ��ʽ��������
 * FLV Container Format Analysis Tools
 * 
 * 
 */
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSpecialFFLVApp:
// �йش����ʵ�֣������ SpecialFFLV.cpp
//

class CSpecialFFLVApp : public CWinApp
{
public:
	CSpecialFFLVApp();

// ��д
public:
	virtual BOOL InitInstance();
	void LoadLaguage();
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSpecialFFLVApp theApp;