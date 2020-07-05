#pragma once
class CConfig
{
protected:
	//主题相关
	int m_nThemeStyle;
	CString m_strElemPath;
	CString m_strMaskPath;
	//背景相关
	int m_nBGPStyle;
	CString m_strBGPPath;
	//音乐相关
	bool m_bBgMusic;
	bool m_bSound;

	int m_nMusicStyle;//音乐风格
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

	//实例操作
	//	static CConfig* GetSingleInstance();//获取实例
	//	static void ReleaseInstance();//释放实例 

	//配置文件处理
	void Save();//保存配置信息
	void Load();//加载配置信息
};

