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
#include "stdafx.h"
#include "SpecialFFLV.h"
#include "SpecialFFLVDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnDestroy();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CSpecialFFLVDlg �Ի���




CSpecialFFLVDlg::CSpecialFFLVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSpecialFFLVDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpecialFFLVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_F_FLV_INPUTURL, m_fflvinputurl);
	DDX_Control(pDX, IDC_F_FLV_OUTPUT_A, m_fflvoutputa);
	DDX_Control(pDX, IDC_F_FLV_OUTPUT_V, m_fflvoutputv);
	DDX_Control(pDX, IDC_F_FLV_BASICINFO, m_fflvbasicinfo);
	DDX_Control(pDX, IDC_F_FLV_TAGLIST, m_fflvtaglist);
	DDX_Control(pDX, IDC_F_FLV_TAGLIST_MAXNUM, m_fflvtaglistmaxnum);
	DDX_Control(pDX, IDC_F_FLV_LANG, m_fflvlang);
}

BEGIN_MESSAGE_MAP(CSpecialFFLVDlg, CDialogEx)
	ON_BN_CLICKED(IDC_F_FLV_INPUTURL_OPEN, &CSpecialFFLVDlg::OnBnClickedFFlvInputurlOpen)
	ON_NOTIFY ( NM_CUSTOMDRAW,IDC_F_FLV_TAGLIST, OnCustomdrawMyList )
	ON_BN_CLICKED(IDC_F_FLV_ABOUT, &CSpecialFFLVDlg::OnBnClickedFFlvAbout)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_CBN_SELCHANGE(IDC_F_FLV_LANG, &CSpecialFFLVDlg::OnSelchangeFFlvLang)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CSpecialFFLVDlg ��Ϣ�������

BOOL CSpecialFFLVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	//����ѡ���б���ߣ���ͷ����������
	DWORD dwExStyle=LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE;
	//�����񣻵���ѡ�񣻸�����ʾѡ����
	//��Ƶ
	

	m_fflvtaglist.ModifyStyle(0,LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
	m_fflvtaglist.SetExtendedStyle(dwExStyle);

	text.LoadString(IDS_LIST_TITLE_NUM);
	m_fflvtaglist.InsertColumn(0,text,LVCFMT_CENTER,50,0);
	text.LoadString(IDS_LIST_TITLE_TYPE);
	m_fflvtaglist.InsertColumn(1,text,LVCFMT_CENTER,75,0);
	text.LoadString(IDS_LIST_TITLE_DATASIZE);
	m_fflvtaglist.InsertColumn(2,text,LVCFMT_CENTER,75,0);
	text.LoadString(IDS_LIST_TITLE_TIMESTAMP);
	m_fflvtaglist.InsertColumn(3,text,LVCFMT_CENTER,75,0);
	text.LoadString(IDS_LIST_TITLE_STREAMID);
	m_fflvtaglist.InsertColumn(4,text,LVCFMT_CENTER,75,0);
	text.LoadString(IDS_LIST_TITLE_TAGDATAFB);
	m_fflvtaglist.InsertColumn(5,text,LVCFMT_CENTER,150,0);


	//Propertylist��ʼ��------------------------
	m_fflvbasicinfo.EnableHeaderCtrl(FALSE);
	m_fflvbasicinfo.EnableDescriptionArea();
	m_fflvbasicinfo.SetVSDotNetLook();
	m_fflvbasicinfo.MarkModifiedProperties();
	//�ѵ�һ�е�����һЩ-----------------------
	HDITEM item; 
	item.cxy=90; 
	item.mask=HDI_WIDTH; 
	m_fflvbasicinfo.GetHeaderCtrl().SetItem(0, &item); 

	//----
	Headergroup=new CMFCPropertyGridProperty(_T("File Header"));
	//-----------
	tl_index=0;
	m_fflvtaglistmaxnum.SetCheck(1);
	//-------------
	m_fflvinputurl.EnableFileBrowseButton(
		NULL,
		_T("FLV Files (*.flv)|*.flv|All Files (*.*)|*.*||")
		);
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_fflvlang.InsertString(0,_T("Chinese"));
	m_fflvlang.InsertString(1,_T("English"));

	//_CrtSetBreakAlloc(822);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSpecialFFLVDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSpecialFFLVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	//���Ի���Ӧ����ӵ�OnInitDialog�У�����û��Ч��

}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSpecialFFLVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSpecialFFLVDlg::OnBnClickedFFlvInputurlOpen()
{
	SystemClear();
	CString strFilePath;
	m_fflvinputurl.GetWindowText(strFilePath);

#ifdef _UNICODE
	USES_CONVERSION;
	strcpy(fileurl,W2A(strFilePath));
#else
	strcpy(fileurl,strFilePath);
#endif


	flvparse(this,fileurl);

	ShowBInfo();
}
//���һ����¼
//ÿ���ֶεĺ��壺���ͣ����ݴ�С��ʱ�����streamid��data�ĵ�һ���ֽ�
int CSpecialFFLVDlg::AppendTLInfo(int type,int datasize,int timestamp,int streamid,char data_f_b){
	//���ѡ���ˡ�������5000�������ж��Ƿ񳬹�5000��
	if(m_fflvtaglistmaxnum.GetCheck()==1&&tl_index>5000){
		return 0;
	}
	CString temp_index,temp_type,temp_datasize,temp_timestamp,temp_streamid;
	CString temp_tagdatafirstbyte;
	
	unsigned char x;

	int nIndex=0;
	switch(type){
	case 8:{
		text.LoadString(IDS_UNKNOWN);
		x=data_f_b&0xF0;
		x=x>>4;
		switch (x)
		{
		case 0:temp_tagdatafirstbyte.AppendFormat(_T("Linear PCM, platform endian"));break;
		case 1:temp_tagdatafirstbyte.AppendFormat(_T("ADPCM"));break;
		case 2:temp_tagdatafirstbyte.AppendFormat(_T("MP3"));break;
		case 3:temp_tagdatafirstbyte.AppendFormat(_T("Linear PCM, little endian"));break;
		case 4:temp_tagdatafirstbyte.AppendFormat(_T("Nellymoser 16-kHz mono"));break;
		case 5:temp_tagdatafirstbyte.AppendFormat(_T("Nellymoser 8-kHz mono"));break;
		case 6:temp_tagdatafirstbyte.AppendFormat(_T("Nellymoser"));break;
		case 7:temp_tagdatafirstbyte.AppendFormat(_T("G.711 A-law logarithmic PCM"));break;
		case 8:temp_tagdatafirstbyte.AppendFormat(_T("G.711 mu-law logarithmic PCM"));break;
		case 9:temp_tagdatafirstbyte.AppendFormat(_T("reserved"));break;
		case 10:temp_tagdatafirstbyte.AppendFormat(_T("AAC"));break;
		case 11:temp_tagdatafirstbyte.AppendFormat(_T("Speex"));break;
		case 14:temp_tagdatafirstbyte.AppendFormat(_T("MP3 8-Khz"));break;
		case 15:temp_tagdatafirstbyte.AppendFormat(_T("Device-specific sound"));break;
		default:temp_tagdatafirstbyte.AppendFormat(_T("%s"),text);break;
		}
		temp_tagdatafirstbyte.AppendFormat(_T("|"));
		x=data_f_b&0x0C;
		x=x>>2;
		switch (x)
		{
		case 0:temp_tagdatafirstbyte.AppendFormat(_T("5.5-kHz"));break;
		case 1:temp_tagdatafirstbyte.AppendFormat(_T("11-kHz"));break;
		case 2:temp_tagdatafirstbyte.AppendFormat(_T("22-kHz"));break;
		case 3:temp_tagdatafirstbyte.AppendFormat(_T("44-kHz"));break;
		default:temp_tagdatafirstbyte.AppendFormat(_T("%s"),text);break;
		}
		temp_tagdatafirstbyte.AppendFormat(_T("|"));
		x=data_f_b&0x02;
		x=x>>1;
		switch (x)
		{
		case 0:temp_tagdatafirstbyte.AppendFormat(_T("8Bit"));break;
		case 1:temp_tagdatafirstbyte.AppendFormat(_T("16Bit"));break;
		default:temp_tagdatafirstbyte.AppendFormat(_T("%s"),text);break;
		}
		temp_tagdatafirstbyte.AppendFormat(_T("|"));
		x=data_f_b&0x01;
		switch (x)
		{
		case 0:temp_tagdatafirstbyte.AppendFormat(_T("Mono"));break;
		case 1:temp_tagdatafirstbyte.AppendFormat(_T("Stereo"));break;
		default:temp_tagdatafirstbyte.AppendFormat(_T("%s"),text);break;
		}
		text.LoadString(IDS_LIST_DATA_TYPE_AUDIO);
		break;
		}
	case 9:{
		text.LoadString(IDS_UNKNOWN);
		x=data_f_b&0xF0;
		x=x>>4;
		switch (x)
		{
		case 1:temp_tagdatafirstbyte.AppendFormat(_T("key frame"));break;
		case 2:temp_tagdatafirstbyte.AppendFormat(_T("inter frame"));break;
		case 3:temp_tagdatafirstbyte.AppendFormat(_T("disposable inter frame"));break;
		case 4:temp_tagdatafirstbyte.AppendFormat(_T("generated keyframe "));break;
		case 5:temp_tagdatafirstbyte.AppendFormat(_T("video info/command frame"));break;
		default:temp_tagdatafirstbyte.AppendFormat(_T("%s"),text);break;
		}
		temp_tagdatafirstbyte.AppendFormat(_T("|"));
		x=data_f_b&0x0F;
		switch (x)
		{
		case 1:temp_tagdatafirstbyte.AppendFormat(_T("JPEG"));break;
		case 2:temp_tagdatafirstbyte.AppendFormat(_T("Sorenson H.263"));break;
		case 3:temp_tagdatafirstbyte.AppendFormat(_T("Screen video"));break;
		case 4:temp_tagdatafirstbyte.AppendFormat(_T("On2 VP6"));break;
		case 5:temp_tagdatafirstbyte.AppendFormat(_T("On2 VP6 with alpha channel"));break;
		case 6:temp_tagdatafirstbyte.AppendFormat(_T("Screen video version 2"));break;
		case 7:temp_tagdatafirstbyte.AppendFormat(_T("AVC"));break;
		default:temp_tagdatafirstbyte.AppendFormat(_T("%s"),text);break;
		}
		text.LoadString(IDS_LIST_DATA_TYPE_VIDEO);
		break;
		   }
	case 18:{
		text.LoadString(IDS_LIST_DATA_TYPE_SCRIPT);break;
			}
	default:{
		text.LoadString(IDS_UNKNOWN);break;
			}
	}
	temp_type.Format(_T("%s"),text);
	temp_index.Format(_T("%d"),tl_index);
	temp_datasize.Format(_T("%d"),datasize);
	temp_timestamp.Format(_T("%d"),timestamp);
	temp_streamid.Format(_T("%d"),streamid);
	//��ȡ��ǰ��¼����
	nIndex=m_fflvtaglist.GetItemCount();
	//���С����ݽṹ
	LV_ITEM lvitem;
	lvitem.mask=LVIF_TEXT;
	lvitem.iItem=nIndex;
	lvitem.iSubItem=0;
	//ע��vframe_index������ֱ�Ӹ�ֵ��
	//���ʹ��f_indexִ��Format!�ٸ�ֵ��
	lvitem.pszText=temp_index.GetBuffer();
	//------------------------
	m_fflvtaglist.InsertItem(&lvitem);
	m_fflvtaglist.SetItemText(nIndex,1,temp_type);
	m_fflvtaglist.SetItemText(nIndex,2,temp_datasize);
	m_fflvtaglist.SetItemText(nIndex,3,temp_timestamp);
	m_fflvtaglist.SetItemText(nIndex,4,temp_streamid);
	m_fflvtaglist.SetItemText(nIndex,5,temp_tagdatafirstbyte);
	tl_index++;
	return TRUE;
}
int CSpecialFFLVDlg::AppendBInfo(CString dst_group,CString property_name,CString value,CString remark){
	if(dst_group.Compare(_T("Header"))==0){
		Headergroup->AddSubItem(new CMFCPropertyGridProperty(property_name, (_variant_t)value, remark));
	}
	return TRUE;
}
int CSpecialFFLVDlg::ShowBInfo(){
	m_fflvbasicinfo.AddProperty(Headergroup);
	return TRUE;
}

