#include <GL/glut.h>
#include <math.h>
#include <vector>

using namespace std;
int MX = 300;
int MY = 300;
float time = 0; //�ð�
int shot = 0;//����ü �ڵ� �߻� ����
float x = 0, y = 35; //�÷��̾�  ��ǥ
float a = 0, b = -30;//���� ��ǥ(�ʱ���ǥ)
int mon_life = 10;
int man_life = 5;


class vec3 {
public:
	float m[3];
	vec3(float x = 0, float y = 0, float z = 0) {
		m[0] = x; m[1] = y; m[2] = z;
	}
	vec3 operator+(vec3 x) {
		return vec3(m[0] + x.m[0],
			m[1] + x.m[1],
			m[2] + x.m[2]);
	}
	vec3 operator-(vec3 x) {
		return vec3(m[0] - x.m[0],
			m[1] - x.m[1],
			m[2] - x.m[2]
		);
	}
	vec3 operator*(float x) {
		return vec3(m[0] * x, m[1] * x, m[2] * x);
	}
	float Length() {
		return sqrtf(m[0] * m[0] + m[1] * m[1] + m[2] * m[2]);
	}
};

class Bullet {
public:
	vec3 v;
	vec3 pos;
};
vector <Bullet> bullet1;
vector <Bullet> bullet2;
vector <Bullet> bullet2_1;
vector <Bullet> bullet2_2;
vector <Bullet> first;

void InitLight(int n) {
	GLfloat mat_diffuse_ground[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat mat_specular_ground[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_ambient_ground[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_shininess_ground[] = { 15.0 };

	GLfloat mat_diffuse_man[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat mat_specular_man[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_ambient_man[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_shininess_man[] = { 15.0 };

	GLfloat mat_diffuse_mon[] = { 0.8, 0.4, 0.3, 1.0 };
	GLfloat mat_specular_mon[] = { 0.7, 0.4, 0.5, 1.0 };
	GLfloat mat_ambient_mon[] = { 0.9, 0.5, 0.5, 1.0 };
	GLfloat mat_shininess_mon[] = { 15.0 };

	GLfloat mat_diffuse_bul1[] = { 0.7, 0.7, 0.4, 1.0 };
	GLfloat mat_specular_bul1[] = { 0.7, 0.7, 0.4, 1.0 };
	GLfloat mat_ambient_bul1[] = { 0.8, 0.8, 0.4, 1.0 };
	GLfloat mat_shininess_bul1[] = { 15.0 };

	GLfloat mat_diffuse_bul2[] = { 0.3, 0.4, 0.8, 1.0 };
	GLfloat mat_specular_bul2[] = { 0.5, 0.4, 0.7, 1.0 };
	GLfloat mat_ambient_bul2[] = { 0.5, 0.5, 0.9, 1.0 };
	GLfloat mat_shininess_bul2[] = { 15.0 };

	GLfloat light_specular[] = { 1.0, 0.8, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -3, 6, 3.0, 0.0 };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);


	//�������� ��ü���� �ٸ� ��
	switch (n) {
	case 0:
	default:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_ground);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_ground);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_ground);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_ground);
		break;
	case 1:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_man);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_man);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_man);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_man);
		break;
	case 2:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_mon);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_mon);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_mon);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_mon);
		break;
	case 3:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_bul1);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_bul1);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_bul1);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_bul1);
		break;
	case 4:
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_bul2);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_bul2);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_bul2);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_bul2);
		break;
	}

	glEnable(GL_NORMALIZE);
}



void MyTimer(int value) {
	time += 30.0;
	shot += 1;
	glutPostRedisplay();
	glutTimerFunc(20, MyTimer, 1);
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0, 25.0, -25.0, 25.0, -100.0, 100.0); // 15�� ���� view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.8, 1.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);  //������ȯ
}

