


#include "database.h"
#include "DataProcessing.h"
#include <list>
#include <iostream>
#include<math.h>
#include <vector>
#include <algorithm> 
//	����դ���ͼ��Χ��ȥ����Χ��ĵ�;
int DataClear(vector<LidarData> &data)
{
	

	vector<LidarData>::iterator listpointer;
	for (listpointer=data.begin();listpointer!=data.end();++listpointer)
	{
		if ((abs(listpointer->GetScanX())) >(s_nGridWidth+s_nCarWidth ))
		{
			data.erase(listpointer);
		}
		
		if (listpointer->GetScanY()>s_nGridFrontLenth || listpointer->GetScanY()<-(s_nCarLenth+s_nGridBackLenth))
		{
			data.erase(listpointer);
		}
	}
	return 0;
}


float TurnToRange(vector<LidarData> &data,int n)
{
	float ScanX=data.at(n).GetScanX();
	float ScanY=data.at(n).GetScanY();
	float iScanRange=sqrt(ScanX*ScanX+ScanY*ScanY);
	return(iScanRange);
}



////	��ֵ�˲�;
//��ֵ�˲������⣬Y����ֱ���������û���ˣ�
//int GetMedianNum(list<LidarData> &data)  
//{  
//	vector<LidarData> Vectordata;
//	list<LidarData>::iterator ListPointer;
//	ListPointer=data.begin();
//
//	Vectordata.assign(data.begin(),data.end());//������ת��Ϊvector���ͣ�
//	int iVectorN=0;  //����ȡ������ֵ��
//
//	const int iFilterLen=10;   //��ָ�˲�����ֵ,ȡ������
//	
//
//	while (iVectorN<=Vectordata.size()-iFilterLen)//��ȥiFilterLen����Ϊ��������һ����û��iFilterLen�����Ͳ�����
//	{
//		//ð������
//		for (int i=iVectorN;i<iVectorN+iFilterLen-1;++i)
//		{
//			for (int j=iVectorN;j<iVectorN+iFilterLen-i-1;++j)
//			{
//				//if (TurnToRange(Vectordata,j)>TurnToRange(Vectordata,j+1))
//				if (Vectordata.at(j).GetScanY()>Vectordata.at(j+1).GetScanY())
//	
//				{
//					std::iter_swap (&Vectordata[j],&Vectordata[j+1]);
//				}
//			}
//		}
//		//ȡ��ָ��
//		for (int i=0;i<iFilterLen;++i)
//		{
//			
//			ListPointer->SetScanY(Vectordata.at((iVectorN+iFilterLen)/2).GetScanY());
//			++ListPointer;
//			++iVectorN;
//		}
//
//		
//	}
//
//	return 0;
//}
	
vector<BreakPointData> BreakPoints;


//���ھ���ľ����㷨
int ClusterLidar(vector<LidarData> &Vectordata)
{
	float Resolution=0.25;   //ת��Ϊ����M_PI/180
	float RLimit=2;
	float NoiseR=10; //�����趨������IBEO˵���ĵ�
	BreakPointData TempPoints;

	BreakPoints.clear();
	//�����㷨������Line Extraction in 2D Range Images for Mobile Robotics;
	for (int i=1;i<Vectordata.size();++i)
	{
		float Rn_1=TurnToRange(Vectordata,i-1);
		
		float Dmax=Rn_1*(sin(Resolution*3.14/180)/sin((RLimit-Resolution)*3.14/180))+3*NoiseR;
		
		float DinX=abs(Vectordata.at(i).GetScanX()-Vectordata.at(i-1).GetScanX());
		float DinY=abs(Vectordata.at(i).GetScanY()-Vectordata.at(i-1).GetScanY());
		float Din=sqrt(DinX*DinX+DinY*DinY);
		
	
		if (i==1) //�ſ�ʼ����x0,y0��Ϊ��ʼ�����
		{
						
			TempPoints.SetStartPosition(0);	
		}
		
		if (Din>Dmax)
		{
			TempPoints.SetEndPosition(i-1);

			if(TempPoints.GetPointNum()>4)   //�˵�������Ǳ���Ҫ����4���㣻
			{
				BreakPoints.push_back(TempPoints);//�洢һ����������յ�;
			}

			
			//��һ��X,Y��Ϊ��ʼ��;
			TempPoints.SetStartPosition(i);
		}
		
		if (i==(Vectordata.size()-1)) //����
		{
			TempPoints.SetEndPosition(Vectordata.size()-1);
			BreakPoints.push_back(TempPoints);//�洢һ����������յ�;
		}
	}
	
	cout<<"breakpoint"<<BreakPoints.size()<<endl;

	return 1;
}

