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
	float RLimit=5;		//�߽���ֵ,ֵԽ��DNAXԽС
	float NoiseR=10; //�����趨������IBEO˵���ĵ�
	BreakPointData TempPoints;
	BreakPoints.clear();
	//�����㷨������Line Extraction in 2D Range Images for Mobile Robotics;
	for (int i=1;i<Vectordata.size();i++)
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

			if(TempPoints.GetPointNum()>2)   //�ϵ�������Ǳ���Ҫ����2���㣻
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
	
	//����Ŀ����
	for (int i=0;i<BreakPoints.size();i++)
	{
		BreakPoints.at(i).SetObjectId(i);
	}

	return 1;
}


//��������֮��ľ���;
float GetPointDistance(LidarData p1, LidarData p2)   
{  
	float PointDistance=(p1.GetScanX()-p2.GetScanX())*(p1.GetScanX()-p2.GetScanX())+
		(p1.GetScanY()-p2.GetScanY())*(p1.GetScanY()-p2.GetScanY());
	PointDistance=sqrt((float)PointDistance);

	return PointDistance;  
} 

//���׹�ʽ��ȡ�㵽ֱ�ߵľ���;
float GetNearestDistance(LidarData PA, LidarData PB, LidarData PX)  
{  
	//PAΪ��㣬PBΪ�յ�;PXΪѡ��ĵ�
	//----------ͼ2--------------------  
	float a,b,c;  
	a=GetPointDistance(PB,PX);  
	if(a<=0.00001)  
		return 0.0f;  
	b=GetPointDistance(PA,PX);  
	if(b<=0.00001)  
		return 0.0f;  
	c=GetPointDistance(PA,PB);  
	if(c<=0.00001)  
		return a;//���PA��PB������ͬ�����˳������������ؾ���  
	//------------------------------  

	if(a*a>=b*b+c*c)//--------ͼ3--------  
		return b;      //����Ƕ۽Ƿ���b  
	if(b*b>=a*a+c*c)//--------ͼ4-------  
		return a;      //����Ƕ۽Ƿ���a  

	//ͼ1  
	float l=(a+b+c)/2;     //�ܳ���һ��  
	float s=sqrt(l*(l-a)*(l-b)*(l-c));  //���׹�ʽ�������Ҳ������ʸ����  
	return 2*s/c;  
}  


//ITERATIVE END-POINT FIT 
void IepfAlgorithm(vector<LidarData> &data)
{
	BreakPointData TempPoints;
	int SizeWW=BreakPoints.size();
	for (int i=0;i<SizeWW;i++)
	{
			int InsertPosition=1;  //�������ݵ�λ��
		const int IEPFThreshold=30;	//iepf�㷨�߽磻
		int StartPostion=BreakPoints.at(i).GetStartPosition();
		int EndPostion=BreakPoints.at(i).GetEndPosition();
		int ObjectID=BreakPoints.at(i).GetObjectId();
		float MaxDistance=0; // ���ľ���;
		int   MaxDistanceFlag=0; //�����봦ָ��������λ��
		
		// Ѱ��һ�����������ľ���;
		for (int j=1+StartPostion;j<EndPostion-1;j++)
		{
			int NearestDistance=GetNearestDistance(data.at(StartPostion),data.at(EndPostion),data.at(j));
			if (NearestDistance>MaxDistance)
			{
				MaxDistance=NearestDistance;
				MaxDistanceFlag=j;
			}
		}

		//���һ����������������ֵ,���Ϊ��������;
		if (MaxDistance>=IEPFThreshold)
		{
			BreakPoints.at(i).SetEndPosition(MaxDistanceFlag);
			TempPoints.SetStartPosition(MaxDistanceFlag);
			TempPoints.SetEndPosition(EndPostion);
			TempPoints.SetObjectId(ObjectID);		
			BreakPoints.insert(BreakPoints.begin()+i+1,TempPoints);
			i=0;
			SizeWW=BreakPoints.size();
			InsertPosition++;
		}
	}
	cout<<"breakpoint"<<BreakPoints.size()<<endl;
};

//��С���˷����ֱ��;
//���նϵ㣬�ı䴫�����data�������
void LeastSquareMethod(vector<BreakPointData> &breakdata,vector<LidarData> &data)
{
	float a,b;	//������С�����˷���������;
	

	for (int i=0;i<breakdata.size();i++)
	{
		int SizeN=breakdata.at(i).GetPointNum();
		int StartPostion=BreakPoints.at(i).GetStartPosition();
		float SumXY=0,SumX=0,SumY=0,SumXX=0;
		//SumXY Ϊplus��XiYi����SumX Ϊ plus��Xi����SumYΪpuls(Yi);
 		for (int j=0;j<SizeN;j++)
		{

			float Xj=data.at(j+StartPostion).GetScanX();
			float Yj=data.at(j+StartPostion).GetScanY();
			
			SumXY +=Xj*Yj;
			SumX +=Xj;
			SumY +=Yj;
			SumXX +=Xj*Xj;
		}
		a=(SumXX*SumY-SumX*SumXY)/(SizeN*SumXX-SumX*SumX);
		b=(SizeN*SumXY-SumX*SumY)/(SizeN*SumXX-SumX*SumX);
		

		//���ϵ����YתΪ��С���˷���Y��
		float ScanX=data.at(breakdata.at(i).GetStartPosition()).GetScanX();//��öϵ���ʼ��X����
		float LeastSquareY=a+b*ScanX;   //������Ӧ��С���˷���Y
		data.at(breakdata.at(i).GetStartPosition()).SetScanY(LeastSquareY);	//����Y

		//���ϵ��յ�YתΪ��С���˷���Y��
		ScanX=data.at(breakdata.at(i).GetEndPosition()).GetScanX();//��öϵ���ʼ��X����
		LeastSquareY=a+b*ScanX;   //������Ӧ��С���˷���Y
		data.at(breakdata.at(i).GetEndPosition()).SetScanY(LeastSquareY);	//����Y
	}
	
}


