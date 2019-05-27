// Deployment.h

#ifndef DEPLOYMENT_H
#define DEPLOYMENT_H

// ==================================================
// ���ñ���

// Բ����
static const double PI = 3.141592653589793;
// ���Ƕ�תΪ����
static const double d2r = PI / 180;
// ������תΪ�Ƕ�
static const double r2d = 1 / d2r;
// ��Ȼ�����ĵ�
static const double e = 2.71828182845905;


class Deployment
{
	// ���ĳ����ת����ϵ Se: ze ��ָ�򱱼�, xe ���س��ƽ���� Greenwich ��������ཻ��, ye �������ַ���ȷ��.
	// ����Ǧ������ϵ Sv: zv �ᵱ��Ǧ������, xv �� yv �ڵ���ˮƽ����, xv ָ��, yv ָ��.
	// �����������ϵ Sg: �� Sv �� zv ����ת�Ƕ� theta_azg ʹ xv ��ָ������������߼��� Sg.
public:
// Constructor
	// Lg: ���岿��㾭�� [deg]
	// Bg: ���岿�����γ�� [deg]
	// hg: ���岿���߳� [m]
	// theta_azg: �����������ϵ x ���뵱��Ǧ������ϵ x ��ļн�, �ɵ���Ǧ������ϵ x ��ת����������ϵ x ��Ϊ�� [deg]
	Deployment(double Lg = 116.38, double Bg = 39.9, double hg = 0, double theta_azg = 0);
	~Deployment();

// Attributes
	// ���õ�������ģ�ͳ������ƫ����
	// RE: ��������ģ�ͳ����� [m]
	// f: ��������ģ��ƫ����
	void SetREandf(double RE, double f);

	// ��ȡ��������ģ�ͳ������ƫ����
	// RE: ��������ģ�ͳ����� [m]
	// f: ��������ģ��ƫ����
	void GetREandf(double &RE, double &f) const;

private:
	double m_Lg;	// ���岿��㾭�� [rad]
	double m_Bg;	// ���岿�����γ�� [rad]
	double m_hg;	// ���岿���߳� [m]
	double m_theta_azg;	// �����������ϵ x ���뵱��Ǧ������ϵ x ��ļн�, �ɵ���Ǧ������ϵ x ��ת�������������ϵ x ��Ϊ�� [rad]
	double m_RE;	// ��������ģ�ͳ����� [m]
	double m_f;		// ��������ģ��ƫ����

	// ����ת������ Cge �еĸ�Ԫ��
	double m_c11;
	double m_c12;
	double m_c13;
	double m_c21;
	double m_c22;
	double m_c23;
	double m_c31;
	double m_c32;
	double m_c33;

	// ����ָ�������������ϵԭ���ʸ���ڵ���ֱ������ϵ�е�����
	double m_xRoge;
	double m_yRoge;
	double m_zRoge;

// Implementation
public:
	// ����ʸ���˵�ľ���,���γ�Ⱥ͸̼߳����ʸ���ڵ�������ϵ�е���������
	// vector_x, vector_y, vector_z: ʸ���ڵ�������ϵ�е��������� [m]
	// L: ����[rad]
	// B: ���γ��[rad]
	// h: �߳� [m]
	void GetEcFromLBH(double &vector_x, double &vector_y, double &vector_z, double L, double B, double h) const;

	// ����ʸ���˵��ڵ�������ϵ�е��������������ʸ���ĸ߳�,���Ⱥʹ��γ��
	// L: ����[rad]
	// B: ���γ��[rad]
	// h: �߳� [m]
	// vector_x, vector_y, vector_z: ʸ���ڵ�������ϵ�е��������� [m]
	void GetLBHFromEc(double &L, double &B, double &h, double vector_x, double vector_y, double vector_z) const;

	// ����ʸ���˵�ľ���, ���γ�Ⱥ͸̼߳���ʸ���˵��������������ϵ�е�����
	// xrg, yrg, zrg: ʸ���˵��������������ϵ�е��������� [m]
	// L: ʸ���˵�ľ���[rad]
	// B: ʸ���˵�Ĵ��γ��[rad]
	// h: ʸ���˵�ĸ߳� [m]
	void GetXYZFromLBH(double &xrg, double &yrg, double &zrg, double L, double B, double h) const;

