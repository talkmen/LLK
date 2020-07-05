#include "stdafx.h"
#include "Config.h"
#include "CONSTANT.h"

CConfig::CConfig()
{
}

CConfig::~CConfig()
{
}

void CConfig::setThemeStyle(int nStyle)
{
	m_nThemeStyle = nStyle;
}

int CConfig::getThemeStyle()
{
	return m_nThemeStyle;
}

void CConfig::setStrElemPath(CString strElemPath)
{
	m_strElemPath.Format(_T("%s"), strElemPath);
}

CString CConfig::getStrElemPath()
{
	return m_strElemPath;
}

void CConfig::setStrMaskPath(CString strMaskPath)
{
	m_strMaskPath.Format(_T("%s"), strMaskPath);
}

CString CConfig::getStrMaskPath()
{
	return m_strMaskPath;
}

void CConfig::setBGPStyle(int nBGPStyle)
{
	m_nBGPStyle = nBGPStyle;
}

int CConfig::getBGPStyle()
{
	return m_nBGPStyle;
}

void CConfig::setStrBGPPath(CString strBGPPath)
{
	m_strBGPPath.Format(_T("%s"), strBGPPath);
}

CString CConfig::getStrBGPPath()
{
	return m_strBGPPath;
}

void CConfig::setBgMusic(bool isBgMusic)
{
	m_bBgMusic = isBgMusic;
}

bool CConfig::getBgMusic()
{
	return m_bBgMusic;
}

void CConfig::setSound(bool isSound)
{
	m_bSound = isSound;
}

bool CConfig::getSound()
{
	return m_bSound;
}

void CConfig::setMusicStyle(int nMusicStyle)
{
	m_nMusicStyle = nMusicStyle;
}

int CConfig::getMusicStyle()
{
	return m_nMusicStyle;
}

void CConfig::setMusicPath(CString strMusicPath)
{
	m_strMusicPath.Format(_T("%s"), strMusicPath);
}

CString CConfig::getMusicPath()
{
	return m_strMusicPath;
}

void CConfig::Save()
{
	CString transfer;
	transfer.Format(_T("%d"), m_nThemeStyle);
	//÷˜Ã‚≈‰÷√
	::WritePrivateProfileString(_T("THEME"), _T("ThemeStyle"), transfer, CONFIGFILEPATH);
	::WritePrivateProfileString(_T("THEME"), _T("ElementPath"), m_strElemPath, CONFIGFILEPATH);
	::WritePrivateProfileString(_T("THEME"), _T("MaskPath"), m_strMaskPath, CONFIGFILEPATH);
	//±≥æ∞≈‰÷√
	transfer.Format(_T("%d"), m_nBGPStyle);
	::WritePrivateProfileString(_T("PICTURE"), _T("PictureStyle"), transfer, CONFIGFILEPATH);
	::WritePrivateProfileString(_T("PICTURE"), _T("PicturePath"), m_strBGPPath, CONFIGFILEPATH);
	//“Ù¿÷≈‰÷√
	if (m_bBgMusic)
		transfer.Format(_T("1"));
	else
		transfer.Format(_T("0"));
	::WritePrivateProfileString(_T("MUSICSWITCH"), _T("BgMusic"), transfer, CONFIGFILEPATH);
	if (m_bSound)
		transfer.Format(_T("1"));
	else
		transfer.Format(_T("0"));
	::WritePrivateProfileString(_T("MUSICSWITCH"), _T("Sound"), transfer, CONFIGFILEPATH);
	transfer.Format(_T("%d"), m_nMusicStyle);
	::WritePrivateProfileString(_T("MUSIC"), _T("BgMusicStyle"), transfer, CONFIGFILEPATH);
	::WritePrivateProfileString(_T("MUSIC"), _T("BgMusicPath"), m_strMusicPath, CONFIGFILEPATH);
}

void CConfig::Load()
{
	//÷˜Ã‚≈‰÷√
	m_nThemeStyle = ::GetPrivateProfileInt(_T("THEME"), _T("ThemeStyle"), 0, CONFIGFILEPATH);
	::GetPrivateProfileString(_T("THEME"), _T("ElementPath"), DEFAULTELEMENT_SMILE, m_strElemPath.GetBufferSetLength(MAXFILEPATHLENGTH), MAXFILEPATHLENGTH, CONFIGFILEPATH);
	m_strElemPath.ReleaseBuffer();
	::GetPrivateProfileString(_T("THEME"), _T("MaskPath"), DEFAULTMASK_SMILE, m_strMaskPath.GetBufferSetLength(MAXFILEPATHLENGTH), MAXFILEPATHLENGTH, CONFIGFILEPATH);
	m_strMaskPath.ReleaseBuffer();
	//±≥æ∞≈‰÷√
	m_nBGPStyle = ::GetPrivateProfileInt(_T("PICTURE"), _T("PictureStyle"), 0, CONFIGFILEPATH);
	::GetPrivateProfileString(_T("PICTURE"), _T("PicturePath"), DEFAULTBG_SEA, m_strBGPPath.GetBufferSetLength(MAXFILEPATHLENGTH), MAXFILEPATHLENGTH, CONFIGFILEPATH);
	m_strBGPPath.ReleaseBuffer();
	//“Ù¿÷≈‰÷√
	int bTrue;
	bTrue = ::GetPrivateProfileInt(_T("MUSICSWITCH"), _T("BgMusic"), 0, CONFIGFILEPATH);
	if (bTrue == 0)
	{
		m_bBgMusic = false;
	}
	else
	{
		m_bBgMusic = true;
	}
	bTrue = ::GetPrivateProfileInt(_T("MUSICSWITCH"), _T("Sound"), 0, CONFIGFILEPATH);
	if (bTrue == 0)
	{
		m_bSound = false;
	}
	else
	{
		m_bSound = true;
	}

	m_nMusicStyle = ::GetPrivateProfileInt(_T("MUSIC"), _T("BgMusicStyle"), 0, CONFIGFILEPATH);
	::GetPrivateProfileString(_T("MUSIC"), _T("BgMusicPath"), DEFAULTMUSIC, m_strMusicPath.GetBufferSetLength(MAXFILEPATHLENGTH), MAXFILEPATHLENGTH, CONFIGFILEPATH);
	m_strMusicPath.ReleaseBuffer();
}

