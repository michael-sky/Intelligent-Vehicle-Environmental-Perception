
/*
 * Copyright 2015 Intelligent Vehicle Lab of CQUPT.
 * Author :Tian Zhen   
 * Date:2015.5.4 
 *	
 * ����һ��lidar���߼����״����ݲɼ���ͷ�ļ���������һ��lidar��
 *    IbeoLidar�����״�ɼ��࣬init��IBEO�����״���г�ʼ��
 *
 */
#pragma once
#include "database.h"
#include "Urg_driver.h"
#include <vector>


using namespace qrk;
using namespace std;


class SingleLineLidar
{
public:
	bool open(int);
	void beginScan(int);
	void preProData(void);

	Urg_driver urg;
	vector<LidarData> m_LidarScanData;
	vector<LidarTargetData> m_LidarTarget;

protected:
private:
		
};

extern SingleLineLidar lidar_BR;extern SingleLineLidar lidar_BL;extern SingleLineLidar lidar_ML;
extern SingleLineLidar lidar_MR;