bool HitCheckBullet1() {//�浹���� �÷��̾� �Ѿ�
	vec3 Mon(a, 6, b);
	
	int size = bullet1.size();


	for (int i = 0; i < size; i++) {//�÷��̾� �Ѿ� ����
			vec3 diff = Mon - bullet1[i].pos;
			if (diff.Length() < 3.8) {
				bullet1.erase(bullet1.begin() + i); //�浹�� �����
				return true;
			}
	}
	return false;

}

bool HitCheckBullet2() {//�浹���� ���� ����ü
	vec3 Man(x,3, y);

	int size2 = bullet2.size();
	int size2_1 = bullet2_1.size();
	int size2_2 = bullet2_2.size();

	for (int i = 0; i < size2; i++) {//���� ����ü ����
		vec3 diff = Man - bullet2[i].pos;
		if (diff.Length() < 4) {
			bullet2.erase(bullet2.begin() + i); //�浹�� �����
			return true;
		}
	}

	for (int i = 0; i < size2_1; i++) {//���� ����ü ����
		vec3 diff = Man - bullet2_1[i].pos;
		if (diff.Length() < 4) {
			bullet2_1.erase(bullet2_1.begin() + i); //�浹�� �����
			return true;
		}
	}

	for (int i = 0; i < size2_2; i++) {//���� ����ü ����
		vec3 diff = Man - bullet2_2[i].pos;
		if (diff.Length() < 4) {
			bullet2_2.erase(bullet2_2.begin() + i); //�浹�� �����
			return true;
		}
	}

	return false;

}



bool HitCheckContact() {//�浹���� ����-�÷��̾� ����
	vec3 Mon(a, 6, b);
	vec3 Man(x, 6, y);

	vec3 diff = Man - Mon;
	if (diff.Length() < 3)
		return true;
	else
		return false;

}


void UpdateBullet() { //�Ѿ� ������

	int size = bullet1.size();

	for (int i = 0; i < size; i++) {
		//bullet1[i].v = bullet1[i].v + 0.1;
		
		bullet1[i].pos = bullet1[i].pos + bullet1[i].v * 0.7;


	}

	
}

void createBullet2() {//���� ����ü ����

	shot = 0; //0���� �ٽ� �ʱ�ȭ �Ѵ�.

	Bullet b2;
	b2.pos.m[0] = a;
	b2.pos.m[1] = 6;
	b2.pos.m[2] = b;
	b2.v.m[0] = 0;
	b2.v.m[1] = 0;
	b2.v.m[2] = 1;

	Bullet b2_1;
	b2_1.pos.m[0] = a;
	b2_1.pos.m[1] = 6;
	b2_1.pos.m[2] = b;
	b2_1.v.m[0] = 1;
	b2_1.v.m[1] = 0;
	b2_1.v.m[2] = 3;

	Bullet b2_2;
	b2_2.pos.m[0] = a;
	b2_2.pos.m[1] = 6;
	b2_2.pos.m[2] = b;
	b2_2.v.m[0] = -1;
	b2_2.v.m[1] = 0;
	b2_2.v.m[2] = 3;


	bullet2.push_back(b2);
	bullet2_1.push_back(b2_1);
	bullet2_2.push_back(b2_2);
}


void DrawBullet() { //�Ѿ� �׸���
	UpdateBullet();
	int size = bullet1.size();
	
	for (int i = 0; i < size; i++) {
		glPushMatrix();
		InitLight(3);
		glTranslatef(bullet1[i].pos.m[0], bullet1[i].pos.m[1], bullet1[i].pos.m[2]);
		glScalef(0.1, 0.1, 0.3);
		glutSolidSphere(3, 20, 20);
		glPopMatrix();
	}

		

	
}

