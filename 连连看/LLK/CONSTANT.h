#pragma once


//·���ϵ��������
#define MAXLNNUM 4

//��ʱ��
#define PLAY_TIMER_ID 1   //��ʱ��ID
#define GAME_WIDTH 1980   //������
#define GAME_HEIGHT 1080  //����߶�

//��Ϸ״̬
#define GAME_LOSER -1
#define GAME_SUCCESS 0
#define GAME_PLAY 1
#define GAME_PAUSE 2

//��Ϸ��ͼ��ʼ��
#define MAXMAPROW 18
#define MAXMAPCOL 24

#define ELEMENTWIDTH 40 //��Ϸͼ���
#define ELEMENTHEIGHT 40 //��Ϸͼ����
#define STARTTOPLOC 10 		//��ϷԪ�س�ʼ����λ�þ���涥�˳���
#define STARTLEFTLOC 10		//��ϷԪ�س�ʼ����λ�þ�������λ��

//�հ�Ԫ��
#define BLANK -1		//Ԫ���Ѿ�����

//��Ϸ�Ѷ�
#define EASY 1
#define MEDIUM 2
#define DIFFICULT 3
//��Ϸ�����Ѷȵ�ͼ��С
#define EASYMAPROW 8
#define EASYMAPCOL 10 //�򵥵�ͼΪ6*8
#define MEDIUMMAPROW 12
#define MEDIUMMAPCOL 16 //�м���ͼΪ10*14
#define DIFFICULTMAPROW 18
#define DIFFICULTMAPCOL 24//�߼���ͼΪ16*22

//��Ϸ��Ҫ����
#define GAME_MAIN_FRAME 0  //������
#define GAME_MODEL_BASE 1 //����ģʽ
#define GAME_MODEL_EASY 2 //����ģʽ
#define GAME_MODEL_LEVEL 3 //�ؿ�ģʽ

//�û������Ӧ����
#define SELECTBLANK 1 //����հ�Ԫ��
#define FIRSTSELECT 2 //�ǿհ�Ԫ����Ϊ��һ��ѡ��
#define CLEARSELECT 3 //�ڶ���ѡ�������������
#define CLEARSELECTUSETOOL 4 //ʹ�õ��߽�������
#define RESELECT 5 //�ڶ���ѡ�������㲻������

//��ʾ���
#define TIPS_GET 1 //�ɹ������ʾ
#define TIPS_NOTFIND 2 //û�пɴ�·��
#define SCORENOTENOUGH 3//���ֲ���
#define SUCCESS 4 //�ɹ�

//�ļ����
#define RANKFILEPATH _T("file\\score.txt")  //������Ϣ·��
#define CONFIGFILEPATH _T("file\\config.ini") //������Ϣ·��

#define MAXRANKMES 1000 //�����Ϣ����
#define MAXFILEPATHLENGTH 50 //���·������

#define DEFAULTELEMENT_SMILE _T("source\\element\\smile.bmp") 
#define DEFAULTMASK_SMILE _T("source\\element\\smile_mask.bmp")
#define DEFAULTBG_SEA _T("source\\bmp\\snow.bmp")
#define DEFAULTBG_FOREST _T("source\\bmp\\cloud.bmp")
#define DEFAULTMUSIC _T("source\\music\\default_best.mp3")
#define DEFAULTELEMENT_STAR _T("source\\element\\star.bmp") 
#define DEFAULTMASK_STAR _T("source\\element\\star_mask.bmp")

//���а�
#define MAXRANKLEVEL 10//���а��������