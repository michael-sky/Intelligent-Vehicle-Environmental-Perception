


#include "database.h"
#include "DataProcessing.h"
#include <list>
#include <iostream>



//	����դ���ͼ��Χ��ȥ����Χ��ĵ�;
int DataClear(list<LidarData> &data)
{
	

	list<LidarData>::iterator listpointer;
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


////	��ֵ�˲�;
//int GetMedianNum(list<LidarData> &data)  
//{  
//	list<LidarData>::iterator listpointer;
//	listpointer
//	
//	int i,j;// ѭ������  
//
//	unsigned char bTemp;  
//
//	// ��ð�ݷ��������������  
//	for (j = 0; j < iFilterLen - 1; j ++)  
//	{  
//		for (i = 0; i < iFilterLen - j - 1; i ++)  
//		{  
//			if (bArray[i] > bArray[i + 1])  
//			{  
//				// ����  
//				bTemp = bArray[i];  
//				bArray[i] = bArray[i + 1];  
//				bArray[i + 1] = bTemp;  
//			}  
//		}  
//	}  
//
//	// ������ֵ  
//	if ((iFilterLen & 1) > 0)  
//	{  
//		// ������������Ԫ�أ������м�һ��Ԫ��  
//		bTemp = bArray[(iFilterLen + 1) / 2];  
//	}  
//	else  
//	{  
//		// ������ż����Ԫ�أ������м�����Ԫ��ƽ��ֵ  
//		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;  
//	}  
//
//	return bTemp;  
//}  