void UpdateBullet2() {
	int size2 = bullet2.size();
	int size2_1 = bullet2_1.size();
	int size2_2 = bullet2_2.size();
	vec3 acc(0, -0.30, 0); //���ӵ�

	for (int i = 0; i < size2; i++) {//����ü���� ���� ƨ����
		bullet2[i].v = bullet2[i].v + acc*0.5;
		bullet2[i].pos = bullet2[i].pos + bullet2[i].v * 0.5;
		if (bullet2[i].pos.m[1] < 0.5 + 0.5) {
			bullet2[i].pos.m[1] = 1.0;
			bullet2[i].v.m[1] = fabs(bullet2[i].v.m[1]);
			bullet2[i].v = bullet2[i].v * 0.95;
		}
	}
	for (int i = 0; i < size2_1; i++) {
		bullet2_1[i].v = bullet2_1[i].v + acc * 0.3;
		bullet2_1[i].pos = bullet2_1[i].pos + bullet2_1[i].v * 0.3;
		if (bullet2_1[i].pos.m[1] < 0.5 + 0.5) {
			bullet2_1[i].pos.m[1] = 1.0;
			bullet2_1[i].v.m[1] = fabs(bullet2_1[i].v.m[1]);
			bullet2_1[i].v = bullet2_1[i].v * 0.95;
		}

	}
	for (int i = 0; i < size2_2; i++) {
		bullet2_2[i].v = bullet2_2[i].v + acc * 0.3;
		bullet2_2[i].pos = bullet2_2[i].pos + bullet2_2[i].v * 0.3;

		if (bullet2_2[i].pos.m[1] < 0.5 + 0.5) {
			bullet2_2[i].pos.m[1] = 1.0;
			bullet2_2[i].v.m[1] = fabs(bullet2_2[i].v.m[1]);
			bullet2_2[i].v = bullet2_2[i].v * 0.95;
		}
	}

	for (int i = 0; i < bullet2.size();) { //�� �� ƨ��� ������� ��
		if (bullet2[i].v.Length() < 0.85)
			bullet2.erase(bullet2.begin() + i);
		else
			i++;
	}
	for (int i = 0; i < bullet2_1.size();) {
		if (bullet2_1[i].v.Length() < 3.1)
			bullet2_1.erase(bullet2_1.begin() + i);
		else
			i++;
	}
	for (int i = 0; i < bullet2_2.size();) {
		if (bullet2_2[i].v.Length() < 3.1)
			bullet2_2.erase(bullet2_2.begin() + i);
		else
			i++;
	}
}

void DrawBullet2() {//������ ����ü 3���� ���ÿ� �߻��Ѵ�.
	UpdateBullet2();
	int size2 = bullet2.size();
	int size2_1 = bullet2_1.size();
	int size2_2 = bullet2_2.size();

	for (int i = 0; i < size2; i++) {

		glPushMatrix();
		InitLight(4);
		glTranslatef(bullet2[i].pos.m[0], bullet2[i].pos.m[1], bullet2[i].pos.m[2]);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();

	}

	for (int i = 0; i < size2_1; i++) {

		glPushMatrix();
		InitLight(4);
		glTranslatef(bullet2_1[i].pos.m[0], bullet2_1[i].pos.m[1], bullet2_1[i].pos.m[2]);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();

	}

	for (int i = 0; i < size2_2; i++) {

		glPushMatrix();
		InitLight(4);
		glTranslatef(bullet2_2[i].pos.m[0], bullet2_2[i].pos.m[1], bullet2_2[i].pos.m[2]);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();

	}

}




