/************************************************************************/
/*  Copyright 2015 Intelligent Vehicle Lab of CQUPT.
/* Author :Tian Zhen   
/* 2015.5.4 
/************************************************************************/
#include <string>
#include <iostream>
#pragma once

using namespace std;

//ȫ�ֱ���;

//����ȫ�ֱ���;
extern int g_nLidarFlag;
extern int g_nMapUpdateTime;


//�״������궨��;
enum LidarName{  FrontLeft=0,FrontRight=1, MidLeft=2, MidRight=3,BackLeft=4,BackRight=5};

//�״�IP���ַ�������IPֵ�����ֺ궨������ڱ��� ip[FrontLeft]����ǰ�󷽵��״�;
const string ip[6]={"192.168.1.30","192.168.1.31","192.168.1.20","192.168.1.21","192.168.1.22","192.168.1.23"};


//�״��Ƿ�򿪱�־��,0Ϊ�رգ�1λ��;
const int g_nOpenflag[6]={1, 0, 0, 0, 0, 0 }; 


// �״�ƫ����Ϣ�������״�����ת������λcm;                          
//front left lidar,ibeo;
const float LIDAR_FRONT_LEFT_POSITION_X=-68.2;   //X��ƫ����;
const float LIDAR_FRONT_LEFT_POSITION_Y=-1.5;		//Y��ƫ����;
const float LIDAR_FRONT_LEFT_POSITION_RATE=1;	//��������ת�Ƕȵĳ��Ե�ϵ��;

//front right lidar,ibeo; 
const float LIDAR_FRONT_RIGHT_POSITION_X=68.2;
const float LIDAR_FRONT_RIGHT_POSITION_Y=-1.5;
const float LIDAR_FRONT_RIGHT_POSITION_RATE=1;

//Middle left lidar; 
const float LIDAR_MIDDLE_LEFT_POSITION_X=-99.1;
const float LIDAR_MIDDLE_LEFT_POSITION_Y=-134.5;
const float LIDAR_MIDDLE_LEFT_POSITION_RATE=1;

//Middle right lidar;  
const float LIDAR_MIDDLE_RIGHT_POSITION_X=99.1;
const float LIDAR_MIDDLE_RIGHT_POSITION_Y=-134.5;
const float LIDAR_MIDDLE_RIGHT_POSITION_RATE=1;

//back left lidar;  
const float LIDAR_BACK_LEFT_POSITION_X=-67.2;
const float LIDAR_BACK_LEFT_POSITION_Y=-486.6;
const float LIDAR_BACK_LEFT_POSITION_COS=0.742;
const float LIDAR_BACK_LEFT_POSITION_Sin=0.670;


//back right lidar;  
const float LIDAR_BACK_RIGHT_POSITION_X=67.2;
const float LIDAR_BACK_RIGHT_POSITION_Y=-486.6;
const float LIDAR_BACK_RIGHT_POSITION_COS=0.613;
const float LIDAR_BACK_RIGHT_POSITION_Sin=0.793;

//	�״�ɨ������ʾ�еķ�Χ����������ͼ����ʾ����-1��1֮��;
//	������Ҫ����һ����ת������ʾ��ΧΪ-5000cm��5000cm����Ҫ���Ա�������;
const float LIDAR_DISPLAY_RANGE=1000;


//	�״�ɨ����������ͣ�����ɨ��õ���X,Y����;
//	ʹ��get��set�����Գ�Ա�������и�ֵ��ȡֵ;
class LidarData
{
public:
	void SetScanX(int x){this->LidarScanX=x;}
	void SetScanY(int y){this->LidarScanY=y;}
	float GetScanX(){return LidarScanX;}
	float GetScanY(){return LidarScanY;}
protected:

private:
	float LidarScanX;
	float LidarScanY;

};

//	�״�Ŀ���������ͣ�����Ŀ�꣬��length,��width,����x,y���ٶ�v;
//	ʹ��get��set�����Գ�Ա�������и�ֵ��ȡֵ;
class LidarTargetData
{
public:
	void SetTargetX(int x){this->TargetPostionX=x;}
	void SetTargetY(int y){this->TargetPostionY=y;}
	void SetTargetLength(int Length){this->TargetLength=Length;}
	void SetTargetWidth(int Width){this->TargetWidth=Width;}
	void SetTargetVelocity(int Velocity){this->TargetVelocity=Velocity;}


	int GetTargetX(){return TargetPostionX;}
	int GetTargetY(){return TargetPostionY;}
	int GetTargetLength(){return TargetLength;}
	int GetTargetWidth(){return TargetWidth;}
	int GetTargetVelocity(){return TargetVelocity;}

protected:

private:
	int TargetPostionX;
	int TargetPostionY;
	int TargetLength;
	int TargetWidth;
	int TargetVelocity;

};

//�������������;
class BreakPointData
{
public:
	void SetObjectId(int x){this->ObjectId=x;}
	void SetStartPosition(int x){this->StartPosition=x;}
	void SetEndPosition(int x){this->EndPosition=x;}

	int GetObjectId(){return ObjectId;}
	int GetStartPosition(){return StartPosition;}
	int GetEndPosition(){return EndPosition;}
	int GetPointNum(){return EndPosition-StartPosition+1;}

private:
	int ObjectId;		//	breakpoint ID��
	int StartPosition;	//	breakpoint���λ�ã�ָ��������Ӧ����
	int EndPosition;	//	breakpoint�������
	int PointNum;    //breakpoint�����ĵ���
};
