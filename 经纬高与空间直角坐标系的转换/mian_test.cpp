#include<iostream>
#include"Deployment.h"
using namespace std;

int main()
{
	//ԭ�㾭γ��
	double Lg0 = 124;
	double Bg0 = 28;
	double hg0 = 0;
	double theta_azg0 = 0;    

	Deployment deployment(Lg0, Bg0, hg0, theta_azg0);


	//��γ��    --->   xyz
	cout << "xyz  ---->  ��γ��" << endl;
	const int n = 4;
	double LBH0[n][3] = { {124,28,0},{125,28,0}, {123,28,0}, {124,27,0} };   //������������    ˳���� ��γ��
	double Txyz[n][3];       //�����������    ˳���� xyz    zΪ�߶�

	for (int i = 0; i < n; i++) {
		//ת�� 
		
		deployment.GetXYZFromLBH(Txyz[i][0], Txyz[i][1], Txyz[i][2]/*�߶�*/, LBH0[i][0] * d2r/*��λ:����*/, LBH0[i][1] * d2r/*��λ������*/, LBH0[i][2]);


		//���
		cout <<"LBH: "<< LBH0[i][0] << "     " << LBH0[i][1] << "     " << LBH0[i][2] << "  " << endl;
		cout << "xyz: " << Txyz[i][0] << "  "<<Txyz[i][1] << "  "<<Txyz[i][2] << "  " << endl;
		cout << endl;
	}





	//xyz  ---->  ��γ��
	cout << "xyz  ---->  ��γ��" << endl;
	double xyz0[n][3] = { {0,0,0}, {1500,0,2400},{10000,0,2400},{10000,10000,2400} };   //������������    ˳���� xyz    zΪ�߶�
	double TLBH[n][3];      //�����������    ˳����  ��γ��

	for (int i = 0; i < n; i++) {
		//ת�� 
		deployment.GetLBHFromXYZ(TLBH[i][0], TLBH[i][1], TLBH[i][2], xyz0[i][0], xyz0[i][1], xyz0[i][2]/*�߶�*/);
		TLBH[i][0] *= r2d;   //ת������������Ϊ����      ��=����*r2d
		TLBH[i][1] *= r2d;


		//���
		cout << "xyz: " << xyz0[i][0] << "     " << xyz0[i][1] << "     " << xyz0[i][2] << "  " << endl;
		cout << "LBH: " << TLBH[i][0] << "  " << TLBH[i][1] << "  " << TLBH[i][2] << "  " << endl;
		cout << endl;
	}



	//system("pause");
	return 0;
}