	// ����ʸ���˵��������������ϵ�е��������ʸ���˵�ľ���, ���γ�Ⱥ͸߳�
	// L: ʸ���˵�ľ���[rad]
	// B: ʸ���˵�Ĵ��γ��[rad]
	// h: ʸ���˵�ĸ߳� [m]
	// xrg, yrg, zrg: ʸ���˵��������������ϵ�е��������� [m]
	void GetLBHFromXYZ(double &L, double &B, double &h, double xrg, double yrg, double zrg) const;

	// ��ʸ���������������ϵ�е��������ת��Ϊʸ���ڵ��ĳ����ת����ϵ�е��������
	// xrhoe, yrhoe, zrhoe: ʸ���ڵ��ĳ����ת����ϵ�е��������
	// xrhog, yrhog, zrhog: ʸ���������������ϵ�е��������
	void GetEcVFromGcV(double &xrhoe, double &yrhoe, double &zrhoe,	double xrhog, double yrhog, double zrhog) const;

	// ��ʸ���ڵ��ĳ����ת����ϵ�е��������ת��Ϊʸ���������������ϵ�е��������
	// xrhog, yrhog, zrhog: ʸ���������������ϵ�е��������
	// xrhoe, yrhoe, zrhoe: ʸ���ڵ��ĳ����ת����ϵ�е��������
	void GetGcVFromEcV(double &xrhog, double &yrhog, double &zrhog,	double xrhoe, double yrhoe, double zrhoe) const;

	// ��ʸ���ڵ���Ǧ������ϵ�е��������ת��Ϊʸ���ڵ��ĳ����ת����ϵ�е��������
	// xrhoe, yrhoe, zrhoe: ʸ���ڵ��ĳ����ת����ϵ�е��������
	// xlocal, ylocal, zlocal: ʸ���ڵ���Ǧ������ϵ�е��������
	// L: ����Ǧ������ϵԭ�㾭��[rad]
	// B: ����Ǧ������ϵԭ����γ��[rad]
	void GetEcVFromLcV(double &xrhoe, double &yrhoe, double &zrhoe,
		double xlocal, double ylocal, double zlocal, double L, double B) const;

	// ��ʸ���ڵ��ĳ����ת����ϵ�е��������ת��Ϊʸ���ڵ���Ǧ������ϵ�е��������
	// xlocal, ylocal, zlocal: ʸ���ڵ���Ǧ������ϵ�е��������
	// xrhoe, yrhoe, zrhoe: ʸ���ڵ��ĳ����ת����ϵ�е��������
	// L: ����Ǧ������ϵԭ�㾭��[rad]
	// B: ����Ǧ������ϵԭ����γ��[rad]
	void GetLcVFromEcV(double &xlocal, double &ylocal, double &zlocal,
		double xrhoe, double yrhoe, double zrhoe, double L, double B) const;

	// ��ʸ���ڵ���Ǧ������ϵ�е��������ת��Ϊʸ���������������ϵ�е��������
	// xrhog, yrhog, zrhog: ʸ���������������ϵ�е��������
	// xlocal, ylocal, zlocal: ʸ���ڵ���Ǧ������ϵ�е��������
	// L: ����Ǧ������ϵԭ�㾭��[rad]
	// B: ����Ǧ������ϵԭ����γ��[rad]
	void GetGcVFromLcV(double &xrhog, double &yrhog, double &zrhog,
		double xlocal, double ylocal, double zlocal, double L, double B) const;

	// ��ʸ���������������ϵ�е��������ת��Ϊʸ���ڵ���Ǧ������ϵ�е��������
	// xlocal, ylocal, zlocal: ʸ���ڵ���Ǧ������ϵ�е��������
	// xrhog, yrhog, zrhog: ʸ���������������ϵ�е��������
	// L: ����Ǧ������ϵԭ�㾭��[rad]
	// B: ����Ǧ������ϵԭ����γ��[rad]
	void GetLcVFromGcV(double &xlocal, double &ylocal, double &zlocal,
		double xrhog, double yrhog, double zrhog, double L, double B) const;
};

#endif