void CSpecialFFLVDlg::SystemClear(){
	Headergroup->RemoveAllOptions();

	Headergroup=new CMFCPropertyGridProperty(_T("Header"));
	m_fflvbasicinfo.RemoveAll();
	m_fflvtaglist.DeleteAllItems();
	tl_index=0;
}
//ListCtrl����ɫ
void CSpecialFFLVDlg::OnCustomdrawMyList ( NMHDR* pNMHDR, LRESULT* pResult )
{
	//This code based on Michael Dunn's excellent article on
	//list control custom draw at http://www.codeproject.com/listctrl/lvcustomdraw.asp

	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

	// Take the default processing unless we set this to something else below.
	*pResult = CDRF_DODEFAULT;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.
	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.

		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{

		COLORREF clrNewTextColor, clrNewBkColor;

		int    nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );

		CString strTemp = m_fflvtaglist.GetItemText(nItem,1);
		CString text_video,text_audio,text_script;
		text_video.LoadString(IDS_LIST_DATA_TYPE_VIDEO);
		text_audio.LoadString(IDS_LIST_DATA_TYPE_AUDIO);
		text_script.LoadString(IDS_LIST_DATA_TYPE_SCRIPT);

		if(strTemp.Compare(text_video)==0){
			clrNewTextColor = RGB(0,0,0);		//Set the text 
			clrNewBkColor = RGB(0,255,255);		//��ɫ
		}
		else if(strTemp.Compare(text_audio)==0){
			clrNewTextColor = RGB(0,0,0);		//text 
			clrNewBkColor = RGB(255,255,0);		//��ɫ
		}
		else if(strTemp.Compare(text_script)==0){
			clrNewTextColor = RGB(0,0,0);		//text
			clrNewBkColor = RGB(255,153,0);		//����ɫ
		}else{
			clrNewTextColor = RGB(0,0,0);		//text
			clrNewBkColor = RGB(255,255,255);			//��ɫ
		}

		pLVCD->clrText = clrNewTextColor;
		pLVCD->clrTextBk = clrNewBkColor;


		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;


	}
}

