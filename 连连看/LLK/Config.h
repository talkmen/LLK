#pragma once
class CConfig
{
protected:
	//�������
	int m_nThemeStyle;
	CString m_strElemPath;
	CString m_strMaskPath;
	//�������
	int m_nBGPStyle;
	CString m_strBGPPath;
	//�������
	bool m_bBgMusic;
	bool m_bSound;

	int m_nMusicStyle;//���ַ��
	CString m_strMusicPath;
public:
	CConfig();
	~CConfig();
	//theme setter and getter
	void setThemeStyle(int nStyle);
	int getThemeStyle();

	void setStrElemPath(CString strElemPath);
	CString getStrElemPath();

	void setStrMaskPath(CString strMaskPath);
	CString getStrMaskPath();
	//bgp setter and getter
	void setBGPStyle(int nBGPStyle);
	int getBGPStyle();

	void setStrBGPPath(CString strBGPStyle);
	CString getStrBGPPath();

	//music setter and getter
	void setBgMusic(bool isBgMusic);
	bool getBgMusic();

	void setSound(bool isSound);
	bool getSound();

	void setMusicStyle(int nMusicStyle);
	int getMusicStyle();

	void setMusicPath(CString strMusicPath);
	CString getMusicPath();

	//ʵ������
	//	static CConfig* GetSingleInstance();//��ȡʵ��
	//	static void ReleaseInstance();//�ͷ�ʵ�� 

	//�����ļ�����
	void Save();//����������Ϣ
	void Load();//����������Ϣ
};

