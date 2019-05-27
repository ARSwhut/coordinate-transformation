// Deployment.cpp


#include "Deployment.h"
#include <cmath>

using namespace std;



// ==================================================
// Deployment ��ʵ��

// Lg: ���� [deg]
// Bg: γ�� [deg]
// hg: �߶� [m]
// theta_azg: ��������ϵ x ���뵱��Ǧ������ϵ x ��ļн�, �ɵ���Ǧ������ϵ x ��ת����������ϵ x ��Ϊ�� [deg]
Deployment::Deployment(double Lg, double Bg, double hg, double theta_azg)
	:m_Lg(Lg*d2r)
	,m_Bg(Bg*d2r)
	,m_hg(hg)
	,m_theta_azg(theta_azg*d2r)
{
	double RE = 6378.14e3;	// Ĭ�ϵĵ�������ģ�ͳ����� [m]
	double RP = 6356.755e3;	// Ĭ�ϵĵ�������ģ�Ͷ̰��� [m]

	m_RE = RE;
	m_f = (RE-RP)/RE;

	double sLg = sin(m_Lg);
	double cLg = cos(m_Lg);
	double sBg = sin(m_Bg);
	double cBg = cos(m_Bg);
	double stheta_azg = sin(theta_azg);
	double ctheta_azg = cos(theta_azg);

	m_c11 = - ctheta_azg*sBg*cLg-stheta_azg*sLg;
	m_c12 = - ctheta_azg*sBg*sLg+stheta_azg*cLg;
	m_c13 = ctheta_azg*cBg;
	m_c21 = stheta_azg*sBg*cLg-ctheta_azg*sLg;
	m_c22 = stheta_azg*sBg*sLg+ctheta_azg*cLg;
	m_c23 = - stheta_azg*cBg;
	m_c31 = - cBg*cLg;
	m_c32 = - cBg*sLg;
	m_c33 = - sBg;

	GetEcFromLBH(m_xRoge, m_yRoge, m_zRoge, m_Lg, m_Bg, m_hg);
}

Deployment::~Deployment()
{}

// ���õ�������ģ�ͳ������ƫ����
// RE: ��������ģ�ͳ����� [m]
// f: ��������ģ��ƫ����
void Deployment::SetREandf(double RE, double f)
{
	m_RE = RE;
	m_f = f;
}

// ��ȡ��������ģ�ͳ������ƫ����
// RE: ��������ģ�ͳ����� [m]
// f: ��������ģ��ƫ����
void Deployment::GetREandf(double &RE, double &f) const
{
	RE = m_RE;
	f = m_f;
}

// ����ʸ���˵�ľ���,���γ�Ⱥ͸̼߳����ʸ���ڵ�������ϵ�е���������
// vector_x, vector_y, vector_z: ʸ���ڵ�������ϵ�е��������� [m]
// L: ����[rad]
// B: γ��[rad]
// h: �߳� [m]
void Deployment::GetEcFromLBH(double &vector_x, double &vector_y, double &vector_z, double L, double B, double h) const
{
	double PHI, Roh, u, Ro, u_, su_plusPHI, cu_plusPHI;
	double tmp1, tmp2;
	double a, b;

	a = m_RE;
	b = m_RE*(1-m_f);

	PHI = atan(b*b/(a*a)*tan(B));
	tmp1 = b*cos(PHI);
	tmp2 = a*sin(PHI);
	Roh = a*b/sqrt(tmp1*tmp1+tmp2*tmp2);
	u = B-PHI;
	Ro = sqrt(Roh*Roh+h*h+2*h*Roh*cos(u));
	u_ = asin(h*sin(u)/Ro);
	su_plusPHI = sin(u_+PHI);
	cu_plusPHI = cos(u_+PHI);
	vector_x = Ro*cu_plusPHI*cos(L);
	vector_y = Ro*cu_plusPHI*sin(L);
	vector_z = Ro*su_plusPHI;
}