void DrawMan() {
	glPushMatrix();
		
	InitLight(1);

		glTranslatef(0, 3.0, 0);
		glPushMatrix();
		glScalef(0.9, 2.0, 0.9);
		glutSolidCube(1);    //����
		glPopMatrix();

	glPushMatrix();             //�����Ƚ���
		glTranslatef(0.5, 0.5, 0.5);
		glRotatef(260, 1, 0, 0);
		glTranslatef(0 ,1, 0);
		glPushMatrix();
		glScalef(0.3, 1, 0.3);
		glutSolidCube(1);
		glPopMatrix();
		
		//�ȸ�
		glTranslatef(0, 0.5, 0);
		glRotatef(30, 0, 0, 1);
		glPushMatrix();
		glTranslatef(0, 0.4, 0);
		glScalef(0.3, 1, 0.3);
		glutSolidCube(1);
		glPopMatrix();
		
		// �� 
		glTranslatef(0.0, 1, 0); 
		glPushMatrix();

		glRotatef(15, 1, 0, 0);
		glRotatef(-30, 0, 0, 1);
		glPushMatrix();          
		glScalef(0.2, 0.2, 0.8);
		glutSolidCube(1);
		glPopMatrix();
		
		//�ѱ�
		glTranslatef(0.0, 0.3, 0.5);
		glPushMatrix();
		glScalef(0.2, 1, 0.2);
		glutSolidCube(1);
		glPopMatrix();

		glPopMatrix();

	glPopMatrix();
	
	//����
	glPushMatrix();
		glTranslatef(-0.6,0.5,0);
		glRotatef(sin(time * 0.0045) * 15 + 200, 1, 0, 0);
		glTranslatef(0, 0.5, 0);
		glPushMatrix();
		glScalef(0.3, 1, 0.3);
		glutSolidCube(1);
		glPopMatrix();

		//�ȸ�
		glTranslatef(0, 0.5, 0);
		glRotatef(sin(time * 0.0045) * 15 + 30,1, 0, 0);
		glPushMatrix();
		glTranslatef(0, 0.4, 0);
		glScalef(0.3, 1, 0.3);
		glutSolidCube(1);
		glPopMatrix();
	glPopMatrix();

	//�����ٸ�
	glPushMatrix();
		glTranslatef(0.3, 0, 0);
		glRotatef(sin(time * 0.0045) * 15 + 5 , 1, 0, 0);
		glPushMatrix();
		glTranslatef(0, -1.5, 0);
		glScalef(0.4, 1, 0.4);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, -2.5,0);
		glRotatef ( - 15, 1, 0, 0);
		glTranslatef(0, 0, 0.2);
		glScalef(0.4, 1.5, 0.35);
		glutSolidCube(1);
		glPopMatrix();

	glPopMatrix();

	//�޴ٸ�
	glPushMatrix();
		glTranslatef(-0.3, 0, 0);
		glRotatef(sin(time * -0.0045) * 15 + 5, 1, 0, 0);
		glPushMatrix();
		glTranslatef(0, -1.5, 0);
		glScalef(0.4, 1, 0.4);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, -2.5, 0);
		glRotatef(-15, 1, 0, 0);
		glTranslatef(0, 0, 0.2);
		glScalef(0.4, 1.5, 0.35);
		glutSolidCube(1);
		glPopMatrix();

	glPopMatrix();

	//�Ӹ�
	glPushMatrix();
	glTranslatef(0, 1.3, 0);
	glutSolidCube(0.6);
	glPopMatrix();
	
	

	glPopMatrix();  
	
}

