
/************************************************************************/
	/* ����ϵͳ��Ƶ�Ҫ�� ��ǰ���� 80m���� 20m;
	    ������ࡢ�Ҳࡢ�� 10m ���������ͼ;
		�����Χ��ĵ�;
	*/
/************************************************************************/


#pragma once

#include "database.h"
#include <list>
#include <vector>
using namespace std;

const int s_nGridFrontLenth=8000; //����ǰ�����ȵ�λ8000cm;
const int s_nGridBackLenth=1000;
const int s_nGridWidth=1000;
const int s_nCarLenth=1000;
const int s_nCarWidth=1000;



// ��������;
int DataClear(vector<LidarData> &data);
float TurnToRange(vector<LidarData> &data,int n);
int ClusterLidar(vector<LidarData> &Vectordata);
void IepfAlgorithm(vector<LidarData> &data);
void LeastSquareMethod(vector<BreakPointData> &breakdata,vector<LidarData> &data);
void FeatureExtraction(vector<BreakPointData> &breakdata,vector<LidarData> &data,vector<LidarTargetData> &Target);