// ����ʸ���˵��ڵ�������ϵ�е��������������ʸ���ĸ߳�,���Ⱥʹ��γ��
// L: ����[rad]
// B: ���γ��[rad]
// h: �߳� [m]
// vector_x, vector_y, vector_z: ʸ���ڵ�������ϵ�е��������� [m]
void Deployment::GetLBHFromEc(double &L, double &B, double &h, double vector_x, double vector_y, double vector_z) const
{
	double Ro = sqrt(vector_x*vector_x+vector_y*vector_y+vector_z*vector_z);
	double phi = asin(vector_z/Ro);
	L = atan2(vector_y, vector_x);
	double sphi = sin(phi);
	double s2phi = sin(2*phi);
	double s4phi = sin(4*phi);
	h = Ro-m_RE*(1-m_f*sphi*sphi-0.5*m_f*m_f*s2phi*s2phi*(m_RE/Ro-0.25));
	double A = asin(m_RE/Ro*(m_f*s2phi+m_f*m_f*s4phi*(m_RE/Ro-0.25)));
	B = A+phi;
}

// ����ʸ���˵��ڲ�������ϵ�е�����
// xrg, yrg, zrg: ʸ���˵��������������ϵ�е��������� [m]
// L: ʸ���˵�ľ���[rad]
// B: ʸ���˵�Ĵ��γ��[rad]
// h: ʸ���˵�ĸ߳� [m]
void Deployment::GetXYZFromLBH(double &xrg, double &yrg, double &zrg, double L, double B, double h) const
{
	double xRe, yRe, zRe;
	GetEcFromLBH(xRe, yRe, zRe, L, B, h);
	double xre = xRe-m_xRoge;
	double yre = yRe-m_yRoge;
	double zre = zRe-m_zRoge;
	GetGcVFromEcV(xrg, yrg, zrg, xre, yre, zre);
}

// ����ʸ���˵��������������ϵ�е��������ʸ���˵�ľ���, ���γ�Ⱥ͸߳�
// L: ʸ���˵�ľ���[rad]
// B: ʸ���˵�Ĵ��γ��[rad]
// h: ʸ���˵�ĸ߳� [m]
// xrg, yrg, zrg: ʸ���˵��������������ϵ�е��������� [m]
void Deployment::GetLBHFromXYZ(double &L, double &B, double &h, double xrg, double yrg, double zrg) const
{
	double xre, yre, zre;
	GetEcVFromGcV(xre, yre, zre, xrg, yrg, zrg);
	double xRe = m_xRoge+xre;
	double yRe = m_yRoge+yre;
	double zRe = m_zRoge+zre;
	GetLBHFromEc(L, B, h, xRe, yRe, zRe);
}

// ��ʸ���������������ϵ�е��������ת��Ϊʸ���ڵ��ĳ����ת����ϵ�е��������
// xrhoe, yrhoe, zrhoe: ʸ���ڵ��ĳ����ת����ϵ�е��������
// xrhog, yrhog, zrhog: ʸ���������������ϵ�е��������
void Deployment::GetEcVFromGcV(double &xrhoe, double &yrhoe, double &zrhoe,	double xrhog, double yrhog, double zrhog) const
{
	xrhoe = m_c11*xrhog+m_c21*yrhog+m_c31*zrhog;
	yrhoe = m_c12*xrhog+m_c22*yrhog+m_c32*zrhog;
	zrhoe = m_c13*xrhog+m_c23*yrhog+m_c33*zrhog;
}

// ��ʸ���ڵ��ĳ����ת����ϵ�е��������ת��Ϊʸ���������������ϵ�е��������
// xrhog, yrhog, zrhog: ʸ���������������ϵ�е��������
// xrhoe, yrhoe, zrhoe: ʸ���ڵ��ĳ����ת����ϵ�е��������
void Deployment::GetGcVFromEcV(double &xrhog, double &yrhog, double &zrhog,	double xrhoe, double yrhoe, double zrhoe) const
{
	xrhog = m_c11*xrhoe+m_c12*yrhoe+m_c13*zrhoe;
	yrhog = m_c21*xrhoe+m_c22*yrhoe+m_c23*zrhoe;
	zrhog = m_c31*xrhoe+m_c32*yrhoe+m_c33*zrhoe;
}