void DrawMonster() {
	

	glPushMatrix(); //��
	
	InitLight(2);
	
	glTranslatef(0, 6, 0);
		glutSolidSphere(3, 20, 20);
		
		glPushMatrix();// ��/�Ӹ�
			glTranslatef(0, 0, 2.5);
			glutSolidSphere(1, 20, 20); 
		glPopMatrix();

		//�޴ٸ� 1
		glPushMatrix();

		glRotatef(sin(time * 0.0045) * 10, 0, 0, 1);
		glTranslatef(3, -2, 1);
		glPushMatrix();
		glScalef(2, 0.4, 0.4);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();

		//����
		
		glTranslatef(0, 1, 0);
			glPushMatrix();
				glRotatef(sin(time * 0.0045) -30,0,0,1);
				glTranslatef(4, 0, 0);
				glPushMatrix();
				glScalef(2, 0.4, 0.4);
				glutSolidSphere(1, 20, 20);
				glPopMatrix();

				glTranslatef(0, 1, 0);
				glPushMatrix();//��
				glRotatef(sin(time * 0.0045) -30, 0, 0, 1);
				glScalef(1, 0.2, 0.2);
				glTranslatef(3, 0, 0);
				glutSolidSphere(1, 20, 20);
				glPopMatrix();
			glPopMatrix();

		glPopMatrix();

		//�޴ٸ� 2
		glPushMatrix();

		glRotatef(sin(time * 0.005) * 5, 0, 0, 1);
		glTranslatef(3, -2, 0);
		glPushMatrix();
		glScalef(2, 0.4, 0.4);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();

		//����

		glTranslatef(0, 1, 0);
		glPushMatrix();
		glRotatef(sin(time * 0.005)-30, 0, 0, 1);
		glTranslatef(4, 0, 0);
		glPushMatrix();
		glScalef(2, 0.4, 0.4);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();

		glTranslatef(0, 1, 0);
		glPushMatrix();//��
		glRotatef(sin(time * 0.005) -30, 0, 0, 1);
		glScalef(1, 0.2, 0.2);
		glTranslatef(3, 0, 0);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();
		glPopMatrix();


		glPopMatrix();

		//�޴ٸ� 3
		glPushMatrix();

		glRotatef(sin(time * 0.0048) * 10, 0, 0, 1);

		glTranslatef(3, -2, -1);
		glPushMatrix();
		glScalef(2, 0.4, 0.4);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();

		//����

		glTranslatef(0, 1, 0);
		glPushMatrix();
		glRotatef(sin(time * 0.0048) -30, 0, 0, 1);
		glTranslatef(4, 0, 0);
		glPushMatrix();
		glScalef(2, 0.4, 0.4);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();

		glTranslatef(0, 1, 0);
		glPushMatrix();//��
		glRotatef(sin(time * 0.0048) -30, 0, 0, 1);
		glScalef(1, 0.2, 0.2);
		glTranslatef(3, 0, 0);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();
		glPopMatrix();


		glPopMatrix();


		//�����ٸ� 1

		glPushMatrix();

		glRotatef(sin(time * 0.0045) * 10, 0, 0, 1);
		glTranslatef(-3, -2, 1);
		glPushMatrix();
		glScalef(2, 0.4, 0.4);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();

		//����

		glTranslatef(0, 1, 0);
		glPushMatrix();
		glRotatef(sin(time * 0.0045)+30, 0, 0, 1);
		glTranslatef(-4, 0, 0);
		glPushMatrix();
		glScalef(2, 0.4, 0.4);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();

		glTranslatef(0, 1, 0);
		glPushMatrix();//��
		glRotatef(sin(time * 0.0045) + 30, 0, 0, 1);
		glScalef(1, 0.2, 0.2);
		glTranslatef(-3, 0, 0);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();
		glPopMatrix();

		glPopMatrix();

		//�����ٸ� 2
		glPushMatrix();

		glRotatef(sin(time * 0.0050) * 5, 0, 0, 1);
		glTranslatef(-3, -2, 0);
		glPushMatrix();
		glScalef(2, 0.4, 0.4);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();

		//����

		glTranslatef(0, 1, 0);
		glPushMatrix();
		glRotatef(sin(time * 0.0050)+30, 0, 0, 1);
		glTranslatef(-4, 0, 0);
		glPushMatrix();
		glScalef(2, 0.4, 0.4);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();

		glTranslatef(0, 1, 0);
		glPushMatrix();//��
		glRotatef(sin(time * 0.0050)+30, 0, 0, 1);
		glScalef(1, 0.2, 0.2);
		glTranslatef(-3, 0, 0);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();
		glPopMatrix();

		glPopMatrix();
		//�����ٸ� 3
		glPushMatrix();

		glRotatef(sin(time * 0.0048) * 10, 0, 0, 1);
		glTranslatef(-3, -2, -1);
		glPushMatrix();
		glScalef(2, 0.4, 0.4);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();

		//����

		glTranslatef(0, 1, 0);
		glPushMatrix();
		glRotatef(sin(time * 0.0048)+30, 0, 0, 1);
		glTranslatef(-4, 0, 0);
		glPushMatrix();
		glScalef(2, 0.4, 0.4);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();

		glTranslatef(0, 1, 0);
		glPushMatrix();//��
		glRotatef(sin(time * 0.0048)+30, 0, 0, 1);
		glScalef(1, 0.2, 0.2);
		glTranslatef(-3, 0, 0);
		glutSolidSphere(1, 20, 20);
		glPopMatrix();
		glPopMatrix();

		glPopMatrix();


		//������

		//����




	glPopMatrix();
}


