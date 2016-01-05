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
#include "resource.h"
#include "stdafx.h"
#include "flvparse.h"

// CSpecialFFLVDlg �Ի���
class CSpecialFFLVDlg : public CDialogEx
{
// ����
public:
	CSpecialFFLVDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SPECIAL_F_FLV };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMFCEditBrowseCtrl m_fflvinputurl;
	CButton m_fflvoutputa;
	CButton m_fflvoutputv;
	CMFCPropertyGridCtrl m_fflvbasicinfo;
	afx_msg void OnBnClickedFFlvInputurlOpen();
	char fileurl[MAX_URL_LENGTH];
	CListCtrl m_fflvtaglist;
	CMFCPropertyGridProperty *Headergroup;
	int AppendTLInfo(int type,int datasize,int timestamp,int streamid,char data_f_b);
	int AppendBInfo(CString dst_group,CString property_name,CString value,CString remark);
	int ShowBInfo();
	int tl_index;
	void SystemClear();
	//-----------------
	void OnCustomdrawMyList ( NMHDR* pNMHDR, LRESULT* pResult );
	CButton m_fflvtaglistmaxnum;
	afx_msg void OnBnClickedFFlvAbout();
	//-------
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//ר�����ڼ����ַ���
	CString text;
	CComboBox m_fflvlang;
	afx_msg void OnSelchangeFFlvLang();
	afx_msg void OnDestroy();
};