void FeatureExtraction(vector<BreakPointData> &breakdata,vector<LidarData> &data,vector<LidarTargetData> &Target)
{
	Target.clear();
	//��ȡbreakdata��һ��Ŀ��������߶�����;
	int i=0;
	while(i < breakdata.size())
	{
		int ObjectLine=1;
		for (int j = i+1;j < breakdata.size();j++)
		{
			if(breakdata.at(i).GetObjectId()!=breakdata.at(j).GetObjectId())
			{	
				breakdata.at(i).SetLineNum(ObjectLine);
				i=j;
				break;
			}
			ObjectLine++;

			//��������һ��;
			if (j==breakdata.size()-1)
			{
				breakdata.at(i).SetLineNum(ObjectLine);
				i=j;
				break;
			}

		}
		if (i==breakdata.size()-1)
		{
			breakdata.at(i).SetLineNum(1);
			break;
		}
	}
	
	LidarTargetData TempTargerData;
	
	
	//������ȡ;
	for (i=0;i<breakdata.size();i++)
	{
		int LineNum=breakdata.at(i).GetLineNum();
		
		if(LineNum==1)  //�߶�����Ϊ1�����//
		{
			float BreakStartX=data.at(breakdata.at(i).GetStartPosition()).GetScanX();
			float BreakEndX=data.at(breakdata.at(i).GetEndPosition()).GetScanX();
			float BreakStartY=data.at(breakdata.at(i).GetStartPosition()).GetScanY();
			float BreakEndY=data.at(breakdata.at(i).GetEndPosition()).GetScanY();
			int TargetWidth=sqrt((BreakStartX-BreakEndX)*(BreakStartX-BreakEndX)+
				(BreakStartY-BreakEndY)*(BreakStartY-BreakEndY)		);

			TempTargerData.SetTargetX((BreakStartX+BreakEndX)/2);
			TempTargerData.SetTargetY((BreakStartY+BreakEndY)/2);
			TempTargerData.SetTargetWidth(TargetWidth);
			TempTargerData.SetTargetLength(30);
			Target.push_back(TempTargerData);
		}

		if(LineNum==2)  //�߶�����Ϊ2�����//
		{
			float BreakStartX=data.at(breakdata.at(i).GetStartPosition()).GetScanX();
			float BreakEndX=data.at(breakdata.at(i).GetEndPosition()).GetScanX();
			float BreakStartY=data.at(breakdata.at(i+1).GetStartPosition()).GetScanY();
			float BreakEndY=data.at(breakdata.at(i+1).GetEndPosition()).GetScanY();
			int TargetWidth=sqrt((BreakStartX-BreakEndX)*(BreakStartX-BreakEndX));
			int TargetLength=sqrt((BreakStartY-BreakEndY)*(BreakStartY-BreakEndY));
			TempTargerData.SetTargetX((BreakStartX+BreakEndX)/2);
			TempTargerData.SetTargetY((BreakStartY+BreakEndY)/2);
			TempTargerData.SetTargetWidth(TargetWidth);
			TempTargerData.SetTargetLength(TargetLength);
			Target.push_back(TempTargerData);
		}

		if(LineNum>2)  //�߶�����Ϊ2�����//
		{
			for (int j=i;j<i+LineNum;j++)
			{
					//�ҵ������߶�LX��LY��
				FIND(i=0;i<breakdata.size();i++)
			}
			float BreakStartX=data.at(breakdata.at(i).GetStartPosition()).GetScanX();
			float BreakEndX=data.at(breakdata.at(i).GetEndPosition()).GetScanX();
			float BreakStartY=data.at(breakdata.at(i+1).GetStartPosition()).GetScanY();
			float BreakEndY=data.at(breakdata.at(i+1).GetEndPosition()).GetScanY();
			int TargetWidth=sqrt((BreakStartX-BreakEndX)*(BreakStartX-BreakEndX));
			int TargetLength=sqrt((BreakStartY-BreakEndY)*(BreakStartY-BreakEndY));
			TempTargerData.SetTargetX((BreakStartX+BreakEndX)/2);
			TempTargerData.SetTargetY((BreakStartY+BreakEndY)/2);
			TempTargerData.SetTargetWidth(TargetWidth);
			TempTargerData.SetTargetLength(TargetLength);
			Target.push_back(TempTargerData);
		}


	}

}


