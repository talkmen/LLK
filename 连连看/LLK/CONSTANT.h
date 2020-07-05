#pragma once


//路径上点的最大个数
#define MAXLNNUM 4

//定时器
#define PLAY_TIMER_ID 1   //定时器ID
#define GAME_WIDTH 1980   //界面宽度
#define GAME_HEIGHT 1080  //界面高度

//游戏状态
#define GAME_LOSER -1
#define GAME_SUCCESS 0
#define GAME_PLAY 1
#define GAME_PAUSE 2

//游戏地图初始化
#define MAXMAPROW 18
#define MAXMAPCOL 24

#define ELEMENTWIDTH 40 //游戏图宽度
#define ELEMENTHEIGHT 40 //游戏图长度
#define STARTTOPLOC 10 		//游戏元素初始绘制位置距界面顶端长度
#define STARTLEFTLOC 10		//游戏元素初始绘制位置距界面左端位置

//空白元素
#define BLANK -1		//元素已经消除

//游戏难度
#define EASY 1
#define MEDIUM 2
#define DIFFICULT 3
//游戏各级难度地图大小
#define EASYMAPROW 8
#define EASYMAPCOL 10 //简单地图为6*8
#define MEDIUMMAPROW 12
#define MEDIUMMAPCOL 16 //中级地图为10*14
#define DIFFICULTMAPROW 18
#define DIFFICULTMAPCOL 24//高级地图为16*22

//游戏主要界面
#define GAME_MAIN_FRAME 0  //主界面
#define GAME_MODEL_BASE 1 //基本模式
#define GAME_MODEL_EASY 2 //休闲模式
#define GAME_MODEL_LEVEL 3 //关卡模式

//用户点击响应返回
#define SELECTBLANK 1 //点击空白元素
#define FIRSTSELECT 2 //非空白元素且为第一次选中
#define CLEARSELECT 3 //第二次选中且两点可消除
#define CLEARSELECTUSETOOL 4 //使用道具进行消子
#define RESELECT 5 //第二次选择且两点不可消除

//提示结果
#define TIPS_GET 1 //成功获得提示
#define TIPS_NOTFIND 2 //没有可达路径
#define SCORENOTENOUGH 3//积分不足
#define SUCCESS 4 //成功

//文件相关
#define RANKFILEPATH _T("file\\score.txt")  //积分信息路径
#define CONFIGFILEPATH _T("file\\config.ini") //配置信息路径

#define MAXRANKMES 1000 //最多信息数量
#define MAXFILEPATHLENGTH 50 //最大路径长度

#define DEFAULTELEMENT_SMILE _T("source\\element\\smile.bmp") 
#define DEFAULTMASK_SMILE _T("source\\element\\smile_mask.bmp")
#define DEFAULTBG_SEA _T("source\\bmp\\snow.bmp")
#define DEFAULTBG_FOREST _T("source\\bmp\\cloud.bmp")
#define DEFAULTMUSIC _T("source\\music\\default_best.mp3")
#define DEFAULTELEMENT_STAR _T("source\\element\\star.bmp") 
#define DEFAULTMASK_STAR _T("source\\element\\star_mask.bmp")

//排行榜
#define MAXRANKLEVEL 10//排行榜最大数量