void CSpecialFFLVDlg::OnBnClickedFFlvAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}


void CSpecialFFLVDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnDropFiles(hDropInfo);
	LPTSTR pFilePathName =(LPTSTR)malloc(MAX_URL_LENGTH);
	::DragQueryFile(hDropInfo, 0, pFilePathName,MAX_URL_LENGTH);  // ��ȡ�Ϸ��ļ��������ļ�������ؼ���
	m_fflvinputurl.SetWindowText(pFilePathName);
	::DragFinish(hDropInfo);   // ע����������٣��������ͷ�Windows Ϊ�����ļ��ϷŶ�������ڴ�
	free(pFilePathName);
}


void CSpecialFFLVDlg::OnSelchangeFFlvLang()
{
	//�����ļ�·��
	char conf_path[300]={0};
	//���exe����·��
	GetModuleFileNameA(NULL,(LPSTR)conf_path,300);//
	//���exe�ļҼ�·��
	strrchr( conf_path, '\\')[0]= '\0';//
	//_getcwd(realpath,MYSQL_S_LENGTH);
	printf("%s",conf_path);
	strcat(conf_path,"\\configure.ini");
	//д�������ļ�
	switch(m_fflvlang.GetCurSel()){
	case 0:WritePrivateProfileStringA("Settings","language","Chinese",conf_path);break;
	case 1:WritePrivateProfileStringA("Settings","language","English",conf_path);break;
	default:break;
	}
	//�������
	char exe_path[300]={0};
	//���exe����·��
	GetModuleFileNameA(NULL,(LPSTR)exe_path,300);
	ShellExecuteA( NULL,"open",exe_path,NULL,NULL,SW_SHOWNORMAL);
	OnCancel();
}


//void CAboutDlg::OnDestroy()
//{
//	CDialogEx::OnDestroy();
//
//	// TODO: �ڴ˴������Ϣ����������
//}


void CSpecialFFLVDlg::OnDestroy()
{

	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}