// ��ʸ���ڵ���Ǧ������ϵ�е��������ת��Ϊʸ���ڵ��ĳ����ת����ϵ�е��������
// xrhoe, yrhoe, zrhoe: ʸ���ڵ��ĳ����ת����ϵ�е��������
// xlocal, ylocal, zlocal: ʸ���ڵ���Ǧ������ϵ�е��������
// L: ����Ǧ������ϵԭ�㾭��[rad]
// B: ����Ǧ������ϵԭ����γ��[rad]
void Deployment::GetEcVFromLcV(double &xrhoe, double &yrhoe, double &zrhoe,
							   double xlocal, double ylocal, double zlocal, double L, double B) const
{
	double sL = sin(L);
	double cL = cos(L);
	double sB = sin(B);
	double cB = cos(B);

	double c11 = - sB*cL;
	double c12 = - sB*sL;
	double c13 = cB;
	double c21 = -sL;
	double c22 = cL;
	double c23 = 0;
	double c31 = - cB*cL;
	double c32 = - cB*sL;
	double c33 = - sB;

	xrhoe = c11*xlocal+c21*ylocal+c31*zlocal;
	yrhoe = c12*xlocal+c22*ylocal+c32*zlocal;
	zrhoe = c13*xlocal+c23*ylocal+c33*zlocal;
}

// ��ʸ���ڵ��ĳ����ת����ϵ�е��������ת��Ϊʸ���ڵ���Ǧ������ϵ�е��������
// xlocal, ylocal, zlocal: ʸ���ڵ���Ǧ������ϵ�е��������
// xrhoe, yrhoe, zrhoe: ʸ���ڵ��ĳ����ת����ϵ�е��������
// L: ����Ǧ������ϵԭ�㾭��[rad]
// B: ����Ǧ������ϵԭ����γ��[rad]
void Deployment::GetLcVFromEcV(double &xlocal, double &ylocal, double &zlocal,
							   double xrhoe, double yrhoe, double zrhoe, double L, double B) const
{
	double sL = sin(L);
	double cL = cos(L);
	double sB = sin(B);
	double cB = cos(B);

	double c11 = - sB*cL;
	double c12 = - sB*sL;
	double c13 = cB;
	double c21 = -sL;
	double c22 = cL;
	double c23 = 0;
	double c31 = - cB*cL;
	double c32 = - cB*sL;
	double c33 = - sB;

	xlocal = c11*xrhoe+c12*yrhoe+c13*zrhoe;
	ylocal = c21*xrhoe+c22*yrhoe+c23*zrhoe;
	zlocal = c31*xrhoe+c32*yrhoe+c33*zrhoe;
}

// ��ʸ���ڵ���Ǧ������ϵ�е��������ת��Ϊʸ���������������ϵ�е��������
// xrhog, yrhog, zrhog: ʸ���������������ϵ�е��������
// xlocal, ylocal, zlocal: ʸ���ڵ���Ǧ������ϵ�е��������
// L: ����Ǧ������ϵԭ�㾭��[rad]
// B: ����Ǧ������ϵԭ����γ��[rad]
void Deployment::GetGcVFromLcV(double &xrhog, double &yrhog, double &zrhog,
							   double xlocal, double ylocal, double zlocal, double L, double B) const
{
	double xrhoe, yrhoe, zrhoe;
	GetEcVFromLcV(xrhoe, yrhoe, zrhoe, xlocal, ylocal, zlocal, L, B);
	GetGcVFromEcV(xrhog, yrhog, zrhog, xrhoe, yrhoe, zrhoe);
}

// ��ʸ���������������ϵ�е��������ת��Ϊʸ���ڵ���Ǧ������ϵ�е��������
// xlocal, ylocal, zlocal: ʸ���ڵ���Ǧ������ϵ�е��������
// xrhog, yrhog, zrhog: ʸ���������������ϵ�е��������
// L: ����Ǧ������ϵԭ�㾭��[rad]
// B: ����Ǧ������ϵԭ����γ��[rad]
void Deployment::GetLcVFromGcV(double &xlocal, double &ylocal, double &zlocal,
							   double xrhog, double yrhog, double zrhog, double L, double B) const
{
	double xrhoe, yrhoe, zrhoe;
	GetEcVFromGcV(xrhoe, yrhoe, zrhoe, xrhog, yrhog, zrhog);
	GetLcVFromEcV(xlocal, ylocal, zlocal, xrhoe, yrhoe, zrhoe, L, B);
}