
/*
 * Copyright 2015 Intelligent Vehicle Lab of CQUPT.
 * Author :Tian Zhen   
 * Date:2015.5.4 
 *	
 * ����һ��Ibeo LUXϵ�����߼����״�����ݲɼ�Դ�ļ�
 *    
 *
 */



#include "ibeo.h"
#include <ibeosdk/lux.hpp>
#include <ibeosdk/IpHelper.hpp>
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace ibeo;
using namespace std;

//======================================================================
class AllLuxListener : public ibeo::DataListener<ScanLux>,
                       public ibeo::DataListener<ObjectListLux>{
public:
	
	AllLuxListener(int f){flag = f;};

	//========================================
	void onData(const ScanLux* const scan)
	{
		const std::vector<ScanPointLux>& points = scan->getScanPoints();
		LidarData TempLidarData;
		switch(flag)
		{
		case FrontLeft:TempIbeoData.m_LidarScanFLeft.clear(); break;
		case FrontRight:TempIbeoData.m_LidarScanFRight.clear(); break;
		}
	
		for (unsigned int i = 0; i < points.size(); i++)  
		{
			ibeo::UINT16  Distance=points.at(i).getDistance();   //��λcm'
		
			float Angle=points.at(i).getHorizontalAngle();    //�Ƕ�Ϊ��y��нǣ���+50��-50��
				Angle=Angle/32;
			//C++��cos,sin,asin,acos��Щ���Ǻ����������ǻ���,���ǽǶ�;����=�Ƕ�*Pi/180;
				//ibeo��������ֱ�����겻ͬ����Ҫת��  X=-gety=-dsinr;y=getx=dcosr;
			long x = static_cast<long>(Distance * -sin(Angle*M_PI/180));//
			long y = static_cast<long>(Distance * cos(Angle*M_PI/180));
			
			//cout<<"Distance="<<Distance<<"   "<<" Angle="<< Angle<<endl;
			//32�ǽǶ�ϵ�����μ�ibeo˵���ĵ���central range 0.125'
			//*medium range 0.25',lateral range 0.5'*	
			//	std::cout <<"X="<<x<<"   "<<"Y=" <<y <<std::endl;
				
				
			//*****�洢����;*****/
			if(flag==FrontLeft)//****Back left lidar*****//
			{
				x=x+LIDAR_FRONT_LEFT_POSITION_X;
				y=y+LIDAR_FRONT_LEFT_POSITION_Y;
			}

			else if (flag==FrontRight)//****Back right lidar*****//
			{
				x=x+LIDAR_FRONT_RIGHT_POSITION_X;
				y=y+LIDAR_FRONT_RIGHT_POSITION_Y;
			}
			
			
			//cerr<<"SetScanX="<<x<<" "<<"SetScanY="<<y<<endl;
			TempLidarData.SetScanX(x);
			TempLidarData.SetScanY(y);

			
			switch(flag)
			{
			case FrontLeft:TempIbeoData.m_LidarScanFLeft.push_back(TempLidarData); break;
			case FrontRight:TempIbeoData.m_LidarScanFRight.push_back(TempLidarData); break;
			}
		}
	}			
		


	//========================================
	void onData(const ObjectListLux* const pObj)
	{
	
		const std::vector<ObjectLux>& objects= pObj->getObjects();
		LidarTargetData TempTargerData;
		switch(flag)
		{
		case FrontLeft:TempIbeoData.m_LidarObjectFLeft.clear(); break;
		case FrontRight:TempIbeoData.m_LidarObjectFRight.clear(); break;
		}
		for (unsigned int i = 0; i < objects.size(); ++i) {
			
			//*****�洢����;*****/
			
			int VelocitySigmaX=objects.at(i).getAbsoluteVelocitySigmaX();
			int VelocitySigmaY=objects.at(i).getAbsoluteVelocitySigmaY();
			ibeo::UINT16 ObjectX,ObjectY;
			if(flag==FrontLeft)//****Back left lidar*****//
			{
				 ObjectX=objects.at(i).getBoundingBoxCenter().getX()+LIDAR_FRONT_LEFT_POSITION_X;
				 ObjectY=objects.at(i).getBoundingBoxCenter().getY()+LIDAR_FRONT_LEFT_POSITION_Y;
			}

			else if (flag==FrontRight)//****Back right lidar*****//
			{
				ObjectX=objects.at(i).getObjectBoxSizeX()+LIDAR_FRONT_RIGHT_POSITION_X;
				ObjectY=objects.at(i).getObjectBoxSizeY()+LIDAR_FRONT_RIGHT_POSITION_Y;
			}	
			
			TempTargerData.SetTargetX(ObjectX);
			TempTargerData.SetTargetY(objects.at(i).getObjectBoxSizeY());
			TempTargerData.SetTargetLength(objects.at(i).getBoundingBoxLength());
			TempTargerData.SetTargetWidth(objects.at(i).getBoundingBoxWidth());
			TempTargerData.SetTargetVelocity(0.707*VelocitySigmaX+0.707*VelocitySigmaY);
			switch(flag)
			{
			case FrontLeft:TempIbeoData.m_LidarObjectFLeft.push_back(TempTargerData);break;
			case FrontRight:TempIbeoData.m_LidarObjectFRight.push_back(TempTargerData);break;
			}
		}

	}

private:
	int flag;
	//========================================;
};



void IbeoLidar::init(int flag)
{
	const char *argv[]={"D:\\"};//�����ַ
	const off_t maxLogFileSize = 1000000;
	logfile.setTargetFileSize(maxLogFileSize);
	logfile.setLogFileBaseName(argv[0]);
	logFileManager.start();
	logInfo << argv[0] << "/n" 
		<< " IP��" << ip[flag] << std::endl;
	
}

bool IbeoLidar::isLidarWork()
{
	return 0;

}

void IbeoLidar::beginScan(int flag)
{
	

	AllLuxListener allLuxListener(flag);
	//const uint16_t port = getPort(ip[flag], 12002);
	IbeoLux lux(ip[flag],12002);
	//ע�⣬��ʼ������ʱ����Ҫ����LogFileManager����󣬷���ᱨ��;
	lux.registerListener(dynamic_cast<DataListener<ScanLux>*>(&allLuxListener));
	lux.registerListener(dynamic_cast<DataListener<ObjectListLux>*>(&allLuxListener));
	lux.getConnected();	
	_sleep(300);
	
}