void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	if (KeyPressed == ' ') { //�Ѿ� �߻�
		Bullet b1;
		b1.pos.m[0] = x;
		b1.pos.m[1] = 3.8;
		b1.pos.m[2] = y-2;
		b1.v.m[0] = 0;
		b1.v.m[1] = 0;
		b1.v.m[2] = -1;
		bullet1.push_back(b1);
		glutPostRedisplay();
	}
}



void MySpecial(int key, int X, int Y) { //x,y ����� ���� ��ġ. a,b�� ������ ��ġ. �����ϼ��� �������. ������ �ӵ��� ���� �� ����.
	if (key == GLUT_KEY_UP) {
		y -= 0.5f;
		b += 0.4f;
		
	}
	if (key == GLUT_KEY_DOWN) {
		y += 0.5f;
		b += 0.4f;
		
	}
	if (key == GLUT_KEY_LEFT) {
		x -= 0.5f;
		a -= 0.5f;
		b += 0.5f;
	}
	if (key == GLUT_KEY_RIGHT) {
		x += 0.5f;
		a += 0.5f;
		b += 0.5f;
	}
	glutPostRedisplay();
}


void MyMouse(GLint X, GLint Y) {
	MX = X;
	MY = Y;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(MX /300.0, MY / 300.0, 1.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);  //������ȯ
	glutPostRedisplay();
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	InitLight(0);
	glPushMatrix();
	glScalef(400, 0.5, 400);//x-z���� ���� ��
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix(); //���
	//glTranslatef(0, 0, 35);
	glTranslatef(x, 0, y);
	DrawMan();
	glPopMatrix();


	glPushMatrix();//����
	//glTranslatef(0, 0, -15);
	glTranslatef(a, 0, b);
	DrawMonster();
	glPopMatrix();

	
	
	//����ü
	if (shot > 20) {//Ÿ�̸Ӱ� ���ڸ� �ڵ����� ���ϰ� 20�� �Ǹ� �����Ѵ�.
		createBullet2();
	}
	

	DrawBullet();
	DrawBullet2();



	bool hitB1 = HitCheckBullet1();
	
	if (hitB1) {
		mon_life--;
	}
	
	bool hitB2 = HitCheckBullet2();
	if (hitB2) {
		man_life--;
		//exit(0);
	}

	bool hit2 = HitCheckContact();
	if (hit2) 
		exit(0);
	
	if (mon_life == 0 || man_life == 0)
		exit(0);

	glFlush();

	

}





int main(int argc, char** argv) {
	glutInit(&argc, argv);               //GLUT ������ �Լ�
	glutInitWindowSize(600, 600);
	glutCreateWindow("Z");
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(20,MyTimer,1);
	glutSpecialFunc(MySpecial);
	glutMotionFunc(MyMouse);
	glutKeyboardFunc(MyKeyboard);
	glClearColor(0.4, 0.4, 0.4, 1);
	InitLight(0);
	
	glutMainLoop();
	return